// Copyright (c) 2018 RISC Software GmbH
//
// This file was generated by CPACSGen from CPACS XML Schema (c) German Aerospace Center (DLR/SC).
// Do not edit, all changes are lost when files are re-generated.
//
// Licensed under the Apache License, Version 2.0 (the "License")
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

#pragma once

#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <CCPACSPositionings.h>
#include <CCPACSTransformation.h>
#include <CCPACSWingSections.h>
#include <CCPACSWingSegments.h>
#include <string>
#include <tixi.h>
#include "CreateIfNotExists.h"
#include "tigl_internal.h"

namespace tigl
{
class CTiglUIDManager;

namespace generated
{
    // This class is used in:
    // CPACSEnginePylons

    // generated from /xsd:schema/xsd:complexType[311]
    class CPACSEnginePylon
    {
    public:
        TIGL_EXPORT CPACSEnginePylon(CTiglUIDManager* uidMgr);
        TIGL_EXPORT virtual ~CPACSEnginePylon();

        TIGL_EXPORT CTiglUIDManager& GetUIDManager();
        TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;

        TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
        TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;

        TIGL_EXPORT virtual const boost::optional<std::string>& GetUID() const;
        TIGL_EXPORT virtual void SetUID(const boost::optional<std::string>& value);

        TIGL_EXPORT virtual const boost::optional<std::string>& GetName() const;
        TIGL_EXPORT virtual void SetName(const boost::optional<std::string>& value);

        TIGL_EXPORT virtual const boost::optional<std::string>& GetDescription() const;
        TIGL_EXPORT virtual void SetDescription(const boost::optional<std::string>& value);

        TIGL_EXPORT virtual const std::string& GetParentUID() const;
        TIGL_EXPORT virtual void SetParentUID(const std::string& value);

        TIGL_EXPORT virtual const CCPACSTransformation& GetTransformation() const;
        TIGL_EXPORT virtual CCPACSTransformation& GetTransformation();

        TIGL_EXPORT virtual const boost::optional<CCPACSWingSections>& GetSections() const;
        TIGL_EXPORT virtual boost::optional<CCPACSWingSections>& GetSections();

        TIGL_EXPORT virtual const boost::optional<CCPACSWingSegments>& GetSegments() const;
        TIGL_EXPORT virtual boost::optional<CCPACSWingSegments>& GetSegments();

        TIGL_EXPORT virtual const boost::optional<CCPACSPositionings>& GetPositionings() const;
        TIGL_EXPORT virtual boost::optional<CCPACSPositionings>& GetPositionings();

        TIGL_EXPORT virtual CCPACSWingSections& GetSections(CreateIfNotExistsTag);
        TIGL_EXPORT virtual void RemoveSections();

        TIGL_EXPORT virtual CCPACSWingSegments& GetSegments(CreateIfNotExistsTag);
        TIGL_EXPORT virtual void RemoveSegments();

        TIGL_EXPORT virtual CCPACSPositionings& GetPositionings(CreateIfNotExistsTag);
        TIGL_EXPORT virtual void RemovePositionings();

    protected:
        CTiglUIDManager* m_uidMgr;

        boost::optional<std::string>        m_uID;
        boost::optional<std::string>        m_name;
        boost::optional<std::string>        m_description;
        std::string                         m_parentUID;
        CCPACSTransformation                m_transformation;
        boost::optional<CCPACSWingSections> m_sections;
        boost::optional<CCPACSWingSegments> m_segments;
        boost::optional<CCPACSPositionings> m_positionings;

    private:
#ifdef HAVE_CPP11
        CPACSEnginePylon(const CPACSEnginePylon&) = delete;
        CPACSEnginePylon& operator=(const CPACSEnginePylon&) = delete;

        CPACSEnginePylon(CPACSEnginePylon&&) = delete;
        CPACSEnginePylon& operator=(CPACSEnginePylon&&) = delete;
#else
        CPACSEnginePylon(const CPACSEnginePylon&);
        CPACSEnginePylon& operator=(const CPACSEnginePylon&);
#endif
    };
} // namespace generated

// Aliases in tigl namespace
#ifdef HAVE_CPP11
using CCPACSEnginePylon = generated::CPACSEnginePylon;
#else
typedef generated::CPACSEnginePylon CCPACSEnginePylon;
#endif
} // namespace tigl
