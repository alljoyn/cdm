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

#ifndef HIDINTFCONTROLLERLISTENER_H_
#define HIDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include "HidInterface.h"

namespace ajn {
namespace services {

/**
 * Hid Interface Controller Listener class
 */
class HidIntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of HidIntfControllerListener
     */
    virtual ~HidIntfControllerListener() {}

    /**
     * Callback handler for getting SupportedEvents property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supportedEvents supported events
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents, void* context) {}

    /**
     * Handler for SupportedEvents property changed
     * @param[in] objectPath the object path
     * @param[in] supportedEvents supported events
     */
    virtual void OnSupportedEventsChanged(const qcc::String& objectPath, const HidInterface::SupportedInputEvents& supportedEvents) {}
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLERLISTENER_H_ */