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

#ifndef ONCONTROLINTFCONTROLLEE_H_
#define ONCONTROLINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/OnControlInterface.h>

namespace ajn {
namespace services {

/**
 * OnControl Interface Controllee class
 */
class OnControlIntfControllee : public OnControlInterface {
  public:
    /**
     * Constructor of OnControlIntfControllee
     */
    OnControlIntfControllee() {}

    /**
     * Destructor of OnControlIntfControllee
     */
    virtual ~OnControlIntfControllee() {}

};

} //namespace services
} //namespace ajn

#endif /* ONCONTROLINTFCONTROLLEE_H_ */