/*
 * Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * Copyright 2019, Proyectos y Sistemas de Mantenimiento SL (eProsima).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OMG_DDS_CORE_XTYPES_T_UNION_TYPE_HPP_
#define OMG_DDS_CORE_XTYPES_T_UNION_TYPE_HPP_

#include <dds/core/xtypes/detail/UnionType.hpp>

#include <dds/core/xtypes/DynamicType.hpp>
#include <dds/core/xtypes/UnionCase.hpp>
#include <dds/core/xtypes/PrimitiveTypes.hpp>

#include <vector>

namespace dds{
namespace core{
namespace xtypes{

/**
 * Declares a forward declaration for a union type.
 */
template<typename DELEGATE>
class TUnionForwardDeclaration : public TDynamicType<DELEGATE>
{
public:
    TUnionForwardDeclaration(
            const std::string& name)
    {
        (void) name;
    }
};

template<
        typename T,
        template<typename> class DELEGATE>
class TUnionType  : public TDynamicType<DELEGATE<T>>
{
public:
    TUnionType(
        const std::string& name,
        const TPrimitiveType<T, DELEGATE<T>>& discriminator_type,
        const std::vector<UnionCase<T>>& cases)
    {
        (void) name;
        (void) discriminator_type;
        (void) cases;
    }

    TUnionType(
        const std::string& name,
        const TPrimitiveType<T, DELEGATE<T> >& discriminator_type,
        const std::vector<UnionCase<T>>& cases,
        const Annotation& annotation)
    {
        (void) name;
        (void) discriminator_type;
        (void) cases;
        (void) annotation;
    }

    TUnionType(
        const std::string& name,
        const TPrimitiveType<T, DELEGATE<T>>& discriminator_type,
        const std::vector<UnionCase<T>>& cases,
        const std::vector<Annotation>& annotations)
    {
        (void) name;
        (void) discriminator_type;
        (void) cases;
        (void) annotations;
    }

    const std::vector<UnionCase<T>>& members() const
    {
        const std::vector<UnionCase<T>> m;
        return m;
    }

    const MemberType& member(
            uint32_t id) const
    {
        (void) id;
        const MemberType m;
        return m;
    }

    const MemberType& member(
            const std::string& name) const
    {
        (void) name;
        const MemberType m;
        return m;
    }

    const std::vector<Annotation>& annotations() const
    {
        const std::vector<Annotation> v;
        return v;
    }

    TUnionType add_member(
            const UnionCase<T>& member) const
    {
    (void) member;
    }

    TUnionType remove_member(
            const UnionCase<T>& member) const
    {
    (void) member;
    }

    TUnionType add_annotation(
            const Annotation& annotation) const
    {
    (void) annotation;
    }

    TUnionType remove_annotation(
            const Annotation& annotation) const
    {
    (void) annotation;
    }
};

template<typename T>
class UnionType : public TUnionType<T, detail::UnionType> {};

} //namespace xtypes
} //namespace core
} //namespace dds

#endif //OMG_DDS_CORE_XTYPES_T_STRUCT_TYPE_HPP_