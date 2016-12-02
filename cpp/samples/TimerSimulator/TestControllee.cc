#include <iostream>
#include <map>
#include <algorithm>
#include <qcc/Log.h>
#include <qcc/String.h>

#include "ControlleeCommands.h"
#include "ControlleeSample.h"
#include "TestControllee.h"


TestControllee::TestControllee(BusAttachment* bus, CdmAboutData* aboutData)
  : ControlleeSample(bus, aboutData), m_cycleControlIntfControllee(NULL), m_timerIntfControllee(NULL), m_recipeIsSet(true)

{
    m_initialTime = clock();

    m_cycleControlListener = new TestCycleControlListener((void*)this);
    m_timerListener = new TestTimerListener((void*)this);
}

TestControllee::~TestControllee()
{
    if(m_cycleControlListener){
        delete m_cycleControlListener;
    }
    if(m_timerListener) {
        delete m_timerListener;
    }
}

void TestControllee::SetRefTimer(int sec)
{
    m_timerIntfControllee->SetReferenceTimer(sec);
}
void TestControllee::InitSample()
{
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }
    m_rootCommands->RegisterCommand(&TestControllee::OnCmdSetRecipe, "sr", "set recipe");
}
QStatus TestControllee::InitS()
{
    return this->Init();
}
void TestControllee::OnCmdSetRecipe(Commands* commands, std::string& cmd)
{
    ControlleeSample* sample = static_cast<ControlleeCommands*>(commands)->GetControlleeSample();

    int lvl = strtol(cmd.c_str(), NULL, 10);

    if (static_cast<TestControllee*>(sample)->m_cycleControlIntfControllee) {
        static_cast<TestControllee*>(sample)->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::OperationalState::OPERATIONAL_STATE_READY_TO_START);
    }
}
void TestControllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    intf = cdmControllee->CreateInterface(CYCLE_CONTROL_INTERFACE, "/Cdm/TestControllee", *m_cycleControlListener);
    m_cycleControlIntfControllee = static_cast<CycleControlIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TIMER_INTERFACE, "/Cdm/TestControllee", *m_timerListener);
    m_timerIntfControllee = static_cast<TimerIntfControllee*>(intf);
}

void TestControllee::SetInitialProperty()
{
    cout << "LaundryControllee::SetInitialProperty()" << endl;

    //CycleCControlInterface
    CycleControlInterface::SupportedOperationalCommands comm;
    comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_START);
    comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_STOP);
    comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_PAUSE);
    comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_RESUME);
    m_cycleControlIntfControllee->SetSupportedCommands(comm);

    CycleControlInterface::SupportedOperationalStates states;
    states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_IDLE);
    states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_PAUSED);
    states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_READY_TO_START);
    states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_END_OF_CYCLE);
    states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_DELAYED_START);
    states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_WORKING);

    m_cycleControlIntfControllee->SetSupportedStates(states);

    if(IsRecipeSet())
    {
        m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::OperationalState::OPERATIONAL_STATE_READY_TO_START);
    }
}

void TestControllee::TimeChangedCallback(int sec)
{
    QStatus status = ER_OK;
    CdmInterface* intf = NULL;
    m_timerIntfControllee->SetReferenceTimer(sec);
    if(this->m_cycleControlIntfControllee->GetOperationalState() == CycleControlInterface::OperationalState::OPERATIONAL_STATE_DELAYED_START)
    {
        if(sec == this->m_timerIntfControllee->GetTargetTimeToStart())
        {
            cout << "time == starttime. Setting state Working." << endl;
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::OperationalState::OPERATIONAL_STATE_WORKING);
        }
    }
    if(this->m_cycleControlIntfControllee->GetOperationalState() == CycleControlInterface::OperationalState::OPERATIONAL_STATE_WORKING)
    {
        if(sec == this->m_timerIntfControllee->GetTargetTimeToStop())
        {
            cout << "time == stoptime. Setting state EOC." << endl;
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::OperationalState::OPERATIONAL_STATE_END_OF_CYCLE);
        }
    }
    if(this->m_cycleControlIntfControllee->GetOperationalState() == CycleControlInterface::OperationalState::OPERATIONAL_STATE_END_OF_CYCLE)
    {
            cout << "setting initial state" << endl;
            IsRecipeSet() ?
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::OperationalState::OPERATIONAL_STATE_READY_TO_START) :
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::OperationalState::OPERATIONAL_STATE_IDLE);
    }

    if(status != ER_OK)
    {
        cout << "Error in TimeChanged callback" << endl;
    }
}

