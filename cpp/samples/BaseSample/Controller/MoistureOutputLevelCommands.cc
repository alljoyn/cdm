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

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "MoistureOutputLevelCommands.h"
#include "ControllerSample.h"

MoistureOutputLevelListener::MoistureOutputLevelListener()
{
}

MoistureOutputLevelListener::~MoistureOutputLevelListener()
{
}

void MoistureOutputLevelListener::OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MoistureOutputLevel: " << (int)value << endl;
}
void MoistureOutputLevelListener::OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxMoistureOutputLevel: " << (int)value << endl;
}
void MoistureOutputLevelListener::OnAutoModeChanged(const qcc::String& objectPath, const uint8_t autoMode)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "AutoMode: " << (int)autoMode << endl;
}

void MoistureOutputLevelListener::OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void MoistureOutputLevelListener::OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MoistureOutputLevel: " << (int)value << endl;
}

void MoistureOutputLevelListener::OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxMoistureOutputLevel: " << (int)value << endl;
}

void MoistureOutputLevelListener::OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void MoistureOutputLevelListener::OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t autoMode, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "AutoMode: " << (int)autoMode << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////

MoistureOutputLevelCommands::MoistureOutputLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

MoistureOutputLevelCommands::~MoistureOutputLevelCommands()
{
}

void MoistureOutputLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(MOISTURE_OUTPUT_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<MoistureOutputLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&MoistureOutputLevelCommands::OnCmdGetMoistureOutputLevel, "getmol", "Get MoistureOutputLevel");
    RegisterCommand(&MoistureOutputLevelCommands::OnCmdSetMoistureOutputLevel, "setmol", "Set MoistureOutputLevel");
    RegisterCommand(&MoistureOutputLevelCommands::OnCmdGetMaxMoistureOutputLevel, "getmmol", "Get MaxMoistureOutputLevel");
    RegisterCommand(&MoistureOutputLevelCommands::OnCmdGetAutoMode, "getmolam", "Get AutoMode");
    RegisterCommand(&MoistureOutputLevelCommands::OnCmdSetAutoMode, "setmolam", "Set AutoMode");

    PrintCommands();
}

void MoistureOutputLevelCommands::OnCmdGetMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfController* intfController = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMoistureOutputLevel();
}

void MoistureOutputLevelCommands::OnCmdSetMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfController* intfController = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetMoistureOutputLevel(value);
}

void MoistureOutputLevelCommands::OnCmdGetMaxMoistureOutputLevel(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfController* intfController = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxMoistureOutputLevel();
}

void MoistureOutputLevelCommands::OnCmdGetAutoMode(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfController* intfController = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetAutoMode();
}

void MoistureOutputLevelCommands::OnCmdSetAutoMode(Commands* commands, std::string& cmd)
{
    MoistureOutputLevelIntfController* intfController = static_cast<MoistureOutputLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 || value > 1) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetAutoMode(value);
}