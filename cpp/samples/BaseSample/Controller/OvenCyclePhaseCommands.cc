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

#include "OvenCyclePhaseCommands.h"
#include "ControllerSample.h"

OvenCyclePhaseListener::OvenCyclePhaseListener()
{
}

OvenCyclePhaseListener::~OvenCyclePhaseListener()
{
}


void OvenCyclePhaseListener::OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t& cyclePhase, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# cyclePhase: " << (int)cyclePhase << endl;
}

void OvenCyclePhaseListener::OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const OvenCyclePhaseInterface::SupportedCyclePhases& listOfCyclePhases, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported cycle phases: " << endl;
    for(size_t i = 0 ; i < listOfCyclePhases.size(); i++)
        cout << (int)listOfCyclePhases[i] << endl;
}

void OvenCyclePhaseListener::OnCyclePhasePropertyChanged(const qcc::String& objectPath, const uint8_t cyclePhase)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# cyclePhase: " << (int)cyclePhase << endl;
}

void OvenCyclePhaseListener::OnSupportedCyclePhasesPropertyChanged(const qcc::String& objectPath, const OvenCyclePhaseInterface::SupportedCyclePhases listOfCyclePhases)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# supported cycle phases: " << endl;
    for(size_t i = 0 ; i < listOfCyclePhases.size(); i++)
        cout << (int)listOfCyclePhases[i] << endl;
}

void OvenCyclePhaseListener::OnResponseGetCyclePhasesDescriptions(QStatus status, const qcc::String& objectPath, const OvenCyclePhaseInterface::CyclePhaseDescriptions& listOfCycleDescriptions, void* context, const char* errorName, const char* errorMessage)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# phase descs: " << endl;
    cout << "Status: " << QCC_StatusText(status) << endl;
    if(status != ER_OK)
    {
        cout << "error name: " << errorName << endl;
        cout << "error mess: " << errorMessage << endl;
    }
    for(size_t i = 0 ; i < listOfCycleDescriptions.size(); i++)
        cout << (int)listOfCycleDescriptions[i].phase << " " << listOfCycleDescriptions[i].name << " " << listOfCycleDescriptions[i].description<<endl;
}

OvenCyclePhaseCommands::OvenCyclePhaseCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

OvenCyclePhaseCommands::~OvenCyclePhaseCommands()
{

}

void OvenCyclePhaseCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(OVEN_CYCLE_PHASE_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<OvenCyclePhaseIntfController*>(haeInterface);
    }

    RegisterCommand(&OvenCyclePhaseCommands::OnCmdGetCyclePhase, "gcp", "get cycle phase");
    RegisterCommand(&OvenCyclePhaseCommands::OnCmdGetSupportedCyclePhases, "gscp", "get supported cycle phases");
    RegisterCommand(&OvenCyclePhaseCommands::OnCmdGetCyclePhasesDescriptions, "gcpd", "get cycle phase descriptions");
    PrintCommands();
}
void OvenCyclePhaseCommands::OnCmdGetCyclePhase(Commands* commands, std::string& cmd)
{
    OvenCyclePhaseIntfController* intfController = static_cast<OvenCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetCyclePhase();
}

void OvenCyclePhaseCommands::OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd)
{
    OvenCyclePhaseIntfController* intfController = static_cast<OvenCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedCyclePhases();
}

void OvenCyclePhaseCommands::OnCmdGetCyclePhasesDescriptions(Commands* commands, std::string& cmd)
{
    OvenCyclePhaseIntfController* intfController = static_cast<OvenCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << "Command string: " << cmd.c_str() << endl;
    intfController->GetCyclePhasesDescriptions(cmd.c_str());
}
