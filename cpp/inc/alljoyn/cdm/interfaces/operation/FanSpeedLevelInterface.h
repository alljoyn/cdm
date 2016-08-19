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
