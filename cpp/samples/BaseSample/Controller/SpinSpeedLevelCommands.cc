/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "SpinSpeedLevelCommands.h"
#include "ControllerSample.h"

SpinSpeedLevelListener::SpinSpeedLevelListener()
{
}

SpinSpeedLevelListener::~SpinSpeedLevelListener()
{
}


void SpinSpeedLevelListener::MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "maxLevel: " << (int)maxLevel << endl;
}


void SpinSpeedLevelListener::GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "objectPath: " << objectPath << endl;
    cout << "maxLevel: " << (int)maxLevel << endl;
}

void SpinSpeedLevelListener::GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "objectPath: " << objectPath << endl;
    cout << "targetLevel: " << (int)targetLevel << endl;
}

void SpinSpeedLevelListener::SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "objectPath: " << objectPath << endl;
}

void SpinSpeedLevelListener::GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "objectPath: " << objectPath << endl;
    cout << "selectable levels: " << endl;
    for (size_t i = 0; i < selectableLevels.size(); ++i) {
        cout << (int)selectableLevels[i] << endl;
    }
}

void SpinSpeedLevelListener::TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel)
{
    cout << "# "<< __func__ << endl;
    cout << "objectPath: " << objectPath << endl;
    cout << "targetLevel: " << (int)targetLevel << endl;
}

void SpinSpeedLevelListener::SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels)
{
    cout << "# "<< __func__ << endl;
    cout << "objectPath: " << objectPath << endl;
    for (size_t i = 0; i < selectableLevels.size(); ++i) {
        cout << (int)selectableLevels[i] << endl;
    }
}



SpinSpeedLevelCommands::SpinSpeedLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

SpinSpeedLevelCommands::~SpinSpeedLevelCommands()
{

}

void SpinSpeedLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(SPIN_SPEED_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<SpinSpeedLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&SpinSpeedLevelCommands::OnCmdGetMaxLevel, "gml", "get max spin speed level");
    RegisterCommand(&SpinSpeedLevelCommands::OnCmdGetTargetLevel, "gtl", "get target spin speed level");
    RegisterCommand(&SpinSpeedLevelCommands::OnCmdSetTargetLevel, "stl", "set target spin speed level");
    RegisterCommand(&SpinSpeedLevelCommands::OnCmdGetSelectableLevels, "gsl", "get selectable levels");
    PrintCommands();
}


void SpinSpeedLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    SpinSpeedLevelIntfController* intfController = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetMaxLevel();
}

void SpinSpeedLevelCommands::OnCmdGetSelectableLevels(Commands* commands, std::string& cmd)
{
    SpinSpeedLevelIntfController* intfController = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSelectableLevels();
}
void SpinSpeedLevelCommands::OnCmdGetTargetLevel(Commands* commands, std::string& cmd)
{
    SpinSpeedLevelIntfController* intfController = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetLevel();
}
void SpinSpeedLevelCommands::OnCmdSetTargetLevel(Commands* commands, std::string& cmd)
{
    SpinSpeedLevelIntfController* intfController = static_cast<SpinSpeedLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    int level = strtol(cmd.c_str(), NULL, 10);
    if (level < 0 || level >= 256) {
        cout << "Input argument is wrong." << endl;
        return;
    }

    intfController->SetTargetLevel(level);
}
