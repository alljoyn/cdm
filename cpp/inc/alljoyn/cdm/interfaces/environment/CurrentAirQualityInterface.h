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

#ifndef CURRENTAIRQUALITYINTERFACE_H_
#define CURRENTAIRQUALITYINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQuality Interface class
 */
class CurrentAirQualityInterface : public CdmInterface {
  public:
    /**
     * Constructor of CurrentAirQuality
     */
    CurrentAirQualityInterface() {}

    /**
     * Destructor of CurrentAirQuality
     */
    virtual ~CurrentAirQualityInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CURRENT_AIR_QUALITY_INTERFACE; }

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
        CONTAMINANT_TYPE_VOC = 5
    };
    enum {
        DEFAULT_MAX_VALUE = 0x7FF0000000000000,
        DEFAULT_MIN_VALUE = 0x0
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_ContaminantType;
    static const qcc::String s_prop_CurrentValue;
    static const qcc::String s_prop_MaxValue;
    static const qcc::String s_prop_MinValue;
    static const qcc::String s_prop_Precision;
    static const qcc::String s_prop_UpdateMinTime;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYINTERFACE_H_ */