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
#include "TargetTemperatureCommands.h"
#include "ControllerSample.h"

TargetTemperatureListener::TargetTemperatureListener()
{
}

TargetTemperatureListener::~TargetTemperatureListener()
{
}

void TargetTemperatureListener::OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void TargetTemperatureListener::OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "TargetValue: " << value << endl;
}

void TargetTemperatureListener::OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MinValue: " << value << endl;
}

void TargetTemperatureListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << value << endl;
}

void TargetTemperatureListener::OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "StepValue: " << value << endl;
}

void TargetTemperatureListener::OnTargetValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "TargetValue: " << value << endl;
}

void TargetTemperatureListener::OnMinValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MinValue: " << value << endl;
}

void TargetTemperatureListener::OnMaxValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << value << endl;
}

void TargetTemperatureListener::OnStepValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "StepValue: " << value << endl;
}

///////////////////////////////////////////////////////////////////////////////

TargetTemperatureCommands::TargetTemperatureCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

TargetTemperatureCommands::~TargetTemperatureCommands()
{
}

void TargetTemperatureCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(TARGET_TEMPERATURE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<TargetTemperatureIntfController*>(haeInterface);
    }

    RegisterCommand(&TargetTemperatureCommands::OnCmdGetTargetValue, "gettv", "Get TargetValue");
    RegisterCommand(&TargetTemperatureCommands::OnCmdSetTargetValue, "settv", "Set TargetValue");
    RegisterCommand(&TargetTemperatureCommands::OnCmdGetMinValue, "getmin", "Get MinValue");
    RegisterCommand(&TargetTemperatureCommands::OnCmdGetMaxValue, "getmax", "Get MaxValue");
    RegisterCommand(&TargetTemperatureCommands::OnCmdGetStepValue, "getstep", "Get StepValue");

    PrintCommands();
}

void TargetTemperatureCommands::OnCmdGetTargetValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfController* intfController = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetTargetValue();
}

void TargetTemperatureCommands::OnCmdSetTargetValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfController* intfController = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    double value = strtol(cmd.c_str(), NULL, 10);
    intfController->SetTargetValue(value);
}

void TargetTemperatureCommands::OnCmdGetMinValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfController* intfController = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMinValue();
}

void TargetTemperatureCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfController* intfController = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxValue();
}
void TargetTemperatureCommands::OnCmdGetStepValue(Commands* commands, std::string& cmd)
{
    TargetTemperatureIntfController* intfController = static_cast<TargetTemperatureCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetStepValue();
}
