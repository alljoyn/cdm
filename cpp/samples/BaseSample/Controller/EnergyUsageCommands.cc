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

#include "EnergyUsageCommands.h"
#include "ControllerSample.h"

using namespace std;

EnergyUsageListener::EnergyUsageListener()
{
}

EnergyUsageListener::~EnergyUsageListener()
{
}

void EnergyUsageListener::OnResponseGetCumulativeEnergy(QStatus status, const qcc::String& objectPath, const double cumulativeEnergy, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "cumulativeEnergy: " << cumulativeEnergy << endl;
}

void EnergyUsageListener::OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "precision: " << precision << endl;
}

void EnergyUsageListener::OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "updateMinTime: " << updateMinTime << endl;
}

void EnergyUsageListener::OnResponseResetCumulativeEnergy(QStatus status, const qcc::String& objectPath,
                                                          void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (ER_OK == status) {
        cout << "ok" << endl;
    } else {
        cout << "error name : " << errorName << endl;
        cout << "error message : " << errorMessage << endl;
    }
}

void EnergyUsageListener::OnCumulativeEnergyChanged(const qcc::String& objectPath, const double cumulatvieEnergy)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "cumulatvieEnergy: " << cumulatvieEnergy << endl;
}

void EnergyUsageListener::OnPrecisionChanged(const qcc::String& objectPath, const double precision)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "precision: " << precision << endl;
}

void EnergyUsageListener::OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "updateMinTime: " << updateMinTime << endl;
}

////////////////////////////////////////////////////////////////////////
EnergyUsageCommands::EnergyUsageCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

EnergyUsageCommands::~EnergyUsageCommands()
{
}

void EnergyUsageCommands::Init()
{
    if (!m_intfController) {
        m_intfController = m_sample->GetController()->CreateInterface<EnergyUsageIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }


    }

    RegisterCommand(&EnergyUsageCommands::OnCmdGetCumulativeEnergy, "gce", "get cumulative energy");
    RegisterCommand(&EnergyUsageCommands::OnCmdGetPrecision, "gp", "get precision");
    RegisterCommand(&EnergyUsageCommands::OnCmdGetUpdateMinTime, "gumt", "get update min time");
    RegisterCommand(&EnergyUsageCommands::OnCmdResetCumulativeEnergy, "rce", "reset cumulative energy");
    PrintCommands();
}

void EnergyUsageCommands::OnCmdGetCumulativeEnergy(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfController* intfController = static_cast<EnergyUsageCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetCumulativeEnergy();
}

void EnergyUsageCommands::OnCmdGetPrecision(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfController* intfController = static_cast<EnergyUsageCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetPrecision();
}

void EnergyUsageCommands::OnCmdGetUpdateMinTime(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfController* intfController = static_cast<EnergyUsageCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetUpdateMinTime();
}

void EnergyUsageCommands::OnCmdResetCumulativeEnergy(Commands* commands, std::string& cmd)
{
    EnergyUsageIntfController* intfController = static_cast<EnergyUsageCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->ResetCumulativeEnergy();
}
