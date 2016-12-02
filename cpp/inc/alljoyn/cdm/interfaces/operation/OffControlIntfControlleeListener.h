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

#ifndef OFFCONTROLINTFCONTROLLEELISTENER_H_
#define OFFCONTROLINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * OffControl Interface Controllee Listener class
 */
class OffControlIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of OffControlIntfControlleeListener
     */
    virtual ~OffControlIntfControlleeListener() {}

    /**
     * Handler for SwitchOff method
     * @param[out] errorCode the error code should be set when the method call is failed
     * @return ER_OK on success
     */
     virtual QStatus OnSwitchOff(ErrorCode& errorCode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* OFFCONTROLINTFCONTROLLEELISTENER_H_ */