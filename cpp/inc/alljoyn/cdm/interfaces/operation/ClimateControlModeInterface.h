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

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface class
 */
class ClimateControlModeInterface : public CdmInterface {
  public:
    typedef std::vector<uint16_t> SupportedModes;
    enum Mode {
        MODE_OFF = 0,
        MODE_HEAT = 1,
        MODE_COOL = 2,
        MODE_AUTO = 3,
        MODE_AUXILIARY_HEAT = 4,
        MODE_DRY = 5,
        MODE_CONTINUOUS_DRY = 6,
    };
    enum OperationalState {
        OPERATIONAL_STATE_IDLE = 0,
        OPERATIONAL_STATE_HEATING = 1,
        OPERATIONAL_STATE_COOLING = 2,
        OPERATIONAL_STATE_PENDING_HEAT = 3,
        OPERATIONAL_STATE_PENDING_COOL = 4,
        OPERATIONAL_STATE_AUXILLIARY_HEAT = 5,
    };


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
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CLIMATE_CONTROL_MODE_INTERFACE; }

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

    enum {
        MIN_CLIMATE_CONTROL_MODE = MODE_OFF,
        MAX_CLIMATE_CONTROL_MODE = MODE_CONTINUOUS_DRY
    };
    enum {
        MIN_CLIMATE_CONTROL_OPERATIONAL_STATE = OPERATIONAL_STATE_IDLE,
        MAX_CLIMATE_CONTROL_OPERATIONAL_STATE = OPERATIONAL_STATE_AUXILLIARY_HEAT
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
