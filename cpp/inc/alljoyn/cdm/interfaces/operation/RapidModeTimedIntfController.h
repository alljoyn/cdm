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

#ifndef RAPIDMODETIMEDINTFCONTROLLER_H_
#define RAPIDMODETIMEDINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedInterface.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controller class
 */
class RapidModeTimedIntfController : public RapidModeTimedInterface {
  public:
    /**
     * Constructor of RapidModeTimedIntfController
     */
    RapidModeTimedIntfController() {}

    /**
     * Destructor of RapidModeTimedIntfController
     */
    virtual ~RapidModeTimedIntfController() {}

    /**
     * Get time remaining in rapid mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetRapidModeMinutesRemaining(void* context = NULL) = 0;

    /**
     * Set time remaining in rapid mode
     * @param[in] value time remaining in rapid mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetRapidModeMinutesRemaining(const uint16_t value, void* context = NULL) = 0;

    /**
     * Get the maximum rapid mode set time
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxSetMinutes(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLER_H_ */