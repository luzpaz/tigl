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

#include <cassert>
#include <CCPACSEnginePylon.h>
#include "CCPACSAircraftModel.h"
#include "CPACSEnginePylons.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSEnginePylons::CPACSEnginePylons(CCPACSAircraftModel* parent, CTiglUIDManager* uidMgr)
        : m_uidMgr(uidMgr)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSEnginePylons::~CPACSEnginePylons()
    {
    }

    const CCPACSAircraftModel* CPACSEnginePylons::GetParent() const
    {
        return m_parent;
    }

    CCPACSAircraftModel* CPACSEnginePylons::GetParent()
    {
        return m_parent;
    }

    CTiglUIDManager& CPACSEnginePylons::GetUIDManager()
    {
        return *m_uidMgr;
    }

    const CTiglUIDManager& CPACSEnginePylons::GetUIDManager() const
    {
        return *m_uidMgr;
    }

    void CPACSEnginePylons::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read element enginePylon
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/enginePylon")) {
            tixi::TixiReadElements(tixiHandle, xpath + "/enginePylon", m_enginePylons, reinterpret_cast<CCPACSEnginePylons*>(this), m_uidMgr);
        }

    }

    void CPACSEnginePylons::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write element enginePylon
        tixi::TixiSaveElements(tixiHandle, xpath + "/enginePylon", m_enginePylons);

    }

    const std::vector<unique_ptr<CCPACSEnginePylon> >& CPACSEnginePylons::GetEnginePylons() const
    {
        return m_enginePylons;
    }

    std::vector<unique_ptr<CCPACSEnginePylon> >& CPACSEnginePylons::GetEnginePylons()
    {
        return m_enginePylons;
    }

    CCPACSEnginePylon& CPACSEnginePylons::AddEnginePylon()
    {
        m_enginePylons.push_back(make_unique<CCPACSEnginePylon>(reinterpret_cast<CCPACSEnginePylons*>(this), m_uidMgr));
        return *m_enginePylons.back();
    }

    void CPACSEnginePylons::RemoveEnginePylon(CCPACSEnginePylon& ref)
    {
        for (std::size_t i = 0; i < m_enginePylons.size(); i++) {
            if (m_enginePylons[i].get() == &ref) {
                m_enginePylons.erase(m_enginePylons.begin() + i);
                return;
            }
        }
        throw CTiglError("Element not found");
    }

} // namespace generated
} // namespace tigl