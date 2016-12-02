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

#ifndef VENDORDEFINEDINTFCONTROLLEELISTENER_H_
#define VENDORDEFINEDINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * VendorDefined Interface Controllee Listener class
 */
class VendorDefinedIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of VendorDefinedIntfControlleeListener
     */
    virtual ~VendorDefinedIntfControlleeListener() {}

    /**
     * TODO: define functions that receives the SetProperty, GetProperty and other method call
     */
    virtual QStatus OnSetTestProperty(int32_t property) = 0;
    virtual QStatus OnGetTestProperty(int32_t& property) = 0;
    virtual QStatus OnTestMethod(int32_t arg1, qcc::String& errorName, qcc::String& errorMessage) = 0;
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLEELISTENER_H_ */