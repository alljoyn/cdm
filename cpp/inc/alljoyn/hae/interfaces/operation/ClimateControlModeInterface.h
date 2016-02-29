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

    enum {
        CLIMATE_CONTROL_MODE_OFF = 0,
        CLIMATE_CONTROL_MODE_HEAT,
        CLIMATE_CONTROL_MODE_COOL,
        CLIMATE_CONTROL_MODE_AUTO,
        CLIMATE_CONTROL_MODE_AUX_HEAT,
        CLIMATE_CONTROL_MODE_DRY,
        CLIMATE_CONTROL_MODE_CONT_DRY
    };

    enum {
        MIN_CLIMATE_CONTROL_MODE = CLIMATE_CONTROL_MODE_OFF,
        MAX_CLIMATE_CONTROL_MODE = CLIMATE_CONTROL_MODE_CONT_DRY
    };

    enum {
        CLIMATE_CONTROL_OPERATIONAL_STATE_IDLE = 0,
        CLIMATE_CONTROL_OPERATIONAL_STATE_HEATING,
        CLIMATE_CONTROL_OPERATIONAL_STATE_COOLING,
        CLIMATE_CONTROL_OPERATIONAL_STATE_PENDING_HEAT,
        CLIMATE_CONTROL_OPERATIONAL_STATE_PENDING_COOL,
        CLIMATE_CONTROL_OPERATIONAL_STATE_AUX_HEAT
    };

    enum {
        MIN_CLIMATE_CONTROL_OPERATIONAL_STATE = CLIMATE_CONTROL_OPERATIONAL_STATE_IDLE,
        MAX_CLIMATE_CONTROL_OPERATIONAL_STATE = CLIMATE_CONTROL_OPERATIONAL_STATE_AUX_HEAT
    };

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_Mode;
    static const qcc::String s_prop_SupportedModes;
    static const qcc::String s_prop_OperationalState;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn


#endif /* CLIMATECONTROLMODEINTERFACE_H_ */
