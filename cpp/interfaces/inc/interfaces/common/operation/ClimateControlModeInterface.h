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
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface class
 */
class ClimateControlModeInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
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

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_Mode;
    static const qcc::String s_prop_SupportedModes;
    static const qcc::String s_prop_OperationalState;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters



template<>
struct CdmMsgCvt<ClimateControlModeInterface::Mode>
{
    void get(const MsgArg& msgarg, ClimateControlModeInterface::Mode& value)
    {
        int32_t v;
        msgarg.Get("i", &v);
        value = static_cast<ClimateControlModeInterface::Mode>(v);
    }

    void set(MsgArg& msgarg, ClimateControlModeInterface::Mode value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }
};

template<>
struct CdmMsgCvt<std::vector<ClimateControlModeInterface::Mode>>
{
    void get(const MsgArg& msgarg, std::vector<ClimateControlModeInterface::Mode>& value)
    {
        int32_t* v;
        size_t l;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<ClimateControlModeInterface::Mode>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<ClimateControlModeInterface::Mode>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }
};



template<>
struct CdmMsgCvt<ClimateControlModeInterface::OperationalState>
{
    void get(const MsgArg& msgarg, ClimateControlModeInterface::OperationalState& value)
    {
        int32_t v;
        msgarg.Get("i", &v);
        value = static_cast<ClimateControlModeInterface::OperationalState>(v);
    }

    void set(MsgArg& msgarg, ClimateControlModeInterface::OperationalState value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }
};

template<>
struct CdmMsgCvt<std::vector<ClimateControlModeInterface::OperationalState>>
{
    void get(const MsgArg& msgarg, std::vector<ClimateControlModeInterface::OperationalState>& value)
    {
        int32_t* v;
        size_t l;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<ClimateControlModeInterface::OperationalState>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<ClimateControlModeInterface::OperationalState>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }
};

// Struct converters

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTERFACE_H_ */