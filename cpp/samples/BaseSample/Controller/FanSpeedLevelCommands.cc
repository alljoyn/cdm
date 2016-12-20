/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "FanSpeedLevelCommands.h"
#include "ControllerSample.h"

FanSpeedLevelListener::FanSpeedLevelListener()
{
}

FanSpeedLevelListener::~FanSpeedLevelListener()
{
}

void FanSpeedLevelListener::OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    printf("FanSpeedLevel: %d \n",  value);
}

void FanSpeedLevelListener::OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void FanSpeedLevelListener::OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    printf("MaxFanSpeedLevel: %d \n",  value);
}

void FanSpeedLevelListener::OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    printf("AutoMode: %d \n",  value);
}

void FanSpeedLevelListener::OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void FanSpeedLevelListener::OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    printf("FanSpeedLevel: %d \n",  value);
}

void FanSpeedLevelListener::OnAutoModeChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    printf("AutoMode: %d \n",  value);
}


FanSpeedLevelCommands::FanSpeedLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

FanSpeedLevelCommands::~FanSpeedLevelCommands()
{
}

void FanSpeedLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(FAN_SPEED_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<FanSpeedLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&FanSpeedLevelCommands::OnCmdGetFanSpeedLevel, "getfsl", "Get FanSpeedLevel");
    RegisterCommand(&FanSpeedLevelCommands::OnCmdSetFanSpeedLevel, "setfsl", "Set FanSpeedLevel");
    RegisterCommand(&FanSpeedLevelCommands::OnCmdGetMaxFanSpeedLevel, "getmfsl", "Get MaxFanSpeedLevel");
    RegisterCommand(&FanSpeedLevelCommands::OnCmdGetAutoMode, "getam", "Get AutoMode");
    RegisterCommand(&FanSpeedLevelCommands::OnCmdSetAutoMode, "setam", "Set AutoMode");

    PrintCommands();
}

void FanSpeedLevelCommands::OnCmdGetFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfController* intfController = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetFanSpeedLevel();
}

void FanSpeedLevelCommands::OnCmdSetFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfController* intfController = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 ) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetFanSpeedLevel(value);
}

void FanSpeedLevelCommands::OnCmdGetMaxFanSpeedLevel(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfController* intfController = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxFanSpeedLevel();
}

void FanSpeedLevelCommands::OnCmdGetAutoMode(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfController* intfController = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetAutoMode();
}

void FanSpeedLevelCommands::OnCmdSetAutoMode(Commands* commands, std::string& cmd)
{
    FanSpeedLevelIntfController* intfController = static_cast<FanSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 ) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetAutoMode(value);
}

