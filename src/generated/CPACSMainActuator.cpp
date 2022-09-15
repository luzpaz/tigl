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
#include "CPACSLandingGearComponentAssembly.h"
#include "CPACSMainActuator.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSMainActuator::CPACSMainActuator(CPACSLandingGearComponentAssembly* parent, CTiglUIDManager* uidMgr)
        : m_uidMgr(uidMgr)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSMainActuator::~CPACSMainActuator()
    {
        if (m_uidMgr) m_uidMgr->TryUnregisterObject(m_uID);
        if (m_uidMgr) {
            if (!m_actuatorUID.empty()) m_uidMgr->TryUnregisterReference(m_actuatorUID, *this);
        }
    }

    const CPACSLandingGearComponentAssembly* CPACSMainActuator::GetParent() const
    {
        return m_parent;
    }

    CPACSLandingGearComponentAssembly* CPACSMainActuator::GetParent()
    {
        return m_parent;
    }

    const CTiglUIDObject* CPACSMainActuator::GetNextUIDParent() const
    {
        if (m_parent) {
            return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    CTiglUIDObject* CPACSMainActuator::GetNextUIDParent()
    {
        if (m_parent) {
            return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    CTiglUIDManager& CPACSMainActuator::GetUIDManager()
    {
        if (!m_uidMgr) {
            throw CTiglError("UIDManager is null");
        }
        return *m_uidMgr;
    }

    const CTiglUIDManager& CPACSMainActuator::GetUIDManager() const
    {
        if (!m_uidMgr) {
            throw CTiglError("UIDManager is null");
        }
        return *m_uidMgr;
    }

    void CPACSMainActuator::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read attribute uID
        if (tixi::TixiCheckAttribute(tixiHandle, xpath, "uID")) {
            m_uID = tixi::TixiGetAttribute<std::string>(tixiHandle, xpath, "uID");
            if (m_uID.empty()) {
                LOG(WARNING) << "Required attribute uID is empty at xpath " << xpath;
            }
        }
        else {
            LOG(ERROR) << "Required attribute uID is missing at xpath " << xpath;
        }

        // read element actuatorUID
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/actuatorUID")) {
            m_actuatorUID = tixi::TixiGetElement<std::string>(tixiHandle, xpath + "/actuatorUID");
            if (m_actuatorUID.empty()) {
                LOG(WARNING) << "Required element actuatorUID is empty at xpath " << xpath;
            }
            if (m_uidMgr && !m_actuatorUID.empty()) m_uidMgr->RegisterReference(m_actuatorUID, *this);
        }
        else {
            LOG(ERROR) << "Required element actuatorUID is missing at xpath " << xpath;
        }

        if (m_uidMgr && !m_uID.empty()) m_uidMgr->RegisterObject(m_uID, *this);
    }

    void CPACSMainActuator::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write attribute uID
        tixi::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);

        // write element actuatorUID
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/actuatorUID");
        tixi::TixiSaveElement(tixiHandle, xpath + "/actuatorUID", m_actuatorUID);

    }

    const std::string& CPACSMainActuator::GetUID() const
    {
        return m_uID;
    }

    void CPACSMainActuator::SetUID(const std::string& value)
    {
        if (m_uidMgr && value != m_uID) {
            if (m_uID.empty()) {
                m_uidMgr->RegisterObject(value, *this);
            }
            else {
                m_uidMgr->UpdateObjectUID(m_uID, value);
            }
        }
        m_uID = value;
    }

    const std::string& CPACSMainActuator::GetActuatorUID() const
    {
        return m_actuatorUID;
    }

    void CPACSMainActuator::SetActuatorUID(const std::string& value)
    {
        if (m_uidMgr) {
            if (!m_actuatorUID.empty()) m_uidMgr->TryUnregisterReference(m_actuatorUID, *this);
            if (!value.empty()) m_uidMgr->RegisterReference(value, *this);
        }
        m_actuatorUID = value;
    }

    const CTiglUIDObject* CPACSMainActuator::GetNextUIDObject() const
    {
        return this;
    }

    void CPACSMainActuator::NotifyUIDChange(const std::string& oldUid, const std::string& newUid)
    {
        if (m_actuatorUID == oldUid) {
            m_actuatorUID = newUid;
        }
    }

} // namespace generated
} // namespace tigl