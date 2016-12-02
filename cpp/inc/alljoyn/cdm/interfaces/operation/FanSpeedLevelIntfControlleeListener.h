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

#ifndef FANSPEEDLEVELINTFCONTROLLEELISTENER_H_
#define FANSPEEDLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controllee Listener class
 */
class FanSpeedLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of FanSpeedLevelIntfControlleeListener
     */
    virtual ~FanSpeedLevelIntfControlleeListener() {}

    /**
     * Handler for setting FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus OnSetFanSpeedLevel(const uint8_t& value) = 0;

    /**
     * Handler for getting FanSpeedLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] FanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetFanSpeedLevel(uint8_t& value) = 0;

    /**
     * Handler for getting MaxFanSpeedLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] MaxFanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxFanSpeedLevel(uint8_t& value) = 0;

    /**
     * Handler for setting AutoMode
     * @param[in] AutoMode
     * @return ER_OK on success
     */
    virtual QStatus OnSetAutoMode(const uint8_t& value) = 0;

    /**
     * Handler for getting AutoMode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] AutoMode
     * @return ER_OK on success
     */
    virtual QStatus OnGetAutoMode(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEELISTENER_H_ */