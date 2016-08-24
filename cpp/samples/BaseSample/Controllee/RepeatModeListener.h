/*
 * RobotCleaningCycleListener.h
 *
 *  Created on: Feb 2, 2016
 *      Author: jiny1u
 */

#ifndef REPEATMODELISTENER_H_
#define REPEATMODELISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControlleeListener.h>

namespace ajn {
namespace services {


class RepeatModeListener : public RepeatModeIntfControlleeListener {
public:
    virtual QStatus OnSetRepeatMode(const bool repeatMode);
    virtual QStatus OnGetRepeatMode(bool& repeatMode);
};
////////////////////////////////////////////////////////////////////////////////

class RepeatModeCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    RepeatModeCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~RepeatModeCommands();

    virtual void Init();

    RepeatModeIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetRepeatMode(Commands* commands, std::string& cmd);
    static void OnCmdSetRepeatMode(Commands* commands, std::string& cmd);

  private:
    RepeatModeIntfControllee* m_intfControllee;
    RepeatModeListener m_listener;
};


} /* namespace services */
} /* namespace ajn */
#endif /* REPEATMODELISTENER_H_ */
