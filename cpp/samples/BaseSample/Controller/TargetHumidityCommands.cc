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
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>
#include "TargetHumidityCommands.h"
#include "ControllerSample.h"

TargetHumidityListener::TargetHumidityListener()
{
}

TargetHumidityListener::~TargetHumidityListener()
{
}

void TargetHumidityListener::OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void TargetHumidityListener::OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "TargetValue: " << (int)value << endl;
}

void TargetHumidityListener::OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MinValue: " << (int)value << endl;
}

void TargetHumidityListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << (int)value << endl;
}

void TargetHumidityListener::OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "StepValue: " << (int)value << endl;
}

void TargetHumidityListener::OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "SelectableHumidityLevels: ";
    for (size_t i = 0; i < value.size(); ++i) {
        cout << (int)value[i] << ", ";
    }
    cout << endl;
}

void TargetHumidityListener::OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "TargetValue: " << (int)value << endl;
}

void TargetHumidityListener::OnMinValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MinValue: " << (int)value << endl;
}

void TargetHumidityListener::OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << (int)value << endl;
}

void TargetHumidityListener::OnStepValueChanged(const qcc::String& objectPath, const uint8_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "StepValue: " << (int)value << endl;
}

void TargetHumidityListener::OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "SelectableHumidityLevels: ";
    for (size_t i = 0; i < value.size(); ++i) {
        cout << (int)value[i] << ", ";
    }
    cout << endl;

}

///////////////////////////////////////////////////////////////////////////////

TargetHumidityCommands::TargetHumidityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

TargetHumidityCommands::~TargetHumidityCommands()
{
}

void TargetHumidityCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(TARGET_HUMIDITY_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<TargetHumidityIntfController*>(haeInterface);
    }

    RegisterCommand(&TargetHumidityCommands::OnCmdGetTargetValue, "gtv", "Get TargetValue");
    RegisterCommand(&TargetHumidityCommands::OnCmdSetTargetValue, "stv", "Set TargetValue");
    RegisterCommand(&TargetHumidityCommands::OnCmdGetMinValue, "gmn", "Get MinValue");
    RegisterCommand(&TargetHumidityCommands::OnCmdGetMaxValue, "gmx", "Get MaxValue");
    RegisterCommand(&TargetHumidityCommands::OnCmdGetStepValue, "gs", "Get StepValue");
    RegisterCommand(&TargetHumidityCommands::OnCmdGetSelectableHumidityLevels, "gshl", "Get SelectableHumidityLevels");

    PrintCommands();
}

void TargetHumidityCommands::OnCmdGetTargetValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfController* intfController = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetValue();
}

void TargetHumidityCommands::OnCmdSetTargetValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfController* intfController = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int value = atoi(cmd.c_str());
    intfController->SetTargetValue(value);
}

void TargetHumidityCommands::OnCmdGetMinValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfController* intfController = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMinValue();
}

void TargetHumidityCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfController* intfController = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxValue();
}
void TargetHumidityCommands::OnCmdGetStepValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfController* intfController = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetStepValue();
}

void TargetHumidityCommands::OnCmdGetSelectableHumidityLevels(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfController* intfController = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSelectableHumidityLevels();
}
