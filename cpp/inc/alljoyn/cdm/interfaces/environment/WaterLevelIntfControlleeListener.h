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

#ifndef WATERLEVELINTFCONTROLLEELISTENER_H_
#define WATERLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelInterface.h>


namespace ajn {
namespace services {

/**
 * WaterLevel Interface Controllee Listener class
 */
class WaterLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of WaterLevelIntfControlleeListener
     */
    virtual ~WaterLevelIntfControlleeListener() {}

    /**
     * Handler for getting currentLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] currentLevel currentLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetCurrentLevel(uint8_t& currentLevel) = 0;

    /**
     * Handler for getting maxLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxLevel(uint8_t& maxLevel)  = 0;

    /**
     * Handler for getting supplySource
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] supplySource supplySource
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupplySource(WaterLevelInterface::WaterLevelSupplySource& supplySource)  = 0;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLEELISTENER_H_ */