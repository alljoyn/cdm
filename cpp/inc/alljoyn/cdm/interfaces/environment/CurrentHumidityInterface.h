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

#ifndef CURRENTHUMIDITYINTERFACE_H_
#define CURRENTHUMIDITYINTERFACE_H_


#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentHumidity Interface class
 */
class CurrentHumidityInterface : public CdmInterface {
  public:

    /**
     * Constructor of CurrentHumidityInterface
     */
    CurrentHumidityInterface() {}

    /**
     * Destructor of CurrentHumidityInterface
     */
    virtual ~CurrentHumidityInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CURRENT_HUMIDITY_INTERFACE; }

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
        MAX_HUMIDITY = 100
    };
  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_CurrentValue;
    static const qcc::String s_prop_MaxValue;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* CURRENTHUMIDITYINTERFACE_H_ */