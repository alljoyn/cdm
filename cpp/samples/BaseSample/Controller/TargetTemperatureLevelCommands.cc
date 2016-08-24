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
#include "TargetTemperatureLevelCommands.h"
#include "ControllerSample.h"

TargetTemperatureLevelListener::TargetTemperatureLevelListener()
{
}

TargetTemperatureLevelListener::~TargetTemperatureLevelListener()
{
}

void TargetTemperatureLevelListener::OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void TargetTemperatureLevelListener::OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "TargetLevel: " << (int)value << endl;
}

void TargetTemperatureLevelListener::OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxLevel: " << (int)value << endl;
}

void TargetTemperatureLevelListener::OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "SelectableTemperatureLevels: ";
    for (size_t i = 0; i < value.size(); ++i) {
        cout << (int)value[i] << ", ";
    }
    cout << endl;
}

void TargetTemperatureLevelListener::OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "TargetLevel: " << (int)value << endl;
}

void TargetTemperatureLevelListener::OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxLevel: " << (int)value << endl;
}

void TargetTemperatureLevelListener::OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "SelectableTemperatureLevels: ";
    for (size_t i = 0; i < value.size(); ++i) {
        cout << (int)value[i] << ", ";
    }
    cout << endl;

}

///////////////////////////////////////////////////////////////////////////////

TargetTemperatureLevelCommands::TargetTemperatureLevelCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

TargetTemperatureLevelCommands::~TargetTemperatureLevelCommands()
{
}

void TargetTemperatureLevelCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TARGET_TEMPERATURE_LEVEL_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<TargetTemperatureLevelIntfController*>(cdmInterface);
    }

    RegisterCommand(&TargetTemperatureLevelCommands::OnCmdGetTargetLevel, "gtv", "Get TargetLevel");
    RegisterCommand(&TargetTemperatureLevelCommands::OnCmdSetTargetLevel, "stv", "Set TargetLevel");
    RegisterCommand(&TargetTemperatureLevelCommands::OnCmdGetMaxLevel, "gmx", "Get MaxLevel");
    RegisterCommand(&TargetTemperatureLevelCommands::OnCmdGetSelectableTemperatureLevels, "gshl", "Get SelectableTemperatureLevels");

    PrintCommands();
}

void TargetTemperatureLevelCommands::OnCmdGetTargetLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfController* intfController = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetLevel();
}

void TargetTemperatureLevelCommands::OnCmdSetTargetLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfController* intfController = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = atoi(cmd.c_str());
    intfController->SetTargetLevel(value);
}

void TargetTemperatureLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfController* intfController = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxLevel();
}

void TargetTemperatureLevelCommands::OnCmdGetSelectableTemperatureLevels(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfController* intfController = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSelectableTemperatureLevels();
}
