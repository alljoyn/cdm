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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLER_H_
#define TEMPERATUREDISPLAYINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface Controller class
 */
class TemperatureDisplayIntfController : public TemperatureDisplayInterface {
  public:
    /**
     * Constructor of TemperatureDisplayIntfController
     */
    TemperatureDisplayIntfController() {}

    /**
     * Destructor of TemperatureDisplayIntfController
     */
    virtual ~TemperatureDisplayIntfController() {}

    /**
     * Get DisplayTemperatureUnit
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTemperatureUnit(void* context = NULL) = 0;

    /**
     * Set DisplayTemperatureUnit
     * @param[in] temperatureUnit temperature unit
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t temperatureUnit, void* context = NULL) = 0;

    /**
     * Get SupportedDisplayTemperatureUnits
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTemperatureUnits(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLER_H_ */