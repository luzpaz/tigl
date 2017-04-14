// Copyright (c) 2016 RISC Software GmbH
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

#include "CPACSProfileGeometry.h"
#include "CPACSWingAirfoils.h"
#include "CTiglError.h"
#include "CTiglLogging.h"
#include "TixiHelper.h"

namespace tigl
{
    namespace generated
    {
        CPACSWingAirfoils::CPACSWingAirfoils(){}
        CPACSWingAirfoils::~CPACSWingAirfoils() {}
        
        void CPACSWingAirfoils::ReadCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath)
        {
            // read element wingAirfoil
            if (tixihelper::TixiCheckElement(tixiHandle, xpath + "/wingAirfoil")) {
                tixihelper::TixiReadElements(tixiHandle, xpath + "/wingAirfoil", m_wingAirfoils);
            }
            
        }
        
        void CPACSWingAirfoils::WriteCPACS(const TixiDocumentHandle& tixiHandle, const std::string& xpath) const
        {
            // write element wingAirfoil
            tixihelper::TixiSaveElements(tixiHandle, xpath + "/wingAirfoil", m_wingAirfoils);
            
        }
        
        const std::vector<unique_ptr<CPACSProfileGeometry> >& CPACSWingAirfoils::GetWingAirfoils() const
        {
            return m_wingAirfoils;
        }
        
        std::vector<unique_ptr<CPACSProfileGeometry> >& CPACSWingAirfoils::GetWingAirfoils()
        {
            return m_wingAirfoils;
        }
        
    }
}