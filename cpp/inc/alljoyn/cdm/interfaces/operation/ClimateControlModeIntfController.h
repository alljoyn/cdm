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

#ifndef CLIMATECONTROLMODEINTFCONTROLLER_H_
#define CLIMATECONTROLMODEINTFCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface Controller class
 */
class ClimateControlModeIntfController : public ClimateControlModeInterface {
  public:
    /**
     * Constructor of ClimateControlMode
     */
    ClimateControlModeIntfController() {}

    /**
     * Destructor of ClimateControlMode
     */
    virtual ~ClimateControlModeIntfController() {}

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

    /**
     * Get operational state
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOperationalState(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLER_H_ */