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

#ifndef WINDDIRECTIONINTERFACE_H_
#define WINDDIRECTIONINTERFACE_H_


#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface class
 */
class WindDirectionInterface : public CdmInterface {
  public:

    /**
     * Constructor of WindDirectionInterface
     */
    WindDirectionInterface() {}

    /**
     * Destructor of WindDirectionInterface
     */
    virtual ~WindDirectionInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return WIND_DIRECTION_INTERFACE; }

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
        OFF = 0x00,
        ON = 0x01,
        NOT_SUPPORTED = 0xff
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_HorizontalDirection;
    static const qcc::String s_prop_HorizontalMax;
    static const qcc::String s_prop_HorizontalAutoMode;
    static const qcc::String s_prop_VerticalDirection;
    static const qcc::String s_prop_VerticalMax;
    static const qcc::String s_prop_VerticalAutoMode;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* WINDDIRECTIONINTERFACE_H_ */