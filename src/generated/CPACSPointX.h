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

#include <string>
#include <tixi.h>
#include <typeinfo>
#include "CTiglError.h"
#include "tigl_internal.h"

namespace tigl
{
class CTiglUIDManager;

namespace generated
{
    // This class is used in:
    // CPACSWingRibCell
    // CPACSWingRibCrossSection

    // generated from /xsd:schema/xsd:complexType[718]
    class CPACSPointX
    {
    public:
        TIGL_EXPORT CPACSPointX(CTiglUIDManager* uidMgr);
        TIGL_EXPORT virtual ~CPACSPointX();

        TIGL_EXPORT CTiglUIDManager& GetUIDManager();
        TIGL_EXPORT const CTiglUIDManager& GetUIDManager() const;

        TIGL_EXPORT virtual void ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath);
        TIGL_EXPORT virtual void WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const;

        TIGL_EXPORT virtual const std::string& GetUID() const;
        TIGL_EXPORT virtual void SetUID(const std::string& value);

        TIGL_EXPORT virtual const double& GetX() const;
        TIGL_EXPORT virtual void SetX(const double& value);

    protected:
        CTiglUIDManager* m_uidMgr;

        std::string m_uID;
        double      m_x;

    private:
#ifdef HAVE_CPP11
        CPACSPointX(const CPACSPointX&) = delete;
        CPACSPointX& operator=(const CPACSPointX&) = delete;

        CPACSPointX(CPACSPointX&&) = delete;
        CPACSPointX& operator=(CPACSPointX&&) = delete;
#else
        CPACSPointX(const CPACSPointX&);
        CPACSPointX& operator=(const CPACSPointX&);
#endif
    };
} // namespace generated

// Aliases in tigl namespace
#ifdef HAVE_CPP11
using CCPACSPointX = generated::CPACSPointX;
#else
typedef generated::CPACSPointX CCPACSPointX;
#endif
} // namespace tigl
