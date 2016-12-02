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

#ifndef FANSPEEDLEVELINTFCONTROLLERLISTENER_H_
#define FANSPEEDLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface Controller Listener class
 */
class FanSpeedLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~FanSpeedLevelIntfControllerListener() {}

    /**
     * Callback handler for setting FanSpeedLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetFanSpeedLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting FanSpeedLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] FanSpeedLevel
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxFanSpeedLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] MaxFanSpeedLevel
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxFanSpeedLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for setting AutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting AutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] AutoMode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for FanSpeedLevel property changed
     * @param[in] objectPath the object path
     * @param[in] FanSpeedLevel
     */
    virtual void OnFanSpeedLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for FanSpeedLevel property changed
     * @param[in] objectPath the object path
     * @param[in] AutoMode
     */
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t value) {}

};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTFCONTROLLERLISTENER_H_ */