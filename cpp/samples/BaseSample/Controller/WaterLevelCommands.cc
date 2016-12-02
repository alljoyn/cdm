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

#include "WaterLevelCommands.h"
#include "ControllerSample.h"

WaterLevelListener::WaterLevelListener()
{
}

WaterLevelListener::~WaterLevelListener()
{
}
void WaterLevelListener::OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << "# WaterLevelListener::OnResponseGetMaxLevel()" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# Object: " << objectPath << endl;
    cout << "# Max level: " << (int)value << endl;
}
void WaterLevelListener::OnResponseGetSupplySource(QStatus status, const qcc::String& objectPath, const WaterLevelInterface::SupplySource value, void* context)
{
    cout << "# WaterLevelListener::OnGetSupplySourceLevelPropertyCallback()" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# Object: " << objectPath << endl;
    cout << "# Supply Source: " << (int)value << endl;
}
void WaterLevelListener::OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << "# WaterLevelListener::OnResponseGetCurrentLevel()" << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# Object: " << objectPath << endl;
    cout << "# Current level: " << (int)value << endl;
}

void WaterLevelListener::OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << "# WaterLevelListener.OnMaxLevelChanged()" << endl;
    cout << "# Object: " << objectPath << endl;
    cout << "# MaxLevel: " << (int)value << endl;
}
void WaterLevelListener::OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << "# WaterLevelListener.OnCurrentLevelChanged()" << endl;
    cout << "# Object: " << objectPath << endl;
    cout << "# CurrentLevel: " << (int)value << endl;
}
void WaterLevelListener::OnSupplySourceChanged(const qcc::String& objectPath, const WaterLevelInterface::SupplySource value)
{
    cout << "# WaterLevelListener.OnSupplySourceChanged()" << endl;
    cout << "# Object: " << objectPath << endl;
    cout << "# SupplySource: " << (int)value << endl;
}



WaterLevelCommands::WaterLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

WaterLevelCommands::~WaterLevelCommands()
{

}

void WaterLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(WATER_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<WaterLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&WaterLevelCommands::OnCmdGetMaxLevel, "gml", "get max water level");
    RegisterCommand(&WaterLevelCommands::OnCmdGetCurrentLevel, "gcl", "get current water level");
    RegisterCommand(&WaterLevelCommands::OnCmdSetSupplySource, "gsc", "get supply source");
    PrintCommands();
}

void WaterLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    WaterLevelIntfController* intfController = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetMaxLevel();
}

void WaterLevelCommands::OnCmdGetCurrentLevel(Commands* commands, std::string& cmd)
{
    WaterLevelIntfController* intfController = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentLevel();
}
void WaterLevelCommands::OnCmdSetSupplySource(Commands* commands, std::string& cmd)
{
    WaterLevelIntfController* intfController = static_cast<WaterLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupplySource();
}
