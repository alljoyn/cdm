#ifndef _TESTCONTROLLEE_H_
#define _TESTCONTROLLEE_H_

#include <qcc/Log.h>
#include <qcc/String.h>

#include "ControlleeCommands.h"
#include "ControlleeSample.h"

#include "TestCycleControlListener.h"
#include "TestTimerListener.h"
#include <alljoyn/hae/interfaces/operation/CycleControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/TimerIntfControllee.h>

using namespace std;
using namespace qcc;

class TestControllee : public ControlleeSample
{
  private:
    TestCycleControlListener *m_cycleControlListener;
    TestTimerListener * m_timerListener;

    CycleControlIntfControllee* m_cycleControlIntfControllee;
    TimerIntfControllee* m_timerIntfControllee;

    bool m_recipeIsSet;

    clock_t m_initialTime;
  public:
    TestControllee(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~TestControllee();
    void CreateInterfaces();
    void SetInitialProperty();
    void InitSample();
    QStatus InitS();
    TimerIntfControllee* TimerIntf() { return m_timerIntfControllee; }
    CycleControlIntfControllee* CycleIntf() { return m_cycleControlIntfControllee; }
    void SetRefTimer(int sec);
    bool IsRecipeSet() {return m_recipeIsSet;}
    void SetRecipe() { m_recipeIsSet = true;}
    void ResetRecipe() { m_recipeIsSet = false;}
    CycleControlIntfControllee::CycleControlOperationalState m_pausedState;
    int m_timeElapsed;
    int m_timeTillStart;
    bool endOfCycleEmitted;

    void TimeChangedCallback(int sec);
    static void OnCmdSetRecipe(Commands* commands, std::string& cmd);
};
#endif