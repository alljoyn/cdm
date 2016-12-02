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

#ifndef CURRENTPOWERINTFCONTROLLERLISTENER_H_
#define CURRENTPOWERINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentPower Interface Controller Listener class
 */
class CurrentPowerIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~CurrentPowerIntfControllerListener() {}

    /**
     * Callback handler for getting CurrentPower property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] CurrentPower
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentPower(QStatus status, const qcc::String& objectPath, const double currentPower, void* context) {}

    /**
     * Callback handler for getting Precision property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] Precision
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetPrecision(QStatus status, const qcc::String& objectPath, const double precision, void* context) {}

    /**
     * Callback handler for getting UpdateMinTime property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetUpdateMinTime(QStatus status, const qcc::String& objectPath, const uint16_t updateMinTime, void* context) {}

    /**
     * Handler for CurrentPower property changed
     * @param[in] objectPath the object path
     * @param[in] CurrentPower
     */
    virtual void OnCurrentPowerChanged(const qcc::String& objectPath, const double currentPower) {}

    /**
     * Handler for Precision property changed
     * @param[in] objectPath the object path
     * @param[in] Precision
     */
    virtual void OnPrecisionChanged(const qcc::String& objectPath, const double precision) {}

    /**
     * Handler for UpdateMinTime property changed
     * @param[in] objectPath the object path
     * @param[in] UpdateMinTime
     */
    virtual void OnUpdateMinTimeChanged(const qcc::String& objectPath, const uint16_t updateMinTime) {}
};

} //namespace services
} //namespace ajn

#endif /* CURRENTPOWERINTFCONTROLLERLISTENER_H_ */