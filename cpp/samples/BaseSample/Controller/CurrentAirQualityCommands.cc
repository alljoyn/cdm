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
#include "CurrentAirQualityCommands.h"
#include "ControllerSample.h"

CurrentAirQualityListener::CurrentAirQualityListener()
{
}

CurrentAirQualityListener::~CurrentAirQualityListener()
{
}

void CurrentAirQualityListener::OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const ContaminantType value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "ContaminantType: " << (int)value << endl;
}

void CurrentAirQualityListener::OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentValue: " << value << endl;
}

void CurrentAirQualityListener::OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << value << endl;
}

void CurrentAirQualityListener::OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "MinValue: " << value << endl;
}

void CurrentAirQualityListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "Precision: " << value << endl;
}

void CurrentAirQualityListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "UpdateMinTime: " << value << endl;
}

void CurrentAirQualityListener::OnContaminantTypeChanged(const qcc::String& objectPath, const ContaminantType value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "ContaminantType: " << (int)value << endl;
}

void CurrentAirQualityListener::OnCurrentValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "CurrentValue: " << value << endl;
}

void CurrentAirQualityListener::OnMaxValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MaxValue: " << value << endl;
}

void CurrentAirQualityListener::OnMinValueChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "MinValue: " << value << endl;
}

void CurrentAirQualityListener::OnPrecisionChanged(const qcc::String& objectPath, const double value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "Precision: " << value << endl;
}

void CurrentAirQualityListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "UpdateMinTime: " << value << endl;
}

///////////////////////////////////////////////////////////////////////////////

CurrentAirQualityCommands::CurrentAirQualityCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

CurrentAirQualityCommands::~CurrentAirQualityCommands()
{
}

void CurrentAirQualityCommands::Init()
{
    if (!m_intfController) {
        m_intfController = m_sample->GetController()->CreateInterface<CurrentAirQualityIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }


    }

    RegisterCommand(&CurrentAirQualityCommands::OnCmdGetContaminantType, "gct", "Get ContaminantType");
    RegisterCommand(&CurrentAirQualityCommands::OnCmdGetCurrentValue, "gcv", "Get CurrentValue");
    RegisterCommand(&CurrentAirQualityCommands::OnCmdGetMaxValue, "gmax", "Get MaxValue");
    RegisterCommand(&CurrentAirQualityCommands::OnCmdGetMinValue, "gmin", "Get MinValue");
    RegisterCommand(&CurrentAirQualityCommands::OnCmdGetPrecision, "gpc", "Get Precision");
    RegisterCommand(&CurrentAirQualityCommands::OnCmdGetUpdateMinTime, "gumt", "Get UpdateMinTime");

    PrintCommands();
}

void CurrentAirQualityCommands::OnCmdGetContaminantType(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfController* intfController = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetContaminantType();
}

void CurrentAirQualityCommands::OnCmdGetCurrentValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfController* intfController = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCurrentValue();
}

void CurrentAirQualityCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfController* intfController = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMaxValue();
}

void CurrentAirQualityCommands::OnCmdGetMinValue(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfController* intfController = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetMinValue();
}

void CurrentAirQualityCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfController* intfController = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetPrecision();
}

void CurrentAirQualityCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    CurrentAirQualityIntfController* intfController = static_cast<CurrentAirQualityCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetUpdateMinTime();
}
