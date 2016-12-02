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
#include "RobotCleaningCyclePhaseCommands.h"
#include "ControllerSample.h"

RobotCleaningCyclePhaseListener::RobotCleaningCyclePhaseListener()
{
}

RobotCleaningCyclePhaseListener::~RobotCleaningCyclePhaseListener()
{
}

void RobotCleaningCyclePhaseListener::OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t cyclePhase, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "cyclePhase: " << (int)cyclePhase << endl;
}

void RobotCleaningCyclePhaseListener::OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath,
                                                                        const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (ER_OK == status) {
        for (RobotCleaningCyclePhaseInterface::SupportedCyclePhases::const_iterator citer = supportedCyclePhases.begin();
            citer != supportedCyclePhases.end(); citer++) {
            cout << (int)*citer << endl;
        }
    }
}

void RobotCleaningCyclePhaseListener::OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath,
                                                                           const RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                                           void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    if (ER_OK == status) {
        for (RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors::const_iterator citer = phasesDescription.begin();
             citer != phasesDescription.end(); citer++)
        {
            cout << (int)citer->phase << " "
                 << citer->name.c_str() << " "
                 << citer->description.c_str() << endl;
        }
    } else {
        cout << "error name : " << errorName << endl;
        cout << "error message : " << errorMessage << endl;
    }
}

void RobotCleaningCyclePhaseListener::OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t cyclePhase)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "cyclePhase: " << (int)cyclePhase << endl;
}

void RobotCleaningCyclePhaseListener::OnSupportedCyclePhasesChanged(const qcc::String& objectPath,
                                                                    const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    for (RobotCleaningCyclePhaseInterface::SupportedCyclePhases::const_iterator citer = supportedCyclePhases.begin();
        citer != supportedCyclePhases.end(); citer++) {
        cout << (int)*citer << endl;
    }
}

RobotCleaningCyclePhaseCommands::RobotCleaningCyclePhaseCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

RobotCleaningCyclePhaseCommands::~RobotCleaningCyclePhaseCommands()
{
}

void RobotCleaningCyclePhaseCommands::Init()
{
    if (!m_intfController) {
        m_intfController = m_sample->GetController()->CreateInterface<RobotCleaningCyclePhaseIntfController>(m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!m_intfController) {
            cout << "Interface creation failed." << endl;
            return;
        }


    }

    RegisterCommand(&RobotCleaningCyclePhaseCommands::OnCmdGetCyclePhase, "gcp", "get cycle phase");
    RegisterCommand(&RobotCleaningCyclePhaseCommands::OnCmdGetSupportedCyclePhases, "gscp", "get supported cycle phases");
    RegisterCommand(&RobotCleaningCyclePhaseCommands::OnCmdGetVendorPhasesDescription, "gvpd", "get vendor phases description (use 'gvpd <languageTag>'");
    PrintCommands();
}

void RobotCleaningCyclePhaseCommands::OnCmdGetCyclePhase(Commands* commands, std::string& cmd)
{
    RobotCleaningCyclePhaseIntfController* intfController = static_cast<RobotCleaningCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCyclePhase();
}

void RobotCleaningCyclePhaseCommands::OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd)
{
    RobotCleaningCyclePhaseIntfController* intfController = static_cast<RobotCleaningCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedCyclePhases();
}

void RobotCleaningCyclePhaseCommands::OnCmdGetVendorPhasesDescription(Commands* commands, std::string& cmd)
{
    RobotCleaningCyclePhaseIntfController* intfController = static_cast<RobotCleaningCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    qcc::String languageTag = qcc::String(cmd.c_str());
    intfController->GetVendorPhasesDescription(languageTag);
}
