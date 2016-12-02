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

#ifndef HVACFANMODEINTERFACE_H_
#define HVACFANMODEINTERFACE_H_


#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * HvacFanMode Interface class
 */
class HvacFanModeInterface : public CdmInterface {
  public:
    typedef std::vector<uint16_t> SupportedModes;

    /**
     * Constructor of HvacFanModeInterface
     */
    HvacFanModeInterface() {}

    /**
     * Destructor of HvacFanModeInterface
     */
    virtual ~HvacFanModeInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return HVAC_FAN_MODE_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return Introspection xml
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return Interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

    enum {
        HVAC_FAN_MODE_AUTO = 0,
        HVAC_FAN_MODE_CIRCULATION,
        HVAC_FAN_MODE_CONTINUOUS
    };

    enum {
        MIN_HVAC_FAN_MODE = HVAC_FAN_MODE_AUTO,
        MAX_HVAC_FAN_MODE = HVAC_FAN_MODE_CONTINUOUS
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_Mode;
    static const qcc::String s_prop_SupportedModes;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* HVACFANMODEINTERFACE_H_ */