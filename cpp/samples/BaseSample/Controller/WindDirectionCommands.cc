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

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "WindDirectionCommands.h"
#include "ControllerSample.h"

WindDirectionListener::WindDirectionListener()
{
}

WindDirectionListener::~WindDirectionListener()
{
}

void WindDirectionListener::OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void WindDirectionListener::OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "HorizontalMax: " << value << endl;
}

void WindDirectionListener::OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void WindDirectionListener::OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    printf("HorizontalAutoMode: %d\n", value);
}

void WindDirectionListener::OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void WindDirectionListener::OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "VerticalDirection: " << value << endl;
}

void WindDirectionListener::OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "VerticalMax: " << value << endl;
}

void WindDirectionListener::OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void WindDirectionListener::OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    printf("VerticalAutoMode: %d\n", value);
}

//////////////////////////////////////////////////////////////////////////////////////////

WindDirectionCommands::WindDirectionCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

WindDirectionCommands::~WindDirectionCommands()
{
}

void WindDirectionCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(WIND_DIRECTION_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<WindDirectionIntfController*>(cdmInterface);
    }

    RegisterCommand(&WindDirectionCommands::OnCmdGetHorizontalDirection, "gethd", "Get HorizontalDirection");
    RegisterCommand(&WindDirectionCommands::OnCmdSetHorizontalDirection, "sethd", "Set HorizontalDirection");
    RegisterCommand(&WindDirectionCommands::OnCmdGetHorizontalMax, "gethm", "Get HorizontalMax");
    RegisterCommand(&WindDirectionCommands::OnCmdGetHorizontalAutoMode, "getham", "Get HorizontalAutoMode");
    RegisterCommand(&WindDirectionCommands::OnCmdSetHorizontalAutoMode, "setham", "Set HorizontalAutoMode");

    RegisterCommand(&WindDirectionCommands::OnCmdGetVerticalDirection, "getvd", "Get VerticalDirection");
    RegisterCommand(&WindDirectionCommands::OnCmdSetVerticalDirection, "setvd", "Set VerticalDirection");
    RegisterCommand(&WindDirectionCommands::OnCmdGetVerticalMax, "getvm", "Get VerticalMax");
    RegisterCommand(&WindDirectionCommands::OnCmdGetVerticalAutoMode, "getvam", "Get VerticalAutoMode");
    RegisterCommand(&WindDirectionCommands::OnCmdSetVerticalAutoMode, "setvam", "Set VerticalAutoMode");


    PrintCommands();
}

void WindDirectionCommands::OnCmdGetHorizontalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetHorizontalDirection();
}

void WindDirectionCommands::OnCmdSetHorizontalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetHorizontalDirection(value);
}

void WindDirectionCommands::OnCmdGetHorizontalMax(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetHorizontalMax();
}

void WindDirectionCommands::OnCmdGetHorizontalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetHorizontalAutoMode();
}

void WindDirectionCommands::OnCmdSetHorizontalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 || value > 1) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetHorizontalAutoMode(value);
}

void WindDirectionCommands::OnCmdGetVerticalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetVerticalDirection();
}

void WindDirectionCommands::OnCmdSetVerticalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetVerticalDirection(value);
}

void WindDirectionCommands::OnCmdGetVerticalMax(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetVerticalMax();
}

void WindDirectionCommands::OnCmdGetVerticalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetVerticalAutoMode();
}

void WindDirectionCommands::OnCmdSetVerticalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfController* intfController = static_cast<WindDirectionCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = strtol(cmd.c_str(), NULL, 10);
    if (value < 0 || value > 1) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetVerticalAutoMode(value);
}

void WindDirectionListener::OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "HorizontalDirection: " << value << endl;
}
void WindDirectionListener::OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "HorizontalMax: " << value << endl;
}
void WindDirectionListener::OnHorizontalAutoModeChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "HorizontalAutoMode: " << value << endl;
}
void WindDirectionListener::OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "VerticalDirection: " << value << endl;
}
void WindDirectionListener::OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "VerticalMax: " << value << endl;
}
void WindDirectionListener::OnVerticalAutoModeChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "VerticalAutoMode: " << value << endl;
}
void WindDirectionListener::OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "HorizontalDirection: " << value << endl;
}