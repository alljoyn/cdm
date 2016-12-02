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

#ifndef HEATINGZONEINTFCONTROLLEELISTENER_H_
#define HEATINGZONEINTFCONTROLLEELISTENER_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * HeatingZone Interface Controllee Listener class
 */
class HeatingZoneIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of HeatingZoneIntfControlleeListener
     */
    virtual ~HeatingZoneIntfControlleeListener() {}

    /**
     * Handler for getting number of heating zones
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] currentState currentState
     * @return ER_OK on success
     */
    virtual QStatus OnGetNumberOfHeatingZones(uint8_t& currentState) = 0;
    /**
     * Handler for getting max heating levels
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] maxHeatingLevels maxHeatingLevels
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxHeatingLevels(std::vector<uint8_t>& maxHeatingLevels) = 0;
    /**
     * Handler for getting heating levels
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] heatingLevels heatingLevels
     * @return ER_OK on success
     */
    virtual QStatus OnGetHeatingLevels(std::vector<uint8_t>& heatingLevels) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLEELISTENER_H_ */