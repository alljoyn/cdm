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

#ifndef REMOTECONTROLLABILITYINTFCONTROLLEELISTENER_H_
#define REMOTECONTROLLABILITYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * RemoteControllability Interface Controllee Listener class
 */
class RemoteControllabilityIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RemoteControllabilityIntfControlleeListener
     */
    virtual ~RemoteControllabilityIntfControlleeListener() {}

    /**
     * Handler for getting isControllable
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] isControllable isControllable
     * @return ER_OK on success
     */
    virtual QStatus OnGetIsControllable(bool& isControllable) = 0;

};

} //namespace services
} //namespace ajn

#endif /* REMOTECONTROLLABILITYINTFCONTROLLEELISTENER_H_ */