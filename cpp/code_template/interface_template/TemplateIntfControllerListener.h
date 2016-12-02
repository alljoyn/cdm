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

#ifndef {interface_nameu}INTFCONTROLLERLISTENER_H_
#define {interface_nameu}INTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * {interface_name} Interface Controller Listener class
 */
class {interface_name}IntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~{interface_name}IntfControllerListener() {}

    /**
     * TODO: define functions that receives the response of SetProperty, GetProperty or method call
     */

    /*
     * TODO: define functions that receives the PropertyChanged and other signals
     */
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLERLISTENER_H_ */