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

#ifndef RAPIDMODETIMEDINTFCONTROLLEE_H_
#define RAPIDMODETIMEDINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedInterface.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controllee class
 */
class RapidModeTimedIntfControllee : public RapidModeTimedInterface {
  public:
    /**
     * Constructor of RapidModeTimedIntfControllee
     */
    RapidModeTimedIntfControllee() {}

    /**
     * Destructor of RapidModeTimedIntfControllee
     */
    virtual ~RapidModeTimedIntfControllee() {}

    /**
     * Get time remaining in rapid mode
     * @return Time remaining in rapid mode
     */
    virtual const uint16_t GetRapidModeMinutesRemaining() const = 0;

    /**
     * Set time remaining in rapid mode
     * @param[in] value time remaining in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus SetRapidModeMinutesRemaining(const uint16_t value) = 0;

    /**
     * Get the maximum rapid mode set time
     * @return The maximum rapid mode set time
     */
    virtual const uint16_t GetMaxSetMinutes() const = 0;

    /**
     * Set the maximum rapid mode set time
     * @param[in] value the maximum rapid mode set time
     * @return ER_OK on success
     */
    virtual QStatus SetMaxSetMinutes(const uint16_t value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLEE_H_ */