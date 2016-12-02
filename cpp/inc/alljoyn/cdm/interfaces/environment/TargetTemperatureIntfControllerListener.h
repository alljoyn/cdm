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

#ifndef TARGETTEMPERATUREINTFCONTROLLERLISTENER_H_
#define TARGETTEMPERATUREINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature interface controller listener class
 */
class TargetTemperatureIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TargetTemperatureIntfControllerListener
     */
    virtual ~TargetTemperatureIntfControllerListener() {}

    /**
     * Callback handler for setting TargetValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting TargetValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting MinValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the minimum value of target temperature
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting MaxValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target temperature
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Callback handler for getting StepValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the step value of target temperature
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const double value, void* context) {}

    /**
     * Handler for TargetValue property changed
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     */
    virtual void OnTargetValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for MinValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the minimum value of target temperature
     */
    virtual void OnMinValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target temperature
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const double value) {}

    /**
     * Handler for StepValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the step value of target temperature
     */
    virtual void OnStepValueChanged(const qcc::String& objectPath, const double value) {}

};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLERLISTENER_H_ */