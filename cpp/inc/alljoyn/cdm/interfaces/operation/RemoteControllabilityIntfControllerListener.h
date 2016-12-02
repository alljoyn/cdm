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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLERLISTENER_H_
#define REMOTECONTROLLABILITYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * RemoteControllability Interface Controller Listener class
 */
class RemoteControllabilityIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RemoteControllabilityIntfControllerListener() {}

    /**
     * Callback handler for getting IsControllableproperty
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isControllable isControllable
     * @param[in] context the context that is passed from application
     */
    virtual void GetIsControllablePropertyCallback(QStatus status, const qcc::String& objectPath, const bool isControllable, void* context) {}

    /**
     * Handler for IsControllable property changed
     * @param[in] objectPath the object path
     * @param[in] isControllable isControllable
     */
    virtual void IsControllalbePropertyChanged(const qcc::String& objectPath, const bool isControllable) {}

};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLERLISTENER_H_ */