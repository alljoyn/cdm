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
#include "CurrentTemperatureCommands.h"
#include "ControllerSample.h"

CurrentTemperatureListener::CurrentTemperatureListener()
{
}

CurrentTemperatureListener::~CurrentTemperatureListener()
{
}

void CurrentTemperatureListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentValue: " << value << endl;
}

void CurrentTemperatureListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Precision: " << precision << endl;
}

void CurrentTemperatureListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "UpdateMinTime: " << updateMinTime << endl;
}

void CurrentTemperatureListener::OnCurrentValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentValue: " << value << endl;
}

void CurrentTemperatureListener::OnPrecisionChanged(const qcc::String& objectPath, const double precision)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "Precision: " << precision << endl;
}

void CurrentTemperatureListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "UpdateMinTime: " << updateMinTime << endl;
}

CurrentTemperatureCommands::CurrentTemperatureCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

CurrentTemperatureCommands::~CurrentTemperatureCommands()
{
}

void CurrentTemperatureCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_TEMPERATURE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<CurrentTemperatureIntfController*>(cdmInterface);
    }

    RegisterCommand(&CurrentTemperatureCommands::OnCmdGetCurrentValue, "getcv", "Get CurrentValue");
    RegisterCommand(&CurrentTemperatureCommands::OnCmdGetPrecision, "gp", "get precision");
    RegisterCommand(&CurrentTemperatureCommands::OnCmdGetUpdateMinTime, "gumt", "get update min time");

    PrintCommands();
}

void CurrentTemperatureCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfController* intfController = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentValue();
}

void CurrentTemperatureCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfController* intfController = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetPrecision();
}

void CurrentTemperatureCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentTemperatureIntfController* intfController = static_cast<CurrentTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetUpdateMinTime();
}