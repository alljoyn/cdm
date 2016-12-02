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

#ifndef VENDORDEFINEDINTFCONTROLLER_H_
#define VENDORDEFINEDINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include "VendorDefinedInterface.h"

namespace ajn {
namespace services {

/**
 * VendorDefined Interface Controller class
 */
class VendorDefinedIntfController : public VendorDefinedInterface {
  public:
    /**
     * Constructor of VendorDefinedIntfController
     */
    VendorDefinedIntfController() {}

    /**
     * Destructor of VendorDefinedIntfController
     */
    virtual ~VendorDefinedIntfController() {}

    /**
     * TODO: define functions to request the set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */
    virtual QStatus SetTestProperty(int32_t property, void* context = NULL) = 0;
    virtual QStatus GetTestProperty(void*  context = NULL) = 0;

    /*
     * TODO: define functions to request the method call
     */
    virtual QStatus TestMethod(int32_t arg1, void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLER_H_ */