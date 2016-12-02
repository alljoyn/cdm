/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef PLUGINUNITSINTERFACE_H_
#define PLUGINUNITSINTERFACE_H_

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
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;


    struct PlugInInfo {
        qcc::String objectPath;
        uint32_t deviceId;
        bool pluggedIn;

        inline bool operator==(const PlugInInfo& a) {
            return a.objectPath==objectPath && a.deviceId==deviceId && a.pluggedIn==pluggedIn;
        }
    };

    /**
     * Constructor of PlugInUnitsInterface
     */
    PlugInUnitsInterface() {}

    /**
     * Destructor of PlugInUnitsInterface
     */
    virtual ~PlugInUnitsInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return PLUG_IN_UNITS_INTERFACE; }

    /**
     * Get Introspection XML
     * @return Introspection XML
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return Interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

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
