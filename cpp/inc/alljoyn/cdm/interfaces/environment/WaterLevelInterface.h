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

#ifndef WATERLEVELINTERFACE_H_
#define WATERLEVELINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface class
 */
class WaterLevelInterface : public HaeInterface {
  public:
    typedef enum
    {
        SUPPLY_SOURCE_TANK,
        SUPPLY_SOURCE_PIPE,
        SUPPLY_SOURCE_NOT_SUPPORTED = 0xFF
    }WaterLevelSupplySource;
    /**
     * Constructor of WaterLevel
     */
    WaterLevelInterface() {}

    /**
     * Destructor of WaterLevel
     */
    virtual ~WaterLevelInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const HaeInterfaceType GetInterfaceType() const { return WATER_LEVEL_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return xml
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_SupplySource;
    static const qcc::String s_prop_CurrentLevel;
    static const qcc::String s_prop_MaxLevel;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTERFACE_H_ */
