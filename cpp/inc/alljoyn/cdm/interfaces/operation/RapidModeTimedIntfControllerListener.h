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

#ifndef RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_
#define RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * RapidModeTimed Interface Controller Listener class
 */
class RapidModeTimedIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RapidModeTimedIntfControllerListener() {}

    /**
     * Handler for RapidModeMinutesRemaining property changed
     * @param[in] objectPath the object path
     * @param[in] value time remaining in rapid mode
     */
    virtual void OnRapidModeMinutesRemainingChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for getting RapidModeMinutesRemaining property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value time remaining in rapid mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for setting RapidModeMinutesRemaining property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetRapidModeMinutesRemaining(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting MaxSetMinutes property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum rapid mode set time
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxSetMinutes(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLERLISTENER_H_ */