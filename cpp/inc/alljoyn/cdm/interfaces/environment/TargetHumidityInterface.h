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

#ifndef TARGETHUMIDITYINTERFACE_H_
#define TARGETHUMIDITYINTERFACE_H_


#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity Interface class
 */
class TargetHumidityInterface : public CdmInterface {
  public:
    typedef std::vector<uint8_t> HumidityLevels;
    enum {
        MIN_HUMIDITY = 0,
        MAX_HUMIDITY = 100
    };

    /**
     * Constructor of TargetHumidityInterface
     */
    TargetHumidityInterface() {}

    /**
     * Destructor of TargetHumidityInterface
     */
    virtual ~TargetHumidityInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return TARGET_HUMIDITY_INTERFACE; }

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

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_TargetValue;
    static const qcc::String s_prop_MinValue;
    static const qcc::String s_prop_MaxValue;
    static const qcc::String s_prop_StepValue;
    static const qcc::String s_prop_SelectableHumidityLevels;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* TARGETHUMIDITYINTERFACE_H_ */