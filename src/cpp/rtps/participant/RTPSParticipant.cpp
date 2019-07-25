// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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
 * @file RTPSParticipant.cpp
 *
 */

#include <fastrtps/rtps/participant/RTPSParticipant.h>
#include "RTPSParticipantImpl.h"
#include <fastrtps/rtps/Endpoint.h>

namespace eprosima {
namespace fastrtps{
namespace rtps {

RTPSParticipant::RTPSParticipant(RTPSParticipantImpl* pimpl):mp_impl(pimpl)
{
}

RTPSParticipant::~RTPSParticipant()
{

}

const GUID_t& RTPSParticipant::getGuid() const
{
    return mp_impl->getGuid();
}

void RTPSParticipant::announceRTPSParticipantState()
{
    return mp_impl->announceRTPSParticipantState();
}

void RTPSParticipant::stopRTPSParticipantAnnouncement()
{
    return mp_impl->stopRTPSParticipantAnnouncement();
}

void RTPSParticipant::resetRTPSParticipantAnnouncement()
{
    return mp_impl->resetRTPSParticipantAnnouncement();
}

bool RTPSParticipant::newRemoteWriterDiscovered(const GUID_t& pguid, int16_t userDefinedId)
{
    return mp_impl->newRemoteEndpointDiscovered(pguid,userDefinedId, WRITER);
}
bool RTPSParticipant::newRemoteReaderDiscovered(const GUID_t& pguid, int16_t userDefinedId)
{
    return mp_impl->newRemoteEndpointDiscovered(pguid,userDefinedId, READER);
}
uint32_t RTPSParticipant::getRTPSParticipantID() const
{
    return mp_impl->getRTPSParticipantID();
}

bool RTPSParticipant::registerWriter(RTPSWriter* Writer, const TopicAttributes& topicAtt, const WriterQos& wqos)
{
    return mp_impl->registerWriter(Writer,topicAtt, wqos);
}

bool RTPSParticipant::registerReader(RTPSReader* Reader, const TopicAttributes& topicAtt, const ReaderQos& rqos)
{
    return mp_impl->registerReader(Reader,topicAtt, rqos);
}

bool RTPSParticipant::updateWriter(RTPSWriter* Writer, const TopicAttributes& topicAtt, const WriterQos& wqos)
{
    return mp_impl->updateLocalWriter(Writer, topicAtt, wqos);
}

bool RTPSParticipant::updateReader(RTPSReader* Reader, const TopicAttributes& topicAtt, const ReaderQos& rqos)
{
    return mp_impl->updateLocalReader(Reader, topicAtt, rqos);
}

std::vector<std::string> RTPSParticipant::getParticipantNames() const {
    return mp_impl->getParticipantNames();
}

const RTPSParticipantAttributes & RTPSParticipant::getRTPSParticipantAttributes() const {
    return mp_impl->getRTPSParticipantAttributes();
}

uint32_t RTPSParticipant::getMaxMessageSize() const
{
    return mp_impl->getMaxMessageSize();
}

uint32_t RTPSParticipant::getMaxDataSize() const
{
    return mp_impl->getMaxDataSize();
}

bool RTPSParticipant::get_remote_writer_info(const GUID_t& writerGuid, WriterProxyData& returnedInfo)
{
    return mp_impl->get_remote_writer_info(writerGuid, returnedInfo);
}

bool RTPSParticipant::get_remote_reader_info(const GUID_t& readerGuid, ReaderProxyData& returnedInfo)
{
    return mp_impl->get_remote_reader_info(readerGuid, returnedInfo);
}

ResourceEvent& RTPSParticipant::get_resource_event() const
{
    return mp_impl->getEventResource();
}

WLP* RTPSParticipant::wlp() const
{
    return mp_impl->wlp();
}

} /* namespace rtps */
} /* namespace fastrtps */
} /* namespace eprosima */

