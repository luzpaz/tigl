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
#include "CPACSLandingGearSteeringFunction.h"
#include "CPACSLandingGearSteeringFunctionStep.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDObject.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSLandingGearSteeringFunctionStep::CPACSLandingGearSteeringFunctionStep(CPACSLandingGearSteeringFunction* parent)
        : m_controlParameter(0)
        , m_steeringAngle(0)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSLandingGearSteeringFunctionStep::~CPACSLandingGearSteeringFunctionStep()
    {
    }

    const CPACSLandingGearSteeringFunction* CPACSLandingGearSteeringFunctionStep::GetParent() const
    {
        return m_parent;
    }

    CPACSLandingGearSteeringFunction* CPACSLandingGearSteeringFunctionStep::GetParent()
    {
        return m_parent;
    }

    const CTiglUIDObject* CPACSLandingGearSteeringFunctionStep::GetNextUIDParent() const
    {
        return m_parent;
    }

    CTiglUIDObject* CPACSLandingGearSteeringFunctionStep::GetNextUIDParent()
    {
        return m_parent;
    }

    void CPACSLandingGearSteeringFunctionStep::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read element stepType
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/stepType")) {
            m_stepType = stringToCPACSLandingGearSteeringFunctionStep_stepType(tixi::TixiGetElement<std::string>(tixiHandle, xpath + "/stepType"));
        }
        else {
            LOG(ERROR) << "Required element stepType is missing at xpath " << xpath;
        }

        // read element controlParameter
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/controlParameter")) {
            m_controlParameter = tixi::TixiGetElement<double>(tixiHandle, xpath + "/controlParameter");
        }
        else {
            LOG(ERROR) << "Required element controlParameter is missing at xpath " << xpath;
        }

        // read element steeringAngle
        if (tixi::TixiCheckElement(tixiHandle, xpath + "/steeringAngle")) {
            m_steeringAngle = tixi::TixiGetElement<double>(tixiHandle, xpath + "/steeringAngle");
        }
        else {
            LOG(ERROR) << "Required element steeringAngle is missing at xpath " << xpath;
        }

    }

    void CPACSLandingGearSteeringFunctionStep::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write element stepType
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/stepType");
        tixi::TixiSaveElement(tixiHandle, xpath + "/stepType", CPACSLandingGearSteeringFunctionStep_stepTypeToString(m_stepType));

        // write element controlParameter
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/controlParameter");
        tixi::TixiSaveElement(tixiHandle, xpath + "/controlParameter", m_controlParameter);

        // write element steeringAngle
        tixi::TixiCreateElementIfNotExists(tixiHandle, xpath + "/steeringAngle");
        tixi::TixiSaveElement(tixiHandle, xpath + "/steeringAngle", m_steeringAngle);

    }

    const CPACSLandingGearSteeringFunctionStep_stepType& CPACSLandingGearSteeringFunctionStep::GetStepType() const
    {
        return m_stepType;
    }

    void CPACSLandingGearSteeringFunctionStep::SetStepType(const CPACSLandingGearSteeringFunctionStep_stepType& value)
    {
        m_stepType = value;
    }

    const double& CPACSLandingGearSteeringFunctionStep::GetControlParameter() const
    {
        return m_controlParameter;
    }

    void CPACSLandingGearSteeringFunctionStep::SetControlParameter(const double& value)
    {
        m_controlParameter = value;
    }

    const double& CPACSLandingGearSteeringFunctionStep::GetSteeringAngle() const
    {
        return m_steeringAngle;
    }

    void CPACSLandingGearSteeringFunctionStep::SetSteeringAngle(const double& value)
    {
        m_steeringAngle = value;
    }

} // namespace generated
} // namespace tigl