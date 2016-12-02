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

#ifndef CURRENTAIRQUALITYINTFCONTROLLEELISTENER_H_
#define CURRENTAIRQUALITYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface Controllee Listener class
 */
class CurrentAirQualityIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of CurrentAirQualityIntfControlleeListener
     */
    virtual ~CurrentAirQualityIntfControlleeListener() {}

    /**
     * Handler for getting the contatminant type
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] type the contaminant type
     * @return ER_OK on success
     */
    virtual QStatus OnGetContaminantType(uint8_t& type) = 0;

    /**
     * Handler for getting current air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentValue(double& value) = 0;

    /**
     * Handler for getting the maximum value of air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum value of air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxValue(double& value) = 0;

    /**
     * Handler for getting the minimum value of air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the minimum value of air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetMinValue(double& value) = 0;

    /**
     * Handler for getting Precision
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] Precision precision
     * @return ER_OK on success
     */
    virtual QStatus OnGetPrecision(double& precision) = 0;

    /**
     * Handler for getting UpdateMinTime
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] UpdateMinTime the minimum time between updates
     * @return ER_OK on success
     */
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTFCONTROLLEELISTENER_H_ */