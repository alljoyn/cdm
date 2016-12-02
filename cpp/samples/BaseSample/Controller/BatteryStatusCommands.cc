/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <cstdlib>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include "BatteryStatusCommands.h"
#include "ControllerSample.h"

BatteryStatusListener::BatteryStatusListener()
{
}

BatteryStatusListener::~BatteryStatusListener()
{
}

void BatteryStatusListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t currentValue, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "currentValue: " << static_cast<int>(currentValue) << endl;
}

void BatteryStatusListener::OnResponseGetIsCharging(QStatus status, const qcc::String& objectPath, const bool isCharging, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "isCharging: " << isCharging << endl;
}

void BatteryStatusListener::OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t currentValue)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "currentValue: " << static_cast<int>(currentValue) << endl;
}

void BatteryStatusListener::OnIsChargingChanged(const qcc::String& objectPath, const bool isCharging)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "isCharging: " << isCharging << endl;
}

BatteryStatusCommands::BatteryStatusCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

BatteryStatusCommands::~BatteryStatusCommands()
{
}

void BatteryStatusCommands::Init()
{
    if (!m_intfController) {
        m_intfController = m_sample->GetController()->CreateInterface<BatteryStatusIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }
    }

    RegisterCommand(&BatteryStatusCommands::OnCmdGetCurrentValue, "gcv", "get current value of battery status");
    RegisterCommand(&BatteryStatusCommands::OnCmdGetIsCharging, "gic", "get battery charging status");
    PrintCommands();
}

void BatteryStatusCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfController* intfController = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentValue();
}

void BatteryStatusCommands::OnCmdGetIsCharging(Commands* commands, std::string& cmd)
{
    BatteryStatusIntfController* intfController = static_cast<BatteryStatusCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetIsCharging();
}
