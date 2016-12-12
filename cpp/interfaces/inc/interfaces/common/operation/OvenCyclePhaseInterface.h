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

#ifndef OVENCYCLEPHASEINTERFACE_H_
#define OVENCYCLEPHASEINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * OvenCyclePhase Interface class
 */
class OvenCyclePhaseInterface : public CdmInterface {
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
     * Constructor of OvenCyclePhaseInterface
     */
    OvenCyclePhaseInterface() {}

    /**
     * Destructor of OvenCyclePhaseInterface
     */
    virtual ~OvenCyclePhaseInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return OVEN_CYCLE_PHASE_INTERFACE; }

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
struct CdmMsgCvt<OvenCyclePhaseInterface::CyclePhaseDescriptor>
{
    void get(const MsgArg& msgarg, OvenCyclePhaseInterface::CyclePhaseDescriptor& value)
    {
        uint8_t phase{};
        const char* name{};
        const char* description{};
        msgarg.Get("(yss)", &phase, &name, &description);
        value.phase = phase;
        value.name = name;
        value.description = description;
    }

    void set(MsgArg& msgarg, const OvenCyclePhaseInterface::CyclePhaseDescriptor value)
    {
        uint8_t phase = value.phase;
        const char* name = value.name.c_str();
        const char* description = value.description.c_str();
        msgarg.Set("(yss)", phase, name, description);
    }

    std::string str(const MsgArg& msgarg)
    {
        OvenCyclePhaseInterface::CyclePhaseDescriptor value;
        get(msgarg, value);

        std::ostringstream strm;
        strm << "phase=" << value.phase;
        strm << " ";
        strm << "name=" << value.name;
        strm << " ";
        strm << "description=" << value.description;
        return strm.str();
    }
};


template<>
struct CdmMsgCvt<std::vector<OvenCyclePhaseInterface::CyclePhaseDescriptor>>
{
    void get(const MsgArg& msgarg, std::vector<OvenCyclePhaseInterface::CyclePhaseDescriptor>& value)
    {
        MsgArg* elems = 0;
        size_t  num = 0;

        msgarg.Get("a(yss)", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            uint8_t phase{};
            const char* name{};
            const char* description{};
            elems[i].Get("(yss)", &phase, &name, &description);
            value[i].phase = phase;
            value[i].name = name;
            value[i].description = description;
        }
    }

    void set(MsgArg& msgarg, const std::vector<OvenCyclePhaseInterface::CyclePhaseDescriptor>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            uint8_t phase = value[i].phase;
            const char* name = value[i].name.c_str();
            const char* description = value[i].description.c_str();
            elems[i].Set("(yss)", phase, name, description);
        }

        msgarg.Set("a(yss)", num, elems.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::vector<OvenCyclePhaseInterface::CyclePhaseDescriptor> vec;
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

#endif /* OVENCYCLEPHASEINTERFACE_H_ */
