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

#ifndef WATERLEVELINTERFACE_H_
#define WATERLEVELINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface class
 */
class WaterLevelInterface : public CdmInterface {
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
    const CdmInterfaceType GetInterfaceType() const { return WATER_LEVEL_INTERFACE; }

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