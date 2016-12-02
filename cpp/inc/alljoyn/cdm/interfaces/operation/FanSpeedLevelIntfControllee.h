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

#ifndef FANSPEEDLEVELINTFCONTROLLEE_H_
#define FANSPEEDLEVELINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelInterface.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controllee class
 */
class FanSpeedLevelIntfControllee : public FanSpeedLevelInterface {
  public:
    /**
     * Constructor of FanSpeedLevelIntfControllee
     */
    FanSpeedLevelIntfControllee() {}

    /**
     * Destructor of FanSpeedLevelIntfControllee
     */
    virtual ~FanSpeedLevelIntfControllee() {}

    /**
     * Get FanSpeedLevel
     * @return FanSpeedLevel
     */
    virtual const uint8_t GetFanSpeedLevel() const = 0;

    /**
     * Set FanSpeedLevel
     * @param[in] FanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus SetFanSpeedLevel (const uint8_t value) = 0;

    /**
     * Get MaxFanSpeedLevel
     * @return MaxFanSpeedLevel
     */
    virtual const uint8_t GetMaxFanSpeedLevel() const = 0;

    /**
     * Set MaxFanSpeedLevel
     * @param[in] MaxFanSpeedLevel
     * @return ER_OK on success
     */
    virtual QStatus SetMaxFanSpeedLevel(const uint8_t value) = 0;

    /**
     * Get AutoMode
     * @return AutoMode
     */
    virtual const uint8_t GetAutoMode() const = 0;

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @return ER_OK on success
     */
    virtual QStatus SetAutoMode(const uint8_t value) = 0;

};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLEE_H_ */