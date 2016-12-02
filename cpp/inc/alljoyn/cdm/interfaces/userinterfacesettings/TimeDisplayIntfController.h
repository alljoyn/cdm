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

#ifndef TIMEDISPLAYINTFCONTROLLER_H_
#define TIMEDISPLAYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controller class
 */
class TimeDisplayIntfController : public TimeDisplayInterface {
  public:
    /**
     * Constructor of TimeDisplayIntfController
     */
    TimeDisplayIntfController() {}

    /**
     * Destructor of TimeDisplayIntfController
     */
    virtual ~TimeDisplayIntfController() {}

    /**
     * Get DisplayTimeFormat
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTimeFormat(void* context = NULL) = 0;

    /**
     * Set DisplayTimeFormat
     * @param[in] timeformat time format
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t timeFormat, void* context = NULL) = 0;

    /**
     * Get SupportedDisplayTimeFormats
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTimeFormats(void* context = NULL) = 0;

};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLER_H_ */