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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLERLISTENER_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel interface controller listener class
 */
class TargetTemperatureLevelIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TargetTemperatureLevelIntfControllerListener
     */
    virtual ~TargetTemperatureLevelIntfControllerListener() {}

    /**
     * Callback handler for setting TargetValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting TargetLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target temperature level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting SelectableTemperatureLevels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the selectable temperature levels
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value, void* context) {}

    /**
     * Handler for TargetLevel property changed
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     */
    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target temperature level
     */
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for SelectableTemperatureLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value the step value of target temperature level
     */
    virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value) {}
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLERLISTENER_H_ */