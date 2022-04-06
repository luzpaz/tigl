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
#include <CCPACSDuctAssembly.h>
#include "CCPACSAircraftModel.h"
#include "CPACSDucts.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "CTiglUIDObject.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSDucts::CPACSDucts(CCPACSAircraftModel* parent, CTiglUIDManager* uidMgr)
        : m_uidMgr(uidMgr)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSDucts::~CPACSDucts()
    {
    }

    const CCPACSAircraftModel* CPACSDucts::GetParent() const
    {
        return m_parent;
    }

    CCPACSAircraftModel* CPACSDucts::GetParent()
    {
        return m_parent;
    }

    const CTiglUIDObject* CPACSDucts::GetNextUIDParent() const
    {
        return m_parent;
    }

    CTiglUIDObject* CPACSDucts::GetNextUIDParent()
    {
        return m_parent;
    }

    CTiglUIDManager& CPACSDucts::GetUIDManager()
    {
        return *m_uidMgr;
    }

    const CTiglUIDManager& CPACSDucts::GetUIDManager() const
    {
        return *m_uidMgr;
    }

    void CPACSDucts::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read element ductAssembly
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/ductAssembly")) {
            tixi::TixiReadElements(tixiHandle, xpath + "/ductAssembly", m_ductAssemblys, 1, tixi::xsdUnbounded, this, m_uidMgr);
        }

    }

    void CPACSDucts::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write element ductAssembly
        tixi::TixiSaveElements(tixiHandle, xpath + "/ductAssembly", m_ductAssemblys);

    }

    const std::vector<std::unique_ptr<CCPACSDuctAssembly>>& CPACSDucts::GetDuctAssemblys() const
    {
        return m_ductAssemblys;
    }

    std::vector<std::unique_ptr<CCPACSDuctAssembly>>& CPACSDucts::GetDuctAssemblys()
    {
        return m_ductAssemblys;
    }

    CCPACSDuctAssembly& CPACSDucts::AddDuctAssembly()
    {
        m_ductAssemblys.push_back(make_unique<CCPACSDuctAssembly>(this, m_uidMgr));
        return *m_ductAssemblys.back();
    }

    void CPACSDucts::RemoveDuctAssembly(CCPACSDuctAssembly& ref)
    {
        for (std::size_t i = 0; i < m_ductAssemblys.size(); i++) {
            if (m_ductAssemblys[i].get() == &ref) {
                m_ductAssemblys.erase(m_ductAssemblys.begin() + i);
                return;
            }
        }
        throw CTiglError("Element not found");
    }

} // namespace generated
} // namespace tigl
