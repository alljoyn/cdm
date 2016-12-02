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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLEE_H_
#define TEMPERATUREDISPLAYINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controllee class
 */
class TemperatureDisplayIntfControllee : public TemperatureDisplayInterface {
  public:
    /**
     * Constructor of TemperatureDisplayIntfControllee
     */
    TemperatureDisplayIntfControllee() {}

    /**
     * Destructor of TemperatureDisplayIntfControllee
     */
    virtual ~TemperatureDisplayIntfControllee() {}

    /**
     * Get DisplayTemperatureUnit
     * @return display temperature unit
     */

    virtual const uint8_t GetDisplayTemperatureUnit() = 0;

    /**
     * Set DisplayTemperatureUnit
     * @param[in] temperatureUnit temperature Unit
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t temperatureUnit) = 0;

    /**
     * Get SupportedDisplayTemperatureUnits
     * @return list of supported temerature units
     */
    virtual const std::vector<uint8_t>& GetSupportedDisplayTemperatureUnits() = 0;

    /**
     * Set SupportedDisplayTemperatureUnits
     * @param[in] supportedTemperatureUnits list of supported temperature units
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayTemperatureUnits(const std::vector<uint8_t>& supportedTemperatureUnits) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLEE_H_ */