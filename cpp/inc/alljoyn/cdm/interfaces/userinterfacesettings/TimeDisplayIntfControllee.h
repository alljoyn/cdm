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

#ifndef TIMEDISPLAYINTFCONTROLLEE_H_
#define TIMEDISPLAYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controllee class
 */
class TimeDisplayIntfControllee : public TimeDisplayInterface {
  public:
    /**
     * Constructor of TimeDisplayIntfControllee
     */
    TimeDisplayIntfControllee() {}

    /**
     * Destructor of TimeDisplayIntfControllee
     */
    virtual ~TimeDisplayIntfControllee() {}
    
    /**
     * Get DisplayTimeFormat
     * @return display time format
     */
    virtual const uint8_t GetDisplayTimeFormat() = 0;

    /**
     * Set DisplayTimeFormat
     * @param[in] timeFormat timeFormat
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t timeFormat) = 0;

    /**
     * Get SupportedDisplayTimeFormats
     * @return list of supported time formats
     */
    virtual const std::vector<uint8_t>& GetSupportedDisplayTimeFormats() = 0;

    /**
     * Set SupportedDisplayTimeFormats
     * @param[in] supportedTimeFormats list of supported time formats
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayTimeFormats(const std::vector<uint8_t>& supportedTimeFormats) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLEE_H_ */