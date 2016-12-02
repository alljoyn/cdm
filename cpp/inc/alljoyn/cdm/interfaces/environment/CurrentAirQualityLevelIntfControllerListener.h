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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLERLISTENER_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controller Listener class
 */
class CurrentAirQualityLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~CurrentAirQualityLevelIntfControllerListener() {}

    /**
     * Callback handler for getting ContaminantType property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value contaminant type
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting CurrentLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value air quality level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum level of air quality
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for ContaminantType property changed
     * @param[in] objectPath the object path
     * @param[in] value air quality
     */
    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for CurrentLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value air quality
     */
    virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of air quality
     */
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) {}


};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLERLISTENER_H_ */