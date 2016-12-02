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

#ifndef ONCONTROLINTFCONTROLLER_H_
#define ONCONTROLINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/OnControlInterface.h>

namespace ajn {
namespace services {

/**
 * OnControl Interface Controller class
 */
class OnControlIntfController : public OnControlInterface {
  public:
    /**
     * Constructor of OnControlIntfController
     */
    OnControlIntfController() {}

    /**
     * Destructor of OnControlIntfController
     */
    virtual ~OnControlIntfController() {}

    /**
     * SwitchOn
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SwitchOn(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ONCONTROLINTFCONTROLLER_H_ */