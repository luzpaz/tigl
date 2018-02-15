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

#include "CPACSSparCell.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDManager.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSSparCell::CPACSSparCell(CTiglUIDManager* uidMgr)
        : m_uidMgr(uidMgr)
        , m_rotation(0)
    {
    }

    CPACSSparCell::~CPACSSparCell()
    {
        if (m_uidMgr) m_uidMgr->TryUnregisterObject(m_uID);
    }

    CTiglUIDManager& CPACSSparCell::GetUIDManager()
    {
        return *m_uidMgr;
    }

    const CTiglUIDManager& CPACSSparCell::GetUIDManager() const
    {
        return *m_uidMgr;
    }

    void CPACSSparCell::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
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

        // read element fromEta
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/fromEta")) {
            m_fromEta.ReadCPACS(tixiHandle, xpath + "/fromEta");
        }
        else {
            LOG(ERROR) << "Required element fromEta is missing at xpath " << xpath;
        }

        // read element toEta
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/toEta")) {
            m_toEta.ReadCPACS(tixiHandle, xpath + "/toEta");
        }
        else {
            LOG(ERROR) << "Required element toEta is missing at xpath " << xpath;
        }

        // read element upperCap
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/upperCap")) {
            m_upperCap.ReadCPACS(tixiHandle, xpath + "/upperCap");
        }
        else {
            LOG(ERROR) << "Required element upperCap is missing at xpath " << xpath;
        }

        // read element lowerCap
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/lowerCap")) {
            m_lowerCap.ReadCPACS(tixiHandle, xpath + "/lowerCap");
        }
        else {
            LOG(ERROR) << "Required element lowerCap is missing at xpath " << xpath;
        }

        // read element web1
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/web1")) {
            m_web1.ReadCPACS(tixiHandle, xpath + "/web1");
        }
        else {
            LOG(ERROR) << "Required element web1 is missing at xpath " << xpath;
        }

        // read element web2
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/web2")) {
            m_web2 = boost::in_place();
            try {
                m_web2->ReadCPACS(tixiHandle, xpath + "/web2");
            } catch(const std::exception& e) {
                LOG(ERROR) << "Failed to read web2 at xpath " << xpath << ": " << e.what();
                m_web2 = boost::none;
            }
        }

        // read element rotation
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/rotation")) {
            m_rotation = tixi::TixiGetElement<double>(tixiHandle, xpath + "/rotation");
        }
        else {
            LOG(ERROR) << "Required element rotation is missing at xpath " << xpath;
        }

        if (m_uidMgr && !m_uID.empty()) m_uidMgr->RegisterObject(m_uID, *this);
    }

    void CPACSSparCell::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write attribute uID
        tixi::TixiSaveAttribute(tixiHandle, xpath, "uID", m_uID);

        // write element fromEta
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/fromEta");
        m_fromEta.WriteCPACS(tixiHandle, xpath + "/fromEta");

        // write element toEta
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/toEta");
        m_toEta.WriteCPACS(tixiHandle, xpath + "/toEta");

        // write element upperCap
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/upperCap");
        m_upperCap.WriteCPACS(tixiHandle, xpath + "/upperCap");

        // write element lowerCap
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/lowerCap");
        m_lowerCap.WriteCPACS(tixiHandle, xpath + "/lowerCap");

        // write element web1
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/web1");
        m_web1.WriteCPACS(tixiHandle, xpath + "/web1");

        // write element web2
        if (m_web2) {
            tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/web2");
            m_web2->WriteCPACS(tixiHandle, xpath + "/web2");
        }
        else {
            if (tixi::TixiCheckElement(tixiHandle, xpath + "/web2")) {
                tixi::TixiRemoveElement(tixiHandle, xpath + "/web2");
            }
        }

        // write element rotation
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/rotation");
        tixi::TixiSaveElement(tixiHandle, xpath + "/rotation", m_rotation);

    }

    const std::string& CPACSSparCell::GetUID() const
    {
        return m_uID;
    }

    void CPACSSparCell::SetUID(const std::string& value)
    {
        if (m_uidMgr) {
            m_uidMgr->TryUnregisterObject(m_uID);
            m_uidMgr->RegisterObject(value, *this);
        }
        m_uID = value;
    }

    const CPACSEtaIsoLine& CPACSSparCell::GetFromEta() const
    {
        return m_fromEta;
    }

    CPACSEtaIsoLine& CPACSSparCell::GetFromEta()
    {
        return m_fromEta;
    }

    const CPACSEtaIsoLine& CPACSSparCell::GetToEta() const
    {
        return m_toEta;
    }

    CPACSEtaIsoLine& CPACSSparCell::GetToEta()
    {
        return m_toEta;
    }

    const CPACSCap& CPACSSparCell::GetUpperCap() const
    {
        return m_upperCap;
    }

    CPACSCap& CPACSSparCell::GetUpperCap()
    {
        return m_upperCap;
    }

    const CPACSCap& CPACSSparCell::GetLowerCap() const
    {
        return m_lowerCap;
    }

    CPACSCap& CPACSSparCell::GetLowerCap()
    {
        return m_lowerCap;
    }

    const CPACSWeb& CPACSSparCell::GetWeb1() const
    {
        return m_web1;
    }

    CPACSWeb& CPACSSparCell::GetWeb1()
    {
        return m_web1;
    }

    const boost::optional<CPACSWeb>& CPACSSparCell::GetWeb2() const
    {
        return m_web2;
    }

    boost::optional<CPACSWeb>& CPACSSparCell::GetWeb2()
    {
        return m_web2;
    }

    const double& CPACSSparCell::GetRotation() const
    {
        return m_rotation;
    }

    void CPACSSparCell::SetRotation(const double& value)
    {
        m_rotation = value;
    }

    CPACSWeb& CPACSSparCell::GetWeb2(CreateIfNotExistsTag)
    {
        if (!m_web2)
            m_web2 = boost::in_place();
        return *m_web2;
    }

    void CPACSSparCell::RemoveWeb2()
    {
        m_web2 = boost::none;
    }

} // namespace generated
} // namespace tigl
