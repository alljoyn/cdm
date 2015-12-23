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

#ifndef CLIMATECONTROLMODEINTERFACE_H_
#define CLIMATECONTROLMODEINTERFACE_H_


#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface class
 */
class ClimateControlModeInterface : public HaeInterface {
  public:
    typedef std::vector<uint16_t> SupportedModes;

    /**
     * Constructor of ClimateControlModeInterface
     */
    ClimateControlModeInterface() {}

    /**
     * Destructor of ClimateControlModeInterface
     */
    virtual ~ClimateControlModeInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const HaeInterfaceType GetInterfaceType() const { return CLIMATE_CONTROL_MODE_INTERFACE; }

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
    static const qcc::String s_prop_Mode;
    static const qcc::String s_prop_SupportedModes;
    static const qcc::String s_prop_OperatingState;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* CLIMATECONTROLMODEINTERFACE_H_ */
