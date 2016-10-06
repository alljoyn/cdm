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

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "FilterStatusCommands.h"
#include "ControllerSample.h"

FilterStatusListener::FilterStatusListener()
{
}

FilterStatusListener::~FilterStatusListener()
{
}

void FilterStatusListener::OnExpectedLifeInDaysChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "ExpectedLifeInDays: " << value << endl;
}

void FilterStatusListener::OnIsCleanableChanged(const qcc::String& objectPath, const bool isCleanable)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "IsCleanable: " << isCleanable << endl;
}

void FilterStatusListener::OnOrderPercentageChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "OrderPercentage: " << (int)value << endl;
}

void FilterStatusListener::OnLifeRemainingChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "LifeRemaining: " << (int)value << endl;
}

void FilterStatusListener::OnResponseGetExpectedLifeInDays(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "ExpectedLifeInDays: " << value << endl;
}

void FilterStatusListener::OnResponseGetIsCleanable(QStatus status, const qcc::String& objectPath, const bool isCleanable, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "IsCleanable: " << isCleanable << endl;
}

void FilterStatusListener::OnResponseGetOrderPercentage(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "OrderPercentage: " << (int)value << endl;
}

void FilterStatusListener::OnResponseGetManufacturer(QStatus status, const qcc::String& objectPath, const qcc::String& manufacturer, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Manufacturer: " << manufacturer << endl;
}

void FilterStatusListener::OnResponseGetPartNumber(QStatus status, const qcc::String& objectPath, const qcc::String& partNumber, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "PartNumber: " << partNumber << endl;
}

void FilterStatusListener::OnResponseGetUrl(QStatus status, const qcc::String& objectPath, const qcc::String& url, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Url: " << url << endl;
}

void FilterStatusListener::OnResponseGetLifeRemaining(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "LifeRemaining: " << (int)value << endl;
}


//////////////////////////////////////////////////////////////////////////////////////////

FilterStatusCommands::FilterStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

FilterStatusCommands::~FilterStatusCommands()
{
}

void FilterStatusCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(FILTER_STATUS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<FilterStatusIntfController*>(cdmInterface);
    }

    RegisterCommand(&FilterStatusCommands::OnCmdGetExpectedLifeInDays, "getelid", "Get ExpectedLifeInDays");
    RegisterCommand(&FilterStatusCommands::OnCmdGetIsCleanable, "getica", "Get IsCleanable");
    RegisterCommand(&FilterStatusCommands::OnCmdGetOrderPercentage, "getop", "Get OrderPercentage");
    RegisterCommand(&FilterStatusCommands::OnCmdGetManufacturer, "getmanu", "Get Manufacturer");
    RegisterCommand(&FilterStatusCommands::OnCmdGetPartNumber, "getpn", "Get PartNumber");
    RegisterCommand(&FilterStatusCommands::OnCmdGetUrl, "geturl", "Get Url");
    RegisterCommand(&FilterStatusCommands::OnCmdGetLifeRemaining, "getlr", "Get LifeRemaining");

    PrintCommands();
}

void FilterStatusCommands::OnCmdGetExpectedLifeInDays(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetExpectedLifeInDays();
}

void FilterStatusCommands::OnCmdGetIsCleanable(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsCleanable();
}

void FilterStatusCommands::OnCmdGetOrderPercentage(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetOrderPercentage();
}

void FilterStatusCommands::OnCmdGetManufacturer(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetManufacturer();
}

void FilterStatusCommands::OnCmdGetPartNumber(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetPartNumber();
}

void FilterStatusCommands::OnCmdGetUrl(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetUrl();
}

void FilterStatusCommands::OnCmdGetLifeRemaining(Commands* commands, std::string& cmd)
{
    FilterStatusIntfController* intfController = static_cast<FilterStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetLifeRemaining();
}