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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLERLISTENER_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * AirRecirculationMode Interface Controller Listener class
 */
class AirRecirculationModeIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~AirRecirculationModeIntfControllerListener() {}

    /**
     * Callback handler for setting IsRecirculating property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting IsRecirculating property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isRecirculating if air is being recirculated or not
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context) {}

    /**
     * Handler for IsRecirculating property changed
     * @param[in] objectPath the object path
     * @param[in] isRecirculating if air is being recirculated or not
     */
    virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating) {}
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLERLISTENER_H_ */