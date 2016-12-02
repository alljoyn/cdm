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

#ifndef {interface_nameu}INTFCONTROLLEE_H_
#define {interface_nameu}INTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include "{interface_name}Interface.h"

namespace ajn {
namespace services {

/**
 * {interface_name} Interface Controllee class
 */
class {interface_name}IntfControllee : public {interface_name}Interface {
  public:
    /**
     * Constructor of {interface_name}IntfControllee
     */
    {interface_name}IntfControllee() {}

    /**
     * Destructor of {interface_name}IntfControllee
     */
    virtual ~{interface_name}IntfControllee() {}

    /**
     * TODO: define functions that set/get properties
     */

    /**
     * TODO: define functions that can emit signals, if any
     */
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLEE_H_ */