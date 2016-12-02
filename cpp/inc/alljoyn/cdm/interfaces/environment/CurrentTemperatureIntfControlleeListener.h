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

#ifndef CURRENTTEMPERATUREINTFCONTROLLEELISTENER_H_
#define CURRENTTEMPERATUREINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentTemperature interface controllee listener class
 */
class CurrentTemperatureIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of CurrentTemperatureIntfControlleeListener
     */
    virtual ~CurrentTemperatureIntfControlleeListener() {}

    /**
     * Handler for getting current temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] CurrentTemperature the current temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentValue(double& value) = 0;

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

#endif /* CURRENTTEMPERATUREINTFCONTROLLEELISTENER_H_ */