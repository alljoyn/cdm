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

#ifndef CLIMATECONTROLMODEINTFCONTROLLEE_H_
#define CLIMATECONTROLMODEINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface Controllee class
 */
class ClimateControlModeIntfControllee : public ClimateControlModeInterface {
  public:
    /**
     * Constructor of ClimateControlMode
     */
    ClimateControlModeIntfControllee() {}

    /**
     * Destructor of ClimateControlMode
     */
    virtual ~ClimateControlModeIntfControllee() {}

    /**
     * Get mode
     * @return Mode
     */
    virtual const uint16_t GetMode() const = 0;

    /**
     * Set mode
     * @param[in] mode mode
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const uint16_t mode) = 0;

    /**
     * Get supported modes
     * @return Supported modes
     */
    virtual const SupportedModes& GetSupportedModes() const = 0;

    /**
     * Set supported modes
     * @param[in] modes supported modes
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedModes(const SupportedModes& modes) = 0;

    /**
     * Get operational state
     * @return Operational state
     */
    virtual const uint16_t GetOperationalState() const = 0;

    /**
     * Set operational state
     * @param[in] state operational state
     * @return ER_OK on success
     */
    virtual QStatus SetOperationalState(const uint16_t state) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLEE_H_ */