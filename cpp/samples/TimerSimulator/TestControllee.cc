#include <iostream>
#include <map>
#include <algorithm>
#include <qcc/Log.h>
#include <qcc/String.h>

#include "ControlleeCommands.h"
#include "ControlleeSample.h"
#include "TestControllee.h"


TestControllee::TestControllee(BusAttachment* bus, HaeAboutData* aboutData)
  : ControlleeSample(bus, aboutData), m_cycleControlIntfControllee(NULL), m_timerIntfControllee(NULL), m_recipeIsSet(true),endOfCycleEmitted(false)

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
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
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
        static_cast<TestControllee*>(sample)->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START);
    }
}
void TestControllee::CreateInterfaces()
{
    HaeInterface* intf = NULL;
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }

    intf = haeControllee->CreateInterface(CYCLE_CONTROL_INTERFACE, "/Hae/TestControllee", *m_cycleControlListener);
    m_cycleControlIntfControllee = static_cast<CycleControlIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(TIMER_INTERFACE, "/Hae/TestControllee", *m_timerListener);
    m_timerIntfControllee = static_cast<TimerIntfControllee*>(intf);
}

void TestControllee::SetInitialProperty()
{
    cout << "LaundryControllee::SetInitialProperty()" << endl;

    //CycleCControlInterface
    CycleControlInterface::SupportedOperationalCommands comm;
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_START);
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_STOP);
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_PAUSE);
    comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_RESUME);
    m_cycleControlIntfControllee->SetSupportedCommands(comm);

    CycleControlInterface::SupportedOperationalStates states;
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START);
    states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING);

    m_cycleControlIntfControllee->SetSupportedStates(states);

    if(IsRecipeSet())
    {
        m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START);
    }
}

void TestControllee::TimeChangedCallback(int sec)
{
    QStatus status = ER_OK;
    HaeInterface* intf = NULL;
    m_timerIntfControllee->SetReferenceTimer(sec);
    if(this->m_cycleControlIntfControllee->GetOperationalState() == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START)
    {
        if(sec == this->m_timerIntfControllee->GetTargetTimeToStart())
        {
            cout << "time == starttime. Setting state Working." << endl;
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING);
        }
    }
    if(this->m_cycleControlIntfControllee->GetOperationalState() == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING)
    {
        if(sec == this->m_timerIntfControllee->GetTargetTimeToStop())
        {
            cout << "time == stoptime. Setting state EOC." << endl;
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE);
        }
    }
    if(this->m_cycleControlIntfControllee->GetOperationalState() == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE)
    {
        if(!endOfCycleEmitted)
        {
            cout << "Emit EOC" << endl;
            status = this->m_cycleControlIntfControllee->EmitEndOfCycle();
            endOfCycleEmitted = true;
        }
        else
        {
            cout << "setting initial state" << endl;
            IsRecipeSet() ?
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START) : 
            status = this->m_cycleControlIntfControllee->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE); 
            endOfCycleEmitted = false;
        }
    }

    if(status != ER_OK)
    {
        cout << "Error in TimeChanged callback" << endl;
    }
}

