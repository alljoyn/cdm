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
        CONTAMINANT_TYPE_CH2O = 0,
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