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

#ifndef OFFCONTROLINTFCONTROLLEE_H_
#define OFFCONTROLINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/OffControlInterface.h>

namespace ajn {
namespace services {

/**
 * OffControl Interface Controllee class
 */
class OffControlIntfControllee : public OffControlInterface {
  public:
    /**
     * Constructor of OffControlIntfControllee
     */
    OffControlIntfControllee() {}

    /**
     * Destructor of OffControlIntfControllee
     */
    virtual ~OffControlIntfControllee() {}

};

} //namespace services
} //namespace ajn

#endif /* OFFCONTROLINTFCONTROLLEE_H_ */