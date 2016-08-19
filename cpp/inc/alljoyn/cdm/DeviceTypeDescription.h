/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
