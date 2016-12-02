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

#ifndef HEATINGZONEINTFCONTROLLER_H_
#define HEATINGZONEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneInterface.h>

namespace ajn {
namespace services {

/**
 * HeatingZone Interface Controller class
 */
class HeatingZoneIntfController : public HeatingZoneInterface {
  public:
    /**
     * Constructor of HeatingZoneIntfController
     */
    HeatingZoneIntfController() {}

    /**
     * Destructor of HeatingZoneIntfController
     */
    virtual ~HeatingZoneIntfController() {}

    /**
     * Get number of heating zones
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetNumberOfHeatingZones(void* context = NULL) = 0;

    /**
     * Get list of maximum heating levels
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxHeatingLevels(void* context = NULL) = 0;

    /**
     * Get list current heating levels
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHeatingLevels(void* context = NULL) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLER_H_ */