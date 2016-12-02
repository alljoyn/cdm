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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLEELISTENER_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel interface controllee listener class
 */
class TargetTemperatureLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of TargetTemperatureLevelIntfControlleeListener
     */
    virtual ~TargetTemperatureLevelIntfControlleeListener() {}

    /**
     * Handler for setting target temperature level
     * @param[in] value the target temperature level
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetLevel(const uint8_t value) = 0;

    /**
     * Handler for getting target temperature level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the target temperature level
     * @return ER_OK on success
     */
    virtual QStatus OnGetTargetLevel(uint8_t& value) = 0;

    /**
     * Handler for getting the maximum level of target temperature level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum value of target temperature level
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxLevel(uint8_t& value) = 0;

    /**
     * Handler for getting the selectable temperature levels
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the selectable temperature levels
     * @return ER_OK on success
     */
    virtual QStatus OnGetSelectableTemperatureLevels(TargetTemperatureLevelInterface::TemperatureLevels& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLEELISTENER_H_ */