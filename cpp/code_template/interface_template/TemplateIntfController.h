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

#ifndef {interface_nameu}INTFCONTROLLER_H_
#define {interface_nameu}INTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/{interface_category}/{interface_name}Interface.h>

namespace ajn {
namespace services {

/**
 * {interface_name} Interface Controller class
 */
class {interface_name}IntfController : public {interface_name}Interface {
  public:
    /**
     * Constructor of {interface_name}IntfController
     */
    {interface_name}IntfController() {}

    /**
     * Destructor of {interface_name}IntfController
     */
    virtual ~{interface_name}IntfController() {}

    /**
     * TODO: define functions to request the set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */

    /*
     * TODO: define functions to request the method call
     */
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLER_H_ */