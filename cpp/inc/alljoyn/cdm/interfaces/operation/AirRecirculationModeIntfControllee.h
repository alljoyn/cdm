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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLEE_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeInterface.h>

namespace ajn {
namespace services {

/**
 * AirRecirculationMode Interface Controllee class
 */
class AirRecirculationModeIntfControllee : public AirRecirculationModeInterface {
  public:
    /**
     * Constructor of AirRecirculationModeIntfControllee
     */
    AirRecirculationModeIntfControllee() {}

    /**
     * Destructor of AirRecirculationModeIntfControllee
     */
    virtual ~AirRecirculationModeIntfControllee() {}

    /**
     * Set if air is being recirculated
     * @param[in] isRecirculating if air is being recirculated or not
     * @return ER_OK on success
     */
    virtual QStatus SetIsRecirculating(const bool isRecirculating) = 0;

    /**
     * Get if air is being recirculated
     * @return If air is being recirculated or not
     */
    virtual const bool GetIsRecirculating() const = 0;
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLEE_H_ */