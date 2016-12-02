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

#ifndef CURRENTHUMIDITYINTFCONTROLLEELISTENER_H_
#define CURRENTHUMIDITYINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity interface controllee listener class
 */
class CurrentHumidityIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of CurrentHumidityIntfControlleeListener
     */
    virtual ~CurrentHumidityIntfControlleeListener() {}

    /**
     * Handler for getting current humidity
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] CurrentHumidity the current humidity
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentValue(uint8_t& value) = 0;

    /**
     * Handler for getting MaxValue
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value max humidity
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxValue(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTHUMIDITYINTFCONTROLLEELISTENER_H_ */