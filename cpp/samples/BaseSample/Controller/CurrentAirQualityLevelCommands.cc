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
#include "CurrentAirQualityLevelCommands.h"
#include "ControllerSample.h"

CurrentAirQualityLevelListener::CurrentAirQualityLevelListener()
{
}

CurrentAirQualityLevelListener::~CurrentAirQualityLevelListener()
{
}

void CurrentAirQualityLevelListener::OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "ContaminantType: " << (int)value << endl;
}

void CurrentAirQualityLevelListener::OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentLevel: " << (int)value << endl;
}

void CurrentAirQualityLevelListener::OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxLevel: " << (int)value << endl;
}

void CurrentAirQualityLevelListener::OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "ContaminantType: " << (int)value << endl;
}

void CurrentAirQualityLevelListener::OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentLevel: " << (int)value << endl;
}

void CurrentAirQualityLevelListener::OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxLevel: " << (int)value << endl;
}

///////////////////////////////////////////////////////////////////////////////

CurrentAirQualityLevelCommands::CurrentAirQualityLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

CurrentAirQualityLevelCommands::~CurrentAirQualityLevelCommands()
{
}

void CurrentAirQualityLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_AIR_QUALITY_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<CurrentAirQualityLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdGetContaminantType, "gct", "Get ContaminantType");
    RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdGetCurrentLevel, "gcv", "Get CurrentLevel");
    RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdGetMaxLevel, "gmax", "Get MaxLevel");

    PrintCommands();
}

void CurrentAirQualityLevelCommands::OnCmdGetContaminantType(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfController* intfController = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetContaminantType();
}

void CurrentAirQualityLevelCommands::OnCmdGetCurrentLevel(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfController* intfController = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentLevel();
}

void CurrentAirQualityLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfController* intfController = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxLevel();
}
