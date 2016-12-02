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


#ifndef DEVICETYPEDESCRIPTION_H_
#define DEVICETYPEDESCRIPTION_H_

#include <map>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/CdmConfig.h>

namespace ajn {
namespace services {

/**
 * Cdm device type description class.
 */
class DeviceTypeDescription {
  public:

    typedef std::multimap<DeviceType, qcc::String> DescriptionsType;

    /**
     * Constructor of DeviceTypeDescription
     */
    DeviceTypeDescription();

    /**
     * Destructor of DeviceTypeDescription
     */
    virtual ~DeviceTypeDescription();

    /**
     * Add device type to specific object path
     * @param[in] type device type
     * @param[in] objectPath the object path including the device type
     * @return ER_OK on success
     */
    QStatus AddDeviceType(DeviceType type, const qcc::String& objectPath);

    /**
     * Reset the device type descriptions
     */
    void ResetDescriptions();

    /**
     * Get device type descriptions
     * @return Device type descriptions
     */
    const DescriptionsType& GetDescriptions() const;

  private:
    DescriptionsType m_descriptions;
};

}
}

#endif // DEVICETYPEDESCRIPTION_H_