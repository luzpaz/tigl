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
#include "CPACSDoubleConstraintBase.h"
#include "CPACSPointPerformanceConstraints.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "CTiglUIDObject.h"
#include "TixiHelper.h"

namespace tigl
{
namespace generated
{
    CPACSDoubleConstraintBase::CPACSDoubleConstraintBase(CPACSPointPerformanceConstraints* parent)
        : m_simpleContent(0)
    {
        //assert(parent != NULL);
        m_parent = parent;
    }

    CPACSDoubleConstraintBase::~CPACSDoubleConstraintBase()
    {
    }

    const CPACSPointPerformanceConstraints* CPACSDoubleConstraintBase::GetParent() const
    {
        return m_parent;
    }

    CPACSPointPerformanceConstraints* CPACSDoubleConstraintBase::GetParent()
    {
        return m_parent;
    }

    const CTiglUIDObject* CPACSDoubleConstraintBase::GetNextUIDParent() const
    {
        if (m_parent) {
            return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    CTiglUIDObject* CPACSDoubleConstraintBase::GetNextUIDParent()
    {
        if (m_parent) {
            return m_parent->GetNextUIDParent();
        }
        return nullptr;
    }

    void CPACSDoubleConstraintBase::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
    {
        // read attribute relationalOperator
        if (tixi::TixiCheckAttribute(tixiHandle, xpath, "relationalOperator")) {
            m_relationalOperator = stringToCPACSRelationalOperator(tixi::TixiGetAttribute<std::string>(tixiHandle, xpath, "relationalOperator"));
        }
        else {
            LOG(ERROR) << "Required attribute relationalOperator is missing at xpath " << xpath;
        }

        // read simpleContent 
        if (tixi::TixiCheckElement(tixiHandle, xpath)) {
            m_simpleContent = tixi::TixiGetElement<double>(tixiHandle, xpath);
        }
        else {
            LOG(ERROR) << "Required simpleContent  is missing at xpath " << xpath;
        }

    }

    void CPACSDoubleConstraintBase::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
    {
        // write attribute relationalOperator
        tixi::TixiSaveAttribute(tixiHandle, xpath, "relationalOperator", CPACSRelationalOperatorToString(m_relationalOperator));

        // write simpleContent 
        tixi::TixiSaveElement(tixiHandle, xpath, m_simpleContent);

    }

    const CPACSRelationalOperator& CPACSDoubleConstraintBase::GetRelationalOperator() const
    {
        return m_relationalOperator;
    }

    void CPACSDoubleConstraintBase::SetRelationalOperator(const CPACSRelationalOperator& value)
    {
        m_relationalOperator = value;
    }

    const double& CPACSDoubleConstraintBase::GetSimpleContent() const
    {
        return m_simpleContent;
    }

    void CPACSDoubleConstraintBase::SetSimpleContent(const double& value)
    {
        m_simpleContent = value;
    }

} // namespace generated
} // namespace tigl
