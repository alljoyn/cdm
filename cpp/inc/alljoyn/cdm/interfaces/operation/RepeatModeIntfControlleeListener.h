/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef REPEATMODEINTFCONTROLLEELISTENER_H_
#define REPEATMODEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * RepeatMode Interface Controllee Listener class
 */
class RepeatModeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RepeatModeIntfControlleeListener
     */
    virtual ~RepeatModeIntfControlleeListener() {}

    /**
     * Handler for setting RepeatMode property
     * @param[in] OperationalCycle
     * @return ER_OK on success
     */
    virtual QStatus OnSetRepeatMode(const bool repeatMode) = 0;

    /**
     * Handler for getting RepeatMode property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] RepeatMode
     * @return ER_OK on success
     */
    virtual QStatus OnGetRepeatMode(bool& repeatMode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLEELISTENER_H_ */