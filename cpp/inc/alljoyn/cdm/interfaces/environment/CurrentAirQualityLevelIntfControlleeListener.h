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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLEELISTENER_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controllee Listener class
 */
class CurrentAirQualityLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of CurrentAirQualityLevelIntfControlleeListener
     */
    virtual ~CurrentAirQualityLevelIntfControlleeListener() {}

    /**
     * Handler for getting the contatminant type
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] type the contaminant type
     * @return ER_OK on success
     */
    virtual QStatus OnGetContaminantType(uint8_t& type) = 0;

    /**
     * Handler for getting current air quality level
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyLevel is true.
     * @param[out] value the air quality level
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentLevel(uint8_t& value) = 0;

    /**
     * Handler for getting the maximum level of air quality
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyLevel is true.
     * @param[out] value the maximum level of air quality
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxLevel(uint8_t& value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLEELISTENER_H_ */