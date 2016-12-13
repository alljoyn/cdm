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

// This file is automatically generated. Do not edit it.

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
    void get(const MsgArg& msgarg, DishWashingCyclePhaseInterface::CyclePhaseDescriptor& arg_)
    {
        uint8_t field_phase{};
        const char* field_name{};
        const char* field_description{};
        msgarg.Get("(yss)", &field_phase, &field_name, &field_description);
        arg_.phase = field_phase;
        arg_.name = field_name;
        arg_.description = field_description;
    }

    void set(MsgArg& msgarg, const DishWashingCyclePhaseInterface::CyclePhaseDescriptor arg_)
    {
        uint8_t field_phase = arg_.phase;
        const char* field_name = arg_.name.c_str();
        const char* field_description = arg_.description.c_str();
        msgarg.Set("(yss)", field_phase, field_name, field_description);
    }

    std::string str(const MsgArg& msgarg)
    {
        DishWashingCyclePhaseInterface::CyclePhaseDescriptor arg_;
        get(msgarg, arg_);

        std::ostringstream strm;
        strm << "phase=" << arg_.phase;
        strm << " ";
        strm << "name=" << arg_.name;
        strm << " ";
        strm << "description=" << arg_.description;
        return strm.str();
    }
};


template<>
struct CdmMsgCvt<std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>>
{
    void get(const MsgArg& msgarg, std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& arg_)
    {
        MsgArg* elems = 0;
        size_t  num = 0;

        msgarg.Get("a(yss)", &num, &elems);
        arg_.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            uint8_t field_phase{};
            const char* field_name{};
            const char* field_description{};
            elems[i].Get("(yss)", &field_phase, &field_name, &field_description);
            arg_[i].phase = field_phase;
            arg_[i].name = field_name;
            arg_[i].description = field_description;
        }
    }

    void set(MsgArg& msgarg, const std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& arg_)
    {
        size_t num = arg_.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            uint8_t field_phase = arg_[i].phase;
            const char* field_name = arg_[i].name.c_str();
            const char* field_description = arg_[i].description.c_str();
            elems[i].Set("(yss)", field_phase, field_name, field_description);
        }

        msgarg.Set("a(yss)", num, elems.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor> vec;
        get(msgarg, vec);

        std::ostringstream strm;

        for (auto& v : vec)
        {
            strm << "{";
            strm << "phase=" << v.phase;
            strm << " ";
            strm << "name=" << v.name.c_str();
            strm << " ";
            strm << "description=" << v.description.c_str();
            strm << "}";
        }

        return strm.str();
    }
};


} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTERFACE_H_ */
