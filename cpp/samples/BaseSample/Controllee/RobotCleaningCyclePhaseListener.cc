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

#include "RobotCleaningCyclePhaseListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus RobotCleaningCyclePhaseListener::OnGetCyclePhase(uint8_t& cyclePhase)
{
    cout << "RobotCleaningCyclePhaseListener::OnGetCyclePhase()" << endl;
    return ER_OK;
}

QStatus RobotCleaningCyclePhaseListener::OnGetSupportedCyclePhases(RobotCleaningCyclePhaseInterface::SupportedCyclePhases& supportedCyclePhases)
{
    cout << "RobotCleaningCyclePhaseListener::OnGetSupportedCyclePhases()" << endl;
    return ER_OK;
}

QStatus RobotCleaningCyclePhaseListener::OnGetVendorPhasesDescription(const qcc::String& languageTag,
                                                                      RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors& phasesDescription,
                                                                      ErrorCode& errorCode)
{
    cout << "RobotCleaningCyclePhaseListener::OnGetVendorPhasesDescription" << endl;

    if (languageTag == "en") {
        RobotCleaningCyclePhaseInterface::CyclePhaseDescriptors description;
        RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor descriptor1;
        descriptor1.phase = 0x80;
        descriptor1.name = "Paused";
        descriptor1.description = "Paused state";
        description.push_back(descriptor1);
        phasesDescription = description;
    } else {
        errorCode = LANGUAGE_NOT_SUPPORTED;
        return ER_LANGUAGE_NOT_SUPPORTED;
    }

    return ER_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* RobotCleaningCyclePhaseCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new RobotCleaningCyclePhaseCommands(sample, objectPath);
}

RobotCleaningCyclePhaseCommands::RobotCleaningCyclePhaseCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

RobotCleaningCyclePhaseCommands::~RobotCleaningCyclePhaseCommands()
{
}

void RobotCleaningCyclePhaseCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<RobotCleaningCyclePhaseIntfControllee*>(cdmInterface);

        RegisterCommand(&RobotCleaningCyclePhaseCommands::OnCmdGetCyclePhase, "gcp", "get cycle phase");
        RegisterCommand(&RobotCleaningCyclePhaseCommands::OnCmdSetCyclePhase, "scp", "set cycle phase (use 'scp <phase>'");
        RegisterCommand(&RobotCleaningCyclePhaseCommands::OnCmdGetSupportedCyclePhases, "gsc", "get supported cylce phases");
    } else {
        PrintCommands();
    }
}

void RobotCleaningCyclePhaseCommands::InitializeProperties()
{
    if (m_intfControllee) {
        RobotCleaningCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase = {
            RobotCleaningCyclePhaseInterface::ROBOT_CLEANING_CYCLE_PHASE_CLEANING,
            RobotCleaningCyclePhaseInterface::ROBOT_CLEANING_CYCLE_PHASE_HOMING,
            0x80 };
        uint8_t cyclePhase = RobotCleaningCyclePhaseInterface::ROBOT_CLEANING_CYCLE_PHASE_CLEANING;
        m_intfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_intfControllee->SetCyclePhase(cyclePhase);
    }
}

void RobotCleaningCyclePhaseCommands::OnCmdGetCyclePhase(Commands* commands, std::string& cmd)
{
    RobotCleaningCyclePhaseIntfControllee* intfControllee = static_cast<RobotCleaningCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetCyclePhase() << endl;
}

void RobotCleaningCyclePhaseCommands::OnCmdSetCyclePhase(Commands* commands, std::string& cmd)
{
    RobotCleaningCyclePhaseIntfControllee* intfControllee = static_cast<RobotCleaningCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int phase = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetCyclePhase(phase);
}

void RobotCleaningCyclePhaseCommands::OnCmdGetSupportedCyclePhases(Commands* commands, std::string& cmd)
{
    RobotCleaningCyclePhaseIntfControllee* intfControllee = static_cast<RobotCleaningCyclePhaseCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const RobotCleaningCyclePhaseInterface::SupportedCyclePhases& phases = intfControllee->GetSupportedCyclePhases();
    for (RobotCleaningCyclePhaseInterface::SupportedCyclePhases::const_iterator citer = phases.begin();
            citer != phases.end(); citer++) {
        cout << (int)*citer << endl;
    }
}

