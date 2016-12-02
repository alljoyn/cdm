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

#ifndef TEMPERATUREDISPLAYINTERFACE_H_
#define TEMPERATUREDISPLAYINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TemperatureDisplay Interface class
 */
class TemperatureDisplayInterface : public CdmInterface {
  public:
    /**
     * Constructor of TemperatureDisplay
     */
    TemperatureDisplayInterface() {}

    /**
     * Destructor of TemperatureDisplay
     */
    virtual ~TemperatureDisplayInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return TEMPERATURE_DISPLAY_INTERFACE; }

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
    static const qcc::String s_prop_DisplayTemperatureUnit;
    static const qcc::String s_prop_SupportedDisplayTemperatureUnits;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTERFACE_H_ */