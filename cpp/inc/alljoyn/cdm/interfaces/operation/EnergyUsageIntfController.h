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

#ifndef ENERGYUSAGEINTFCONTROLLER_H_
#define ENERGYUSAGEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageInterface.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface Controller class
 */
class EnergyUsageIntfController : public EnergyUsageInterface {
  public:
    /**
     * Constructor of EnergyUsageIntfController
     */
    EnergyUsageIntfController() {}

    /**
     * Destructor of EnergyUsageIntfController
     */
    virtual ~EnergyUsageIntfController() {}

    /**
     * Get cumulative energy
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCumulativeEnergy(void* context = NULL) = 0;

    /**
     * Get precision
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPrecision(void* context = NULL) = 0;

    /**
     * Get the minimum update time
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetUpdateMinTime(void* context = NULL) = 0;

    /**
     * Reset cumulative energy
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus ResetCumulativeEnergy(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLER_H_ */