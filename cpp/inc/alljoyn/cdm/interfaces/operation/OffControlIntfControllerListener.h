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

#ifndef OFFCONTROLINTFCONTROLLERLISTENER_H_
#define OFFCONTROLINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * OffControl Interface Controller Listener class
 */
class OffControlIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~OffControlIntfControllerListener() {}

    /**
     * Callback handler for SwitchOff method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseSwitchOff(QStatus status, const qcc::String& objectPath, void* context,
                                         const char* errorName, const char* errorMessage) {}

};

} //namespace services
} //namespace ajn

#endif /* OFFCONTROLINTFCONTROLLERLISTENER_H_ */