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

#ifndef HVACFANMODEINTFCONTROLLEE_H_
#define HVACFANMODEINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeInterface.h>

namespace ajn {
namespace services {

/**
 * HvacFanMode Interface Controllee class
 */
class HvacFanModeIntfControllee : public HvacFanModeInterface {
  public:
    /**
     * Constructor of HvacFanMode
     */
    HvacFanModeIntfControllee() {}

    /**
     * Destructor of HvacFanMode
     */
    virtual ~HvacFanModeIntfControllee() {}

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
};

} //namespace services
} //namespace ajn

#endif /* HVACFANMODEINTFCONTROLLEE_H_ */