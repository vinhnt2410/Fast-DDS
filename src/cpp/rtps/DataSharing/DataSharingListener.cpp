// Copyright 2020 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file DataSharingListener.cpp
 */

#include <rtps/DataSharing/DataSharingListener.hpp>
#include <fastdds/rtps/reader/RTPSReader.h>

#include <memory>
#include <mutex>

namespace eprosima {
namespace fastrtps {
namespace rtps {


DataSharingListener::DataSharingListener(
        std::shared_ptr<DataSharingNotification> notification,
        const std::string& datasharing_pools_directory,
        ResourceLimitedContainerConfig limits,
        RTPSReader* reader)
    : notification_(notification)
    , is_running_(false)
    , reader_(reader)
    , writer_pools_(limits)
    , datasharing_pools_directory_(datasharing_pools_directory)
{
}

DataSharingListener::~DataSharingListener()
{
    stop();
}

void DataSharingListener::run()
{
    std::unique_lock<Segment::mutex> lock(notification_->notification_->notification_mutex);
    while (is_running_.load())
    {
        notification_->notification_->notification_cv.wait(lock, [&]
                {
                    return !is_running_.load() || notification_->notification_->new_data.load();
                });
        
        if (!is_running_.load())
        {
            // Woke up because listener is stopped
            return;
        }

        do
        {
            // If during the processing some other writer adds a notification,
            // it will also set notification_->notification_->new_data
            notification_->notification_->new_data.store(false);
            lock.unlock();
            process_new_data();
            lock.lock();
        } while (is_running_.load() && notification_->notification_->new_data.load());
    }
}

void DataSharingListener::start()
{
    // Check the thread
    bool was_running = is_running_.exchange(true);
    if (was_running)
    {
        return;
    }

    // Initialize the thread
    listening_thread_ = new std::thread(&DataSharingListener::run, this);
}

void DataSharingListener::stop()
{
    // Notify the listening thread that is no longer running
    bool was_running = is_running_.exchange(false);
    if (!was_running)
    {
        return;
    }

    // Notify the thread and wait for it to finish
    notification_->notify();
    listening_thread_->join();
    delete listening_thread_;
}

void DataSharingListener::process_new_data ()
{
    logInfo(RTPS_READER, "Received new data notification");

    // Loop on the writers looking for data not read yet
    for (auto it = writer_pools_.begin(); it != writer_pools_.end(); ++it)
    {
        //First see if we have some liveliness asertion pending
        uint32_t new_assertion_sequence = it->pool->last_liveliness_sequence();
        if (it->last_assertion_sequence != new_assertion_sequence)
        {
            reader_->assert_writer_liveliness(it->pool->writer());
            it->last_assertion_sequence = new_assertion_sequence;
        }

        bool has_new_payload = true;
        while(has_new_payload)
        {
            CacheChange_t ch;
            has_new_payload = it->pool->get_next_unread_payload(ch);

            if (has_new_payload)
            {
                logInfo(RTPS_READER, "New data found on writer " <<it->pool->writer()
                        << " with SN " << ch.sequenceNumber);

                reader_->processDataMsg(&ch);
                it->pool->release_payload(ch);
            }
        }
    }
}

bool DataSharingListener::add_datasharing_writer(
    const GUID_t& writer_guid,
    bool is_volatile)
{
    // TODO [ILG] adding and removing must be protected
    if (writer_is_matched(writer_guid))
    {
        logInfo(RTPS_READER, "Attempting to add existing datasharing writer " << writer_guid);
        return false;
    }

    std::shared_ptr<DataSharingPayloadPool> pool = DataSharingPayloadPool::get_reader_pool(is_volatile);
    pool->init_shared_memory(writer_guid, datasharing_pools_directory_);
    writer_pools_.emplace_back(pool, pool->last_liveliness_sequence());

    return true;
}

bool DataSharingListener::remove_datasharing_writer(
    const GUID_t& writer_guid)
{
    return writer_pools_.remove_if (
            [writer_guid](const WriterInfo& info)
            {
                return info.pool->writer() == writer_guid;
            }
    );
}

bool DataSharingListener::writer_is_matched(
        const GUID_t& writer_guid) const
{
    auto it = std::find_if(writer_pools_.begin(), writer_pools_.end(),
        [writer_guid](const WriterInfo& info)
        {
            return info.pool->writer() == writer_guid;
        }
    );
    return (it != writer_pools_.end());
}

void DataSharingListener::notify()
{
    notification_->notify();
}

}  // namespace rtps
}  // namespace fastrtps
}  // namespace eprosima
