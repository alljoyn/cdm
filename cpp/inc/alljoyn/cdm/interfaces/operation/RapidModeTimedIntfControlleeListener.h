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

#ifndef RAPIDMODETIMEDINTFCONTROLLEELISTENER_H_
#define RAPIDMODETIMEDINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controllee Listener class
 */
class RapidModeTimedIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RapidModeTimedIntfControlleeListener
     */
    virtual ~RapidModeTimedIntfControlleeListener() {}

    /**
     * Handler for getting RapidModeMinutesRemaining property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value time remaining in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetRapidModeMinutesRemaining(uint16_t& value) = 0;

    /**
     * Handler for setting RapidModeMinutesRemaining property
     * @param[in] value time remaining in rapid mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetRapidModeMinutesRemaining(const uint16_t& value) = 0;

    /**
     * Handler for getting MaxSetMinutes property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum rapid mode set time
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxSetMinutes(uint16_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLEELISTENER_H_ */