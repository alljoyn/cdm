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

#ifndef WINDDIRECTIONINTERFACE_H_
#define WINDDIRECTIONINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface class
 */
class WindDirectionInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
    enum AutoMode {
        AUTO_MODE_OFF = 0,
        AUTO_MODE_ON = 1,
        AUTO_MODE_NOT_SUPPORTED = 255,
    };


    /**
     * Constructor of WindDirectionInterface
     */
    WindDirectionInterface() {}

    /**
     * Destructor of WindDirectionInterface
     */
    virtual ~WindDirectionInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return WIND_DIRECTION_INTERFACE; }

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
    static const qcc::String s_prop_HorizontalDirection;
    static const qcc::String s_prop_HorizontalMax;
    static const qcc::String s_prop_HorizontalAutoMode;
    static const qcc::String s_prop_VerticalDirection;
    static const qcc::String s_prop_VerticalMax;
    static const qcc::String s_prop_VerticalAutoMode;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters



template<>
struct CdmMsgCvt<WindDirectionInterface::AutoMode>
{
    void get(const MsgArg& msgarg, WindDirectionInterface::AutoMode& value)
    {
        int32_t v = 0;
        msgarg.Get("i", &v);
        value = static_cast<WindDirectionInterface::AutoMode>(v);
    }

    void set(MsgArg& msgarg, WindDirectionInterface::AutoMode value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t value = 0;
        msgarg.Get("i", &value);
        strm << value;
        return strm.str();
    }
};

template<>
struct CdmMsgCvt<std::vector<WindDirectionInterface::AutoMode>>
{
    void get(const MsgArg& msgarg, std::vector<WindDirectionInterface::AutoMode>& value)
    {
        int32_t* v = 0;
        size_t l = 0;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<WindDirectionInterface::AutoMode>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<WindDirectionInterface::AutoMode>& value)
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

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t* v = 0;
        size_t l = 0;
        msgarg.Get("ai", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};

// Struct converters

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTERFACE_H_ */
