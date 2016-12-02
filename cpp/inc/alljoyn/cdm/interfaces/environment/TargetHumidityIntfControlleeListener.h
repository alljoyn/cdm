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

#ifndef TARGETHUMIDITYINTFCONTROLLEELISTENER_H_
#define TARGETHUMIDITYINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity interface controllee listener class
 */
class TargetHumidityIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of TargetHumidityIntfControlleeListener
     */
    virtual ~TargetHumidityIntfControlleeListener() {}

    /**
     * Handler for setting target humidity
     * @param[in] value the target humidity
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetValue(const uint8_t value) = 0;

    /**
     * Handler for getting target humidity
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the target humidity
     * @return ER_OK on success
     */
    virtual QStatus OnGetTargetValue(uint8_t& value) = 0;

    /**
     * Handler for getting the minimum value of target humidity
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the minimum value of target humidity
     * @return ER_OK on success
     */
    virtual QStatus OnGetMinValue(uint8_t& value) = 0;


    /**
     * Handler for getting the maximum value of target humidity
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum value of target humidity
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxValue(uint8_t& value) = 0;


    /**
     * Handler for getting the step value of target humidity
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the step value of target humidity
     * @return ER_OK on success
     */
    virtual QStatus OnGetStepValue(uint8_t& value) = 0;

    /**
     * Handler for getting the selectable humidity levels
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the selectable humidity levels
     * @return ER_OK on success
     */
    virtual QStatus OnGetSelectableHumidityLevels(TargetHumidityInterface::HumidityLevels& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLEELISTENER_H_ */