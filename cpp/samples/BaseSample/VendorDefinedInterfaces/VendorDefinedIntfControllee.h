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

#ifndef VENDORDEFINEDINTFCONTROLLEE_H_
#define VENDORDEFINEDINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include "VendorDefinedInterface.h"

namespace ajn {
namespace services {

/**
 * VendorDefined Interface Controllee class
 */
class VendorDefinedIntfControllee : public VendorDefinedInterface {
  public:
    /**
     * Constructor of VendorDefinedIntfControllee
     */
    VendorDefinedIntfControllee() {}

    /**
     * Destructor of VendorDefinedIntfControllee
     */
    virtual ~VendorDefinedIntfControllee() {}

    /**
     * TODO: define functions that set/get property
     */
    virtual QStatus SetTestProperty(int32_t property) = 0;
    virtual int32_t GetTestProperty() const = 0;

    /**
     * TODO: define functions that can emit signals
     */
    virtual QStatus EmitTestSignal() = 0;

};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLEE_H_ */