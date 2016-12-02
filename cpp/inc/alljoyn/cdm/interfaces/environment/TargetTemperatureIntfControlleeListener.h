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

#ifndef TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_
#define TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * TargetTemperature interface controllee listener class
 */
class TargetTemperatureIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of TargetTemperatureIntfControlleeListener
     */
    virtual ~TargetTemperatureIntfControlleeListener() {}

    /**
     * Handler for setting target temperature
     * @param[in] value the target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetValue(const double value) = 0;

    /**
     * Handler for getting target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetTargetValue(double& value) = 0;

    /**
     * Handler for getting the minimum value of target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the minimum value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetMinValue(double& value) = 0;


    /**
     * Handler for getting the maximum value of target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxValue(double& value) = 0;


    /**
     * Handler for getting the step value of target temperature
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the step value of target temperature
     * @return ER_OK on success
     */
    virtual QStatus OnGetStepValue(double& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATUREINTFCONTROLLEELISTENER_H_ */