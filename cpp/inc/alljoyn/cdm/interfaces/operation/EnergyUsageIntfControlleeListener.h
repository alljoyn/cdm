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

#ifndef ENERGYUSAGEINTFCONTROLLEELISTENER_H_
#define ENERGYUSAGEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * EnergyUsage Interface Controllee Listener class
 */
class EnergyUsageIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of EnergyUsageIntfControlleeListener
     */
    virtual ~EnergyUsageIntfControlleeListener() {}

    /**
     * Handler for getting CumulativeEnergy property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] cumulativeEnergy cumulative energy
     * @return ER_OK on success
     */
    virtual QStatus OnGetCumulativeEnergy(double& cumulativeEnergy) = 0;

    /**
     * Handler for getting Precision property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] precision precision
     * @return ER_OK on success
     */
    virtual QStatus OnGetPrecision(double& precision) = 0;

    /**
     * Handler for getting UpdateMinTime property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] updateMinTime the minimum update time
     * @return ER_OK on success
     */
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime) = 0;

    /**
     * Handler for ResetCumulativeEnergy method
     * @param[out] errorCode the error code should be set when the method call is failed
     * @return ER_OK on succes
     */
    virtual QStatus OnResetCumulativeEnergy(ErrorCode& errorCode) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLEELISTENER_H_ */