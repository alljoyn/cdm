/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include "HeatingZoneListener.h"
#include "ControlleeSample.h"

using namespace std;


QStatus HeatingZoneListener::OnGetNumberOfHeatingZones(uint8_t& currentState)
{
    cout << "HeatingZoneListener::OnGetNumberOfHeatingZones()" << endl;
    return ER_OK;
}
QStatus HeatingZoneListener::OnGetMaxHeatingLevels(std::vector<uint8_t>& maxHeatingLevels)
{
    cout << "HeatingZoneListener::OnGetMaxHeatingLevels()" << endl;
    return ER_OK;
}
QStatus HeatingZoneListener::OnGetHeatingLevels(std::vector<uint8_t>& heatingLevels)
{
    cout << "HeatingZoneListener::OnGetHeatingLevels()" << endl;
    return ER_OK;
}


ControlleeCommands* HeatingZoneCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new HeatingZoneCommands(sample, objectPath);
}

HeatingZoneCommands::HeatingZoneCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

HeatingZoneCommands::~HeatingZoneCommands()
{
}

void HeatingZoneCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(HEATING_ZONE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<HeatingZoneIntfControllee*>(cdmInterface);

        RegisterCommand(&HeatingZoneCommands::OnCmdGetNumberOfHeatingZones, "gnhz", "get number of heating zones");
        RegisterCommand(&HeatingZoneCommands::OnCmdSetNumberOfHeatingZones, "snhz", "set number of heating zones (use 'snhz <number of heating zones>')");

        RegisterCommand(&HeatingZoneCommands::OnCmdGetMaxHeatingLevels, "gmhl", "get max heating levels");
        RegisterCommand(&HeatingZoneCommands::OnCmdGetHeatingLevels, "ghl", "get heating levels");

    } else {
        PrintCommands();
    }
}

void HeatingZoneCommands::InitializeProperties()
{
    if (m_intfControllee) {

        uint8_t numberOfZones = 4;
        std::vector<uint8_t> maxHeatingLevels;
        std::vector<uint8_t> heatingLevels;

        for(uint8_t i =0; i < numberOfZones; i ++)
        {
            maxHeatingLevels.push_back(6);
            heatingLevels.push_back(0);
        }

        m_intfControllee->SetNumberOfHeatingZones(numberOfZones);
        m_intfControllee->SetMaxHeatingLevels(maxHeatingLevels);
        m_intfControllee->SetHeatingLevels(heatingLevels);
    }
}


void HeatingZoneCommands::OnCmdGetNumberOfHeatingZones(Commands* commands, std::string& cmd)
{

    HeatingZoneIntfControllee* intfControllee = static_cast<HeatingZoneCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetNumberOfHeatingZones() << endl;
}
void HeatingZoneCommands::OnCmdSetNumberOfHeatingZones(Commands* commands, std::string& cmd)
{
    HeatingZoneIntfControllee* intfControllee = static_cast<HeatingZoneCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t numberOfZones = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetNumberOfHeatingZones(numberOfZones);
}

void HeatingZoneCommands::OnCmdGetMaxHeatingLevels(Commands* commands, std::string& cmd)
{
    HeatingZoneIntfControllee* intfControllee = static_cast<HeatingZoneCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    std::vector<uint8_t> maxHeatingLevels = intfControllee->GetMaxHeatingLevels();
    for(size_t i = 0 ; i < maxHeatingLevels.size(); i ++)
        cout << (int)maxHeatingLevels[i] << " ";
    cout << endl;

}
void HeatingZoneCommands::OnCmdGetHeatingLevels(Commands* commands, std::string& cmd)
{
    HeatingZoneIntfControllee* intfControllee = static_cast<HeatingZoneCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    std::vector<uint8_t> heatingLevels = intfControllee->GetHeatingLevels();
    for(size_t i = 0 ; i < heatingLevels.size(); i ++)
        cout << (int)heatingLevels[i] << " ";
    cout << endl;
}