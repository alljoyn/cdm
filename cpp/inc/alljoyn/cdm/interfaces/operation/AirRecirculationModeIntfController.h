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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLER_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeInterface.h>

namespace ajn {
namespace services {

/**
 * AirRecirculationMode Interface Controller class
 */
class AirRecirculationModeIntfController : public AirRecirculationModeInterface {
  public:
    /**
     * Constructor of AirRecirculationModeIntfController
     */
    AirRecirculationModeIntfController() {}

    /**
     * Destructor of AirRecirculationModeIntfController
     */
    virtual ~AirRecirculationModeIntfController() {}

    /**
     * Set if air is being recirculated
     * @param[in] isRecirculating if air is being recirculated or not
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetIsRecirculating(const bool isRecirculating, void* context = NULL) = 0;

    /**
     * Get if air is being recirculated
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetIsRecirculating(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLER_H_ */