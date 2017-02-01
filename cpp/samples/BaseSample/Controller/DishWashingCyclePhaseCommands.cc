/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *    
 *    SPDX-License-Identifier: Apache-2.0
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *    
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/

#include "DishWashingCyclePhaseCommands.h"
#include "ControllerSample.h"

DishWashingCyclePhaseListener::DishWashingCyclePhaseListener()
{
}

DishWashingCyclePhaseListener::~DishWashingCyclePhaseListener()
{
}


void DishWashingCyclePhaseListener::OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# cyclePhase: " << (int)cyclePhase << endl;
}

void DishWashingCyclePhaseListener::OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported cycle phases: " << endl;
    for(size_t i = 0 ; i < listOfCyclePhases.size(); i++)
        cout << (int)listOfCyclePhases[i] << endl;
}

void DishWashingCyclePhaseListener::OnCyclePhasePropertyChanged(const qcc::String& objectPath, const uint8_t cyclePhase)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# cyclePhase: " << (int)cyclePhase << endl;
}

void DishWashingCyclePhaseListener::OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const DishWashingCyclePhaseInterface::SupportedCyclePhases listOfCyclePhases)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported cycle phases: " << endl;
    for(size_t i = 0 ; i < listOfCyclePhases.size(); i++)
        cout << (int)listOfCyclePhases[i] << endl;
}

void DishWashingCyclePhaseListener::OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const DishWashingCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions, void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# phase descs: " << endl;
    cout << "Status: " << QCC_StatusText(status) << endl;
    if(status != ER_OK)
    {
        cout << "error name: " << errorName << endl;
        cout << "error mess: " << errorMessage << endl;
    }
    for(size_t i = 0 ; i < listOfCycleDescriptions.size(); i++)
        cout << (int)listOfCycleDescriptions[i].phase << " " << listOfCycleDescriptions[i].name << " " << listOfCycleDescriptions[i].description<<endl;
}

DishWashingCyclePhaseCommands::DishWashingCyclePhaseCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

DishWashingCyclePhaseCommands::~DishWashingCyclePhaseCommands()
{

}

void DishWashingCyclePhaseCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(DISH_WASHING_CYCLE_PHASE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<DishWashingCyclePhaseIntfController*>(cdmInterface);
    }

    RegisterCommand(&DishWashingCyclePhaseCommands::OnCmdGetCyclePhase, "gcp", "get cycle phase");
    RegisterCommand(&DishWashingCyclePhaseCommands::OnCmdGetSupportedCyclePhases, "gscp", "get supported cycle phases");
    RegisterCommand(&DishWashingCyclePhaseCommands::OnCmdGetCyclePhasesDescriptions, "gcpd", "get cycle phase descriptions");
    PrintCommands();
}
void DishWashingCyclePhaseCommands::OnCmdGetCyclePhase(Commands* commands, std::string& cmd)
{
    DishWashingCyclePhaseIntfController* intfController = static_cast<DishWashingCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCyclePhase();
}

void DishWashingCyclePhaseCommands::OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd)
{
    DishWashingCyclePhaseIntfController* intfController = static_cast<DishWashingCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedCyclePhases();
}

void DishWashingCyclePhaseCommands::OnCmdGetCyclePhasesDescriptions(Commands* commands, std::string& cmd)
{
    DishWashingCyclePhaseIntfController* intfController = static_cast<DishWashingCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << "Command string: " << cmd.c_str() << endl;
    intfController->GetCyclePhasesDescriptions(cmd.c_str());
}