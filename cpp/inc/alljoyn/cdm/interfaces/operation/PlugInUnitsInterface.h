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

#ifndef PLUGINUNITSINTERFACE_H_
#define PLUGINUNITSINTERFACE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * PlugInUnits Interface class
 */
class PlugInUnitsInterface : public CdmInterface {
  public:
    /**
     * Constructor of PlugInUnits
     */
    PlugInUnitsInterface() {}

    /**
     * Destructor of PlugInUnits
     */
    virtual ~PlugInUnitsInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return PLUG_IN_UNITS_INTERFACE; }

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


    struct PlugInInfo {
        qcc::String objectPath;
        uint32_t deviceId;
        bool pluggedIn;
        inline bool operator==(const PlugInInfo& info) const {
            return (info.objectPath == objectPath &&
                    info.deviceId == deviceId &&
                    info.pluggedIn == pluggedIn);
        }
    };

    typedef std::vector<PlugInInfo> PlugInUnits;

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_PlugInUnits;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* PLUGINUNITSINTERFACE_H_ */