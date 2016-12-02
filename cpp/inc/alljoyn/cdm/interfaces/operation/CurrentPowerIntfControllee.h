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

#ifndef CURRENTPOWERINTFCONTROLLEE_H_
#define CURRENTPOWERINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentPower Interface Controllee class
 */
class CurrentPowerIntfControllee : public CurrentPowerInterface
{
public:
    /**
     * Constructor of CurrentPowerIntfControllee
     */
    CurrentPowerIntfControllee()
    {
    }

    /**
     * Destructor of CurrentPowerIntfControllee
     */
    virtual ~CurrentPowerIntfControllee()
    {
    }

    /**
     * Get CurrentPower
     * @return CurrentPower
     */
    virtual const double GetCurrentPower() const = 0;

    /**
     * Set CurrentPower
     * @param[in] CurrentPower
     * @return ER_OK on success
     */
    virtual QStatus SetCurrentPower(const double currentPower) = 0;

    /**
     * Get Precision
     * @return Precision
     */
    virtual const double GetPrecision() const = 0;

    /**
     * Set Precision
     * @param[in] Precision
     * @return ER_OK on success
     */
    virtual QStatus SetPrecision(const double precision) = 0;

    /**
     * Get UpdateMinTime
     * @return UpdateMinTime
     */
    virtual const uint16_t GetUpdateMinTime() const = 0;

    /**
     * Set UpdateMinTime
     * @param[in] UpdateMinTime
     * @return ER_OK on success
     */
    virtual QStatus SetUpdateMinTime(const uint16_t updateMinTime) = 0;
};

}  //namespace services
}  //namespace ajn

#endif /* CURRENTPOWERINTFCONTROLLEE_H_ */