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

#ifndef CURRENTTEMPERATUREINTERFACE_H_
#define CURRENTTEMPERATUREINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * CurrentTemperature Interface class
 */
class CurrentTemperatureInterface : public CdmInterface {
  public:

    /**
     * Constructor of CurrentTemperatureInterface
     */
    CurrentTemperatureInterface() {}

    /**
     * Destructor of CurrentTemperatureInterface
     */
    virtual ~CurrentTemperatureInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CURRENT_TEMPERATURE_INTERFACE; }

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
    static const qcc::String s_prop_CurrentValue;
    static const qcc::String s_prop_Precision;
    static const qcc::String s_prop_UpdateMinTime;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* CURRENTTEMPERATUREINTERFACE_H_ */