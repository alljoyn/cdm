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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLERLISTENER_H_
#define TEMPERATUREDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controller Listener class
 */
class TemperatureDisplayIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~TemperatureDisplayIntfControllerListener() {}

    /**
     * Callback handler for getting DisplayTemperatureUnit
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] temperatureUnit temperature unit
     * @param[in] context the context that is passed from application
     */
    virtual void GetDisplayTemperatureUnitPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t temperatureUnit, void* context) {};

    /**
     * Callback handler for setting DisplayTemperatureUnit
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void SetDisplayTemperatureUnitPropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {};

    /**
     * Callback handler for getting SupportedDisplayTemperatureUnits
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] SupportedDisplayTemperatureUnits list of supported display temperature units
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedDisplayTemperatureUnitsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& SupportedDisplayTemperatureUnits, void* context) {};

    /**
     * Handler for DisplayTemperatureUnit property changed
     * @param[in] objectPath the object path
     * @param[in] temperatureUnit temperature unit
     */
    virtual void DisplayTemperatureUnitPropertyChanged(const qcc::String& objectPath, const uint8_t temperatureUnit) {};

    /**
     * Handler for SupportedDisplayTemperatureUnits property changed
     * @param[in] objectPath the object path
     * @param[in] SupportedDisplayTemperatureUnits list of supported display temperature units
     */
    virtual void SupportedDisplayTemperatureUnitsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& SupportedDisplayTemperatureUnits) {};
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLERLISTENER_H_ */