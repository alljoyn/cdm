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

#ifndef {{Interface.Name.upper()}}INTERFACE_H_
#define {{Interface.Name.upper()}}INTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * {{Interface.Name}} Interface class
 */
class {{Interface.Name}}Interface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
    {% for enum in Interface.Enums %}
    enum {{enum.Name}} {
        {% for value in enum.Values %}
        {{enum.Name.upper_snake()}}_{{value.Name.upper_snake()}} = {{value.Value}},
        {% endfor %}
    };

    {% endfor %}
    {% for struct in Interface.Structs %}
    struct {{struct.Name}} {
        {% for field in struct.Fields %}
        {{field.Type.cpptype()}} {{field.Name}};
        {% endfor %}

        inline bool operator==(const {{struct.Name}}& a) {
            return {% for field in struct.Fields %}a.{{field.Name}}=={{field.Name}}{% if not loop.last %} && {% endif %}{% endfor %};
        }
    };
    {% endfor %}

    /**
     * Constructor of {{Interface.Name}}Interface
     */
    {{Interface.Name}}Interface() {}

    /**
     * Destructor of {{Interface.Name}}Interface
     */
    virtual ~{{Interface.Name}}Interface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return {{Interface.Name.upper_snake()}}_INTERFACE; }

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
    {% for property in Interface.Properties %}
    static const qcc::String s_prop_{{property.Name}};
    {% endfor %}
    {% for method in Interface.Methods %}
    static const qcc::String s_method_{{method.Name}};
    {% endfor %}
    {% for signal in Interface.Signals %}
    static const qcc::String s_signal_{{signal.Name}};
    {% endfor %}

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters
{% for enum in Interface.Enums %}



template<>
struct CdmMsgCvt<{{Interface.Name}}Interface::{{enum.Name}}>
{
    void get(const MsgArg& msgarg, {{Interface.Name}}Interface::{{enum.Name}}& value)
    {
        int32_t v = 0;
        msgarg.Get("i", &v);
        value = static_cast<{{Interface.Name}}Interface::{{enum.Name}}>(v);
    }

    void set(MsgArg& msgarg, {{Interface.Name}}Interface::{{enum.Name}} value)
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
struct CdmMsgCvt<std::vector<{{Interface.Name}}Interface::{{enum.Name}}>>
{
    void get(const MsgArg& msgarg, std::vector<{{Interface.Name}}Interface::{{enum.Name}}>& value)
    {
        int32_t* v = 0;
        size_t l = 0;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<{{Interface.Name}}Interface::{{enum.Name}}>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<{{Interface.Name}}Interface::{{enum.Name}}>& value)
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
{% endfor %}

// Struct converters
{% for struc in Interface.Structs %}
template<>
struct CdmMsgCvt<{{Interface.Name}}Interface::{{struc.Name}}>
{
    void get(const MsgArg& msgarg, {{Interface.Name}}Interface::{{struc.Name}}& value)
    {
{# We can not Get directly into fields that are QString #}
{% for field in struc.Fields %}
        {{field.Type.msgType()}} {{field.Name}}{};
{% endfor %}
        msgarg.Get("{{struc.resolve_signature()}}"
{%- for field in struc.Fields %}
, &{{field.Name}}
{%- endfor %});
{% for field in struc.Fields %}
        value.{{field.Name}} = {{field.Type.fromMsgArg(field.Name)}};
{% endfor %}
    }

    void set(MsgArg& msgarg, const {{Interface.Name}}Interface::{{struc.Name}} value)
    {
{% for field in struc.Fields %}
        {{field.Type.msgType()}} {{field.Name}} = {{field.Type.toMsgArg("value."~field.Name)}};
{% endfor %}
        msgarg.Set("{{struc.resolve_signature()}}"
{%- for field in struc.Fields %}
, {{field.Name}}
{%- endfor %});
    }

    std::string str(const MsgArg& msgarg)
    {
        {{Interface.Name}}Interface::{{struc.Name}} value;
        get(msgarg, value);

        std::ostringstream strm;
{% for field in struc.Fields %}
{% if not loop.first %}
        strm << " ";
{% endif %}
        strm << "{{field.Name}}=" << value.{{field.Name}};
{% endfor %}
        return strm.str();
    }
};


template<>
struct CdmMsgCvt<std::vector<{{Interface.Name}}Interface::{{struc.Name}}>>
{
    void get(const MsgArg& msgarg, std::vector<{{Interface.Name}}Interface::{{struc.Name}}>& value)
    {
        MsgArg* elems = 0;
        size_t  num = 0;

        msgarg.Get("a{{struc.resolve_signature()}}", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
{# We can not Get directly into fields that are QString #}
{% for field in struc.Fields %}
            {{field.Type.msgType()}} {{field.Name}}{};
{% endfor %}
            elems[i].Get("{{struc.resolve_signature()}}"
{%- for field in struc.Fields %}
, &{{field.Name}}
{%- endfor %});
{% for field in struc.Fields %}
            value[i].{{field.Name}} = {{field.Type.fromMsgArg(field.Name)}};
{% endfor %}
        }
    }

    void set(MsgArg& msgarg, const std::vector<{{Interface.Name}}Interface::{{struc.Name}}>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
{% for field in struc.Fields %}
            {{field.Type.msgType()}} {{field.Name}} = {{field.Type.toMsgArg("value[i]."~field.Name)}};
{% endfor %}
            elems[i].Set("{{struc.resolve_signature()}}"
{%- for field in struc.Fields %}
, {{field.Name}}
{%- endfor %});
        }

        msgarg.Set("a{{struc.resolve_signature()}}", num, elems.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::vector<{{Interface.Name}}Interface::{{struc.Name}}> vec;
        get(msgarg, vec);

        std::ostringstream strm;

        for (auto& v : vec)
        {
            strm << "{";
{% for field in struc.Fields %}
{% if not loop.first %}
            strm << " ";
{% endif %}
            strm << "{{field.Name}}=" << {{field.Type.toMsgArg("v."~field.Name)}};
{% endfor %}
            strm << "}";
        }

        return strm.str();
    }
};

{% endfor %}

} //namespace services
} //namespace ajn

#endif /* {{Interface.Name.upper()}}INTERFACE_H_ */
