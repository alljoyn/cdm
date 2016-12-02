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

#ifndef BATTERYSTATUSINTERFACE_H_
#define BATTERYSTATUSINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * BatteryStatus Interface class
 */
class BatteryStatusInterface : public CdmInterface {
  public:
    /**
     * Constructor of BatteryStatus
     */
    BatteryStatusInterface() {}

    /**
     * Destructor of BatteryStatus
     */
    virtual ~BatteryStatusInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return BATTERY_STATUS_INTERFACE; }

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
        MIN_BATTERY = 0,
        MAX_BATTERY = 100
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_CurrentValue;
    static const qcc::String s_prop_IsCharging;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* BATTERYSTATUSINTERFACE_H_ */