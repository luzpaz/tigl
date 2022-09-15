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
#include "CCPACSFuselageWallSegment.h"
#include "CPACSWallSegment_phi.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDObject.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSWallSegment_phi::CPACSWallSegment_phi(CCPACSFuselageWallSegment* parent)
        : m_simpleContent(0)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSWallSegment_phi::~CPACSWallSegment_phi()
    {
    }

    const CCPACSFuselageWallSegment* CPACSWallSegment_phi::GetParent() const
    {
        return m_parent;
    }

    CCPACSFuselageWallSegment* CPACSWallSegment_phi::GetParent()
    {
        return m_parent;
    }

    const CTiglUIDObject* CPACSWallSegment_phi::GetNextUIDParent() const
    {
        if (m_parent) {
            if (m_parent->GetUID())
                return m_parent;
            else
                return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    CTiglUIDObject* CPACSWallSegment_phi::GetNextUIDParent()
    {
        if (m_parent) {
            if (m_parent->GetUID())
                return m_parent;
            else
                return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    void CPACSWallSegment_phi::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read simpleContent 
        if (tixi::TixiCheckElement(tixiHandle, xpath)) {
            m_simpleContent = tixi::TixiGetElement<double>(tixiHandle, xpath);
        }
        else {
            LOG(ERROR) << "Required simpleContent  is missing at xpath " << xpath;
        }

    }

    void CPACSWallSegment_phi::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write simpleContent 
        tixi::TixiSaveElement(tixiHandle, xpath, m_simpleContent);

    }

    const double& CPACSWallSegment_phi::GetSimpleContent() const
    {
        return m_simpleContent;
    }

    void CPACSWallSegment_phi::SetSimpleContent(const double& value)
    {
        m_simpleContent = value;
    }

} // namespace generated
} // namespace tigl