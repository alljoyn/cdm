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

#ifndef CURRENTAIRQUALITYLEVELINTERFACE_H_
#define CURRENTAIRQUALITYLEVELINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface class
 */
class CurrentAirQualityLevelInterface : public CdmInterface {
  public:
    /**
     * Constructor of CurrentAirQualityLevel
     */
    CurrentAirQualityLevelInterface() {}

    /**
     * Destructor of CurrentAirQualityLevel
     */
    virtual ~CurrentAirQualityLevelInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CURRENT_AIR_QUALITY_LEVEL_INTERFACE; }

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

    enum {
        CONTAMINANT_TYPE_CH20 = 0,
        CONTAMINANT_TYPE_CO2 = 1,
        CONTAMINANT_TYPE_CO = 2,
        CONTAMINANT_TYPE_PM2_5 = 3,
        CONTAMINANT_TYPE_PM10 = 4,
        CONTAMINANT_TYPE_VOC = 5,
        CONTAMINANT_TYPE_SMOKE = 253,
        CONTAMINANT_TYPE_ODOR = 254,
        CONTAMINANT_TYPE_AIR_POLLUTION = 255
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_ContaminantType;
    static const qcc::String s_prop_CurrentLevel;
    static const qcc::String s_prop_MaxLevel;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTERFACE_H_ */
