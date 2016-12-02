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

#ifndef CURRENTTEMPERATUREINTFCONTROLLERLISTENER_H_
#define CURRENTTEMPERATUREINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentTemperature interface controller listener class
 */
class CurrentTemperatureIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of CurrentTemperatureIntfControllerListener
     */
    virtual ~CurrentTemperatureIntfControllerListener() {}

    /**
     * Callback handler for getting CurrentValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value current temperature
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting Precision property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] Precision precision
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context) {}

    /**
     * Callback handler for getting UpdateMinTime property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime the minimum time between updates
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context) {}

    /**
     * Handler for CurrentValue property changed
     * @param[in] objectPath the object path
     * @param[in] value current temperature
     */
    virtual void OnCurrentValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] Precision precision
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime the minimum time between updates
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTTEMPERATUREINTFCONTROLLERLISTENER_H_ */