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

#ifndef VENDORDEFINEDINTFCONTROLLERLISTENER_H_
#define VENDORDEFINEDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * VendorDefined Interface Controller Listener class
 */
class VendorDefinedIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~VendorDefinedIntfControllerListener() {}

    /*
     * TODO: define functions that receives the response of SetProperty, GetProperty or method call
     */
    virtual void OnResponseSetTestProperty(QStatus status, const qcc::String& objectPath, void* context) {}
    virtual void OnResponseGetTestProperty(QStatus status, const qcc::String& objectPath, int32_t property, void* context) {}
    virtual void OnResponseTestMethod(QStatus status, const qcc::String& objectPath,
            void* context, const char* errorName, const char* errorMessage) {}

    /*
     * TODO: define functions that receives the PropertyChanged and other signals
     */
    virtual void OnTestPropertyChanged(const qcc::String& objectPath, const int32_t property) {}
    virtual void OnTestSignal(const qcc::String& objectPath) {}
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLERLISTENER_H_ */