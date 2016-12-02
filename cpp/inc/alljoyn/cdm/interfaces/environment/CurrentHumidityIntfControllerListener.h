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

#ifndef CURRENTHUMIDITYINTFCONTROLLERLISTENER_H_
#define CURRENTHUMIDITYINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity interface controller listener class
 */
class CurrentHumidityIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of CurrentHumidityIntfControllerListener
     */
    virtual ~CurrentHumidityIntfControllerListener() {}

    /**
     * Callback handler for getting CurrentValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value current humidity
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value max humidity
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] value current humidity
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value max humidity
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLERLISTENER_H_ */