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

#ifndef HEATINGZONEINTFCONTROLLEE_H_
#define HEATINGZONEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <vector>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneInterface.h>

namespace ajn {
namespace services {

/**
 * HeatingZone Interface Controllee class
 */
class HeatingZoneIntfControllee : public HeatingZoneInterface {
  public:
    /**
     * Constructor of HeatingZoneIntfControllee
     */
    HeatingZoneIntfControllee() {}

    /**
     * Destructor of HeatingZoneIntfControllee
     */
    virtual ~HeatingZoneIntfControllee() {}

    /**
     * Get number of heating zones
     * @return NumberOfHeatingZones
     */
    virtual const uint8_t GetNumberOfHeatingZones() const = 0;

    /**
     * Set NumberOfHeatingZones
     * @param[in] numberOfZones number of heating zones
     * @return ER_OK on success
     */
    virtual QStatus SetNumberOfHeatingZones(const uint8_t numberOfZones) = 0;

    /**
     * Get MaxHeatingLevels
     * @return the list of maximum heating levels
     */
    virtual const std::vector<uint8_t>& GetMaxHeatingLevels() const = 0;

    /**
     * Set MaxHeatingLevels
     * @param[in] maxHeatingLevels maxHeatingLevels
     * @return ER_OK on success
     */
    virtual QStatus SetMaxHeatingLevels(const std::vector<uint8_t>& maxHeatingLevels) = 0;

    /**
     * Get HeatingLevels
     * @return the list of heating levels
     */
    virtual const std::vector<uint8_t>& GetHeatingLevels() const = 0;

    /**
     * Set HeatingLevels
     * @param[in] heatingLevels heatingLevels
     * @return ER_OK on success
     */
    virtual QStatus SetHeatingLevels(const std::vector<uint8_t>& heatingLevels) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLEE_H_ */