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

#ifndef REPEATMODEINTFCONTROLLERLISTENER_H_
#define REPEATMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * RepeatMode Interface Controller Listener class
 */
class RepeatModeIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RepeatModeIntfControllerListener() {}

    /**
     * Callback handler for getting RepeatMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] RepeatMode value
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRepeatMode(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Callback handler for getting RepeatMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetRepeatMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Handler for RepeatMode property changed
     * @param[in] objectPath the object path
     * @param[in] RepeatMode value
     */
    virtual void OnRepeatModeChanged(const qcc::String& objectPath, const bool value) {}

};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLERLISTENER_H_ */