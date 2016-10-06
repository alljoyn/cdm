/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "HeatingZoneCommands.h"
#include "ControllerSample.h"

HeatingZoneListener::HeatingZoneListener()
{
}

HeatingZoneListener::~HeatingZoneListener()
{
}


void HeatingZoneListener::OnGetNumberOfHeatingZonesPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t numberOfZones, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# number of heating zones: " << (int) numberOfZones << endl;
}
void HeatingZoneListener::OnGetMaxHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# max heating levels: " << endl;
    for (size_t i = 0 ; i < maxHeatingLevels.size() ; i++)
    {
        cout << "# max level: " << (int)maxHeatingLevels[i] << endl;
    }
}
void HeatingZoneListener::OnGetHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# heating levels: " << endl;
    for (size_t i = 0 ; i < heatingLevels.size() ; i++)
    {
        cout << "# level: " << (int)heatingLevels[i] << endl;
    }
}
void HeatingZoneListener::NumberOfHeatingZonesPropertyChanged(const qcc::String& objectPath, const uint8_t numberOfHeatingZones)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# number of heating zones: " << (int) numberOfHeatingZones << endl;
}
void HeatingZoneListener::MaxHeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# max heating levels: " << endl;
    for (size_t i = 0 ; i < maxHeatingLevels.size() ; i++)
    {
        cout << "# max level: " << (int)maxHeatingLevels[i] << endl;
    }
}
void HeatingZoneListener::HeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# heating levels: " << endl;
    for (size_t i = 0 ; i < heatingLevels.size() ; i++)
    {
        cout << "# level: " << (int)heatingLevels[i] << endl;
    }
}

HeatingZoneCommands::HeatingZoneCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

HeatingZoneCommands::~HeatingZoneCommands()
{

}

void HeatingZoneCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(HEATING_ZONE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<HeatingZoneIntfController*>(cdmInterface);
    }

    RegisterCommand(&HeatingZoneCommands::OnCmdGetNumberOfHeatingZones, "gnhz", "get number opf heating zones");
    RegisterCommand(&HeatingZoneCommands::OnCmdGetMaxHeatingLevels, "gmhl", "get max heating levels");
    RegisterCommand(&HeatingZoneCommands::OnCmdGetHeatingLevels, "ghl", "get get heating levels");
    PrintCommands();
}


void HeatingZoneCommands::OnCmdGetHeatingLevels(Commands * commands, std::string& cmd)
{
    HeatingZoneIntfController* intfController = static_cast<HeatingZoneCommands*>(commands)->GetInterface();
    if(!intfController)
    {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetHeatingLevels();
}

void HeatingZoneCommands::OnCmdGetMaxHeatingLevels(Commands * commands, std::string& cmd)
{
    HeatingZoneIntfController* intfController = static_cast<HeatingZoneCommands*>(commands)->GetInterface();
    if(!intfController)
    {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxHeatingLevels();
}

void HeatingZoneCommands::OnCmdGetNumberOfHeatingZones(Commands * commands, std::string& cmd)
{
    HeatingZoneIntfController* intfController = static_cast<HeatingZoneCommands*>(commands)->GetInterface();
    if(!intfController)
    {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetNumberOfHeatingZones();
}