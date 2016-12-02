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

#ifndef TIMEDISPLAYINTFCONTROLLEELISTENER_H_
#define TIMEDISPLAYINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controllee Listener class
 */
class TimeDisplayIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of TimeDisplayIntfControlleeListener
     */
    virtual ~TimeDisplayIntfControlleeListener() {}

    /**
     * Handler for setting DisplayTimeFormat property
     * @param[in] timeFormat time format
     * @return ER_OK on success
     */
    virtual QStatus OnSetDisplayTimeFormat(const uint8_t timeFormat) = 0;

    /**
     * Handler for getting DisplayTimeFormat property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] timeFormat time format
     * @return ER_OK on success
     */
    virtual QStatus OnGetDisplayTimeFormat(uint8_t& timeFormat) = 0;

    /**
     * Handler for getting SupportedDisplayTimeFormats
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] selectableLevels the list of selectable levels
     * @return ER_OK on success
     */
    virtual QStatus OnGetSupportedDisplayTimeFormats(std::vector<uint8_t>& supportedDisplayTimeFormats) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLEELISTENER_H_ */