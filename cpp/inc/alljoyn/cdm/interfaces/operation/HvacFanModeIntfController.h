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

#ifndef HVACFANMODEINTFCONTROLLER_H_
#define HVACFANMODEINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeInterface.h>

namespace ajn {
namespace services {

/**
 * HvacFanMode Interface Controller class
 */
class HvacFanModeIntfController : public HvacFanModeInterface {
  public:
    /**
     * Constructor of HvacFanMode
     */
    HvacFanModeIntfController() {}

    /**
     * Destructor of HvacFanMode
     */
    virtual ~HvacFanModeIntfController() {}

    /**
     * Get mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMode(void* context = NULL) = 0;

    /**
     * Set mode
     * @param[in] mode mode
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const uint16_t mode, void* context = NULL) = 0;

    /**
     * Get supported modes
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedModes(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HVACFANMODEINTFCONTROLLER_H_ */