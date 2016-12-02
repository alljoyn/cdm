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

#ifndef DISHWASHINGCYCLEPHASEINTERFACE_H_
#define DISHWASHINGCYCLEPHASEINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface class
 */
class DishWashingCyclePhaseInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
    struct CyclePhaseDescriptor {
        uint8_t phase;
        qcc::String name;
        qcc::String description;

        inline bool operator==(const CyclePhaseDescriptor& a) {
            return a.phase==phase && a.name==name && a.description==description;
        }
    };

    /**
     * Constructor of DishWashingCyclePhaseInterface
     */
    DishWashingCyclePhaseInterface() {}

    /**
     * Destructor of DishWashingCyclePhaseInterface
     */
    virtual ~DishWashingCyclePhaseInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return DISH_WASHING_CYCLE_PHASE_INTERFACE; }

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
    static const qcc::String s_prop_CyclePhase;
    static const qcc::String s_prop_SupportedCyclePhases;
    static const qcc::String s_method_GetVendorPhasesDescription;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters

// Struct converters
template<>
struct CdmMsgCvt<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>
{
    void get(const MsgArg& msgarg, DishWashingCyclePhaseInterface::CyclePhaseDescriptor& value)
    {
        msgarg.Get("(yss)", &value.phase, &value.name, &value.description);
    }

    void set(MsgArg& msgarg, DishWashingCyclePhaseInterface::CyclePhaseDescriptor value)
    {
        msgarg.Set("(yss)", &value.phase, &value.name, &value.description);
    }
};


template<>
struct CdmMsgCvt<std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>>
{
    void get(const MsgArg& msgarg, std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& value)
    {
        MsgArg* elems;
        size_t  num;

        msgarg.Get("a*", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Get("(yss)", &value[i].phase, &value[i].name, &value[i].description);
        }
    }

    void set(MsgArg& msgarg, std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Set("(yss)", &value[i].phase, &value[i].name, &value[i].description);
        }

        msgarg.Set("a*", num, elems.data());
    }
};


} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTERFACE_H_ */
