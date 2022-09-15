// Copyright (c) 2020 RISC Software GmbH
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

#include <cassert>
#include "CPACSStandardProfile.h"
#include "CPACSSuperEllipseProfile.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDObject.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSSuperEllipseProfile::CPACSSuperEllipseProfile(CPACSStandardProfile* parent)
        : m_mUpper(this)
        , m_nUpper(this)
        , m_mLower(this)
        , m_nLower(this)
        , m_lowerHeightFraction(this)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSSuperEllipseProfile::~CPACSSuperEllipseProfile()
    {
    }

    const CPACSStandardProfile* CPACSSuperEllipseProfile::GetParent() const
    {
        return m_parent;
    }

    CPACSStandardProfile* CPACSSuperEllipseProfile::GetParent()
    {
        return m_parent;
    }

    const CTiglUIDObject* CPACSSuperEllipseProfile::GetNextUIDParent() const
    {
        if (m_parent) {
            return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    CTiglUIDObject* CPACSSuperEllipseProfile::GetNextUIDParent()
    {
        if (m_parent) {
            return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    void CPACSSuperEllipseProfile::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read element mUpper
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/mUpper")) {
            m_mUpper.ReadCPACS(tixiHandle, xpath + "/mUpper");
        }
        else {
            LOG(ERROR) << "Required element mUpper is missing at xpath " << xpath;
        }

        // read element nUpper
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/nUpper")) {
            m_nUpper.ReadCPACS(tixiHandle, xpath + "/nUpper");
        }
        else {
            LOG(ERROR) << "Required element nUpper is missing at xpath " << xpath;
        }

        // read element mLower
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/mLower")) {
            m_mLower.ReadCPACS(tixiHandle, xpath + "/mLower");
        }
        else {
            LOG(ERROR) << "Required element mLower is missing at xpath " << xpath;
        }

        // read element nLower
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/nLower")) {
            m_nLower.ReadCPACS(tixiHandle, xpath + "/nLower");
        }
        else {
            LOG(ERROR) << "Required element nLower is missing at xpath " << xpath;
        }

        // read element lowerHeightFraction
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/lowerHeightFraction")) {
            m_lowerHeightFraction.ReadCPACS(tixiHandle, xpath + "/lowerHeightFraction");
        }
        else {
            LOG(ERROR) << "Required element lowerHeightFraction is missing at xpath " << xpath;
        }

    }

    void CPACSSuperEllipseProfile::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write element mUpper
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/mUpper");
        m_mUpper.WriteCPACS(tixiHandle, xpath + "/mUpper");

        // write element nUpper
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/nUpper");
        m_nUpper.WriteCPACS(tixiHandle, xpath + "/nUpper");

        // write element mLower
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/mLower");
        m_mLower.WriteCPACS(tixiHandle, xpath + "/mLower");

        // write element nLower
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/nLower");
        m_nLower.WriteCPACS(tixiHandle, xpath + "/nLower");

        // write element lowerHeightFraction
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/lowerHeightFraction");
        m_lowerHeightFraction.WriteCPACS(tixiHandle, xpath + "/lowerHeightFraction");

    }

    const CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetMUpper() const
    {
        return m_mUpper;
    }

    CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetMUpper()
    {
        return m_mUpper;
    }

    const CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetNUpper() const
    {
        return m_nUpper;
    }

    CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetNUpper()
    {
        return m_nUpper;
    }

    const CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetMLower() const
    {
        return m_mLower;
    }

    CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetMLower()
    {
        return m_mLower;
    }

    const CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetNLower() const
    {
        return m_nLower;
    }

    CPACSPosExcl0DoubleBase& CPACSSuperEllipseProfile::GetNLower()
    {
        return m_nLower;
    }

    const CPACSSuperEllipseProfile_lowerHeightFraction& CPACSSuperEllipseProfile::GetLowerHeightFraction() const
    {
        return m_lowerHeightFraction;
    }

    CPACSSuperEllipseProfile_lowerHeightFraction& CPACSSuperEllipseProfile::GetLowerHeightFraction()
    {
        return m_lowerHeightFraction;
    }

} // namespace generated
} // namespace tigl