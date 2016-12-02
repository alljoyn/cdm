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

#ifndef CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_
#define CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode interface controller listener class
 */
class ClimateControlModeIntfControllerListener : public InterfaceControllerListener {
  public:
    typedef std::vector<uint16_t> SupportedModes;

    /**
     * Destructor of ClimateControlModeIntfControllerListener
     */
    virtual ~ClimateControlModeIntfControllerListener() {}

    /**
     * Callback handler for setting Mode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting Mode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for getting SupportedModes property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value supported mdoes
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context) {}

    /**
     * Callback handler for getting OperationalState property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value operational state
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for Mode property changed
     * @param[in] objectPath the object path
     * @param[in] value mode
     */
    virtual void OnModeChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for SupportedModes property changed
     * @param[in] objectPath the object path
     * @param[in] value supported modes
     */
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value) {}

    /**
     * Handler for OperationalState property changed
     * @param[in] objectPath the object path
     * @param[in] value operational state
     */
    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const uint16_t value) {}

};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_ */