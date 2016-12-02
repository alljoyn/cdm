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

#ifndef FANSPEEDLEVELINTERFACE_H_
#define FANSPEEDLEVELINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * FanSpeedLevel Interface class
 */
class FanSpeedLevelInterface : public CdmInterface {
  public:
    /**
     * Constructor of FanSpeedLevel
     */
    FanSpeedLevelInterface() {}

    /**
     * Destructor of FanSpeedLevel
     */
    virtual ~FanSpeedLevelInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return FAN_SPEED_LEVEL_INTERFACE; }

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
        FAN_TURNED_OFF = 0
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_FanSpeedLevel;
    static const qcc::String s_prop_MaxFanSpeedLevel;
    static const qcc::String s_prop_AutoMode;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* FANSPEEDLEVELINTERFACE_H_ */