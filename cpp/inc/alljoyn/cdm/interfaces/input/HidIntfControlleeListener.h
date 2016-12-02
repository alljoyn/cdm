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

#ifndef HIDINTFCONTROLLEELISTENER_H_
#define HIDINTFCONTROLLEELISTENER_H_

#include <vector>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include "HidInterface.h"

namespace ajn {
namespace services {

/**
 * Hid Interface Controllee Listener class
 */
class HidIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of HidIntfControlleeListener
     */
    virtual ~HidIntfControlleeListener() {}

    /**
     * Handler for getting SupportedEvents property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supportedEvents supported events
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedEvents(HidInterface::SupportedInputEvents& supportedEvents) = 0;

    /**
     * Handler for InjectEvents method
     * @param[in] inputEvents input events
     */
    virtual void OnInjectEvents(HidInterface::InputEvents& inputEvents) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLEELISTENER_H_ */