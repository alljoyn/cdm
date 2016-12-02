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

#ifndef {interface_nameu}INTFCONTROLLEELISTENER_H_
#define {interface_nameu}INTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * {interface_name} Interface Controllee Listener class
 */
class {interface_name}IntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of {interface_name}IntfControlleeListener
     */
    virtual ~{interface_name}IntfControlleeListener() {}

    /**
     * TODO: define functions that receives the SetProperty, GetProperty and other method call
     */
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLEELISTENER_H_ */