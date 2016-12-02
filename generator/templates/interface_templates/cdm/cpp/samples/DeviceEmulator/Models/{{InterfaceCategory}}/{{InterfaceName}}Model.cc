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

#include "{{Interface.Name}}Model.h"
#include "../../../Utils/HAL.h"

{% include ("patch/" ~ Interface.Name ~ "Model_header.cc") ignore missing with context %}

namespace ajn {
namespace services {

{% for enum in Interface.Enums %}
template <>
struct Serializer<{{Interface.Name}}Interface::{{enum.Name}}>
{
    Element* put(Element* parent, {{Interface.Name}}Interface::{{enum.Name}} value)
    {
        Serializer<int32_t> ser;
        return ser.put(parent, value);
    }


    {{Interface.Name}}Interface::{{enum.Name}} get(Element* element)
    {
        Serializer<int32_t> ser;
        return static_cast<{{Interface.Name}}Interface::{{enum.Name}}>(ser.get(element));
    }
};

{% endfor %}
{% for struc in Interface.Structs %}
template <>
struct Serializer<{{Interface.Name}}Interface::{{struc.Name}}>
{
    Element* put(Element* parent, {{Interface.Name}}Interface::{{struc.Name}} value)
    {
        std::vector<SerializerField> sfields;
{% for field in struc.Fields %}
        {
            SerializerField sfield;
            Serializer<{{field[0].ctype()}}> ser;
            sfield.name = "{{field[1]}}";
            sfield.elem = ser.put(nullptr, value.{{field.Name}});
            sfields.push_back(sfield);
        }
{% endfor %}
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    {{Interface.Name}}Interface::{{struc.Name}} get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        {{Interface.Name}}Interface::{{struc.Name}} result;
        auto fields = ser.get(element);
        if (fields.size() != {{struc.Fields|length}}) {
            throw SerializerError();
        }
{% for field in struc.Fields %}
        {
            auto& sfield = fields[{{loop.index0}}];
            if (sfield.name != "{{field[1]}}")
            {
                throw SerializerError();
            }
            Serializer<{{field[0].ctype()}}> ser;
            result.{{field.Name}} = ser.get(sfield.elem);
        }
{% endfor %}
        return result;
    }
};

{% endfor %}
} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {

{% include ("patch/" ~ Interface.Name ~ "Model_static.cc") ignore missing with context %}

{{Interface.Name}}Model::{{Interface.Name}}Model(const std::string& busPath) :
    m_busPath(busPath)
{}
{% for property in Interface.UserProperties %}

QStatus {{Interface.Name}}Model::Get{{property.Name}}({{property.Type.ctype()}}& out) const
{
    return HAL::ReadProperty(m_busPath, "{{Interface.FullName}}", "{{property.Name}}", out);
}
{% if property.Writable %}

QStatus {{Interface.Name}}Model::Set{{property.Name}}(const {{property.Type.ctype_arg()}} value)
{
    return HAL::WriteProperty(m_busPath, "{{Interface.FullName}}", "{{property.Name}}", value);
}
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}

{% set comma = joiner(", ") %}
QStatus {{Interface.Name}}Model::{{method.Name}}(
{%- for arg in method.input_args() %}{{comma()}}{{arg.Type.ctype_arg()}} arg_{{arg.Name}}{% endfor %}
{%- for arg in method.output_args() %}{{comma()}}{{arg.Type.ctype()}}& arg_{{arg.Name}}{% endfor %}{{comma()-}}
    ErrorCode& error, CdmControllee& controllee)
{
    {% include ["patch/" ~ Interface.Name ~ "Model::" ~ method.Name ~ ".cc", "patch/TODO.cc"] ignore missing with context %}
}
{% endfor %}

} // namespace emulator
} // namespace services
} // namespace ajn
