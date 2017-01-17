/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "{{Interface.Name}}Model.h"
#include <interfaces/controllee/{{InterfaceCategory}}/{{Interface.Name}}IntfControllee.h>
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
        Serializer<{{enum.enum_type().cpp_signature_type()}}> ser;
        return ser.put(parent, value);
    }


    {{Interface.Name}}Interface::{{enum.Name}} get(Element* element)
    {
        Serializer<{{enum.enum_type().cpp_signature_type()}}> ser;
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
            Serializer<{{field[0].cpptype()}}> ser;
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
            Serializer<{{field[0].cpptype()}}> ser;
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

QStatus {{Interface.Name}}Model::Get{{property.Name}}({{property.Type.cpptype()}}& out) const
{
    return HAL::ReadProperty(m_busPath, "{{Interface.FullName}}", "{{property.Name}}", out);
}
{% if property.Writable %}

QStatus {{Interface.Name}}Model::Set{{property.Name}}(const {{property.Type.cpptype_arg()}} value)
{
    return HAL::WriteProperty(m_busPath, "{{Interface.FullName}}", "{{property.Name}}", value);
}
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}

{% set comma = joiner(", ") %}
QStatus {{Interface.Name}}Model::{{method.Name}}(
{%- for arg in method.input_args() %}{{comma()}}{{arg.Type.cpptype_arg()}} arg_{{arg.Name}}{% endfor %}
{%- for arg in method.output_args() %}{{comma()}}{{arg.Type.cpptype()}}& arg_{{arg.Name}}{% endfor %}{{comma()-}}
    ErrorCode& error, CdmControllee& controllee)
{
    {# Note that '::' is not allowed in files on Windows #}
    {% include ["patch/" ~ Interface.Name ~ "Model-" ~ method.Name ~ ".cc", "patch/TODO.cc"] ignore missing with context %}
}
{% endfor %}



QStatus Handle{{Interface.Name}}Command(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

{% for property in Interface.EmittingProperties() %}
{% if loop.first %}
    if (cmd.name == "changed" && cmd.interface == "{{Interface.FullName}}") {
{% endif %}
        if (cmd.property == "{{property.Name}}") {
            {{property.Type.cpptype()}} value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<{{Interface.Name}}IntfControllee>(cmd.objPath, "{{Interface.FullName}}");
                if (iface) {
                    iface->Emit{{property.Name}}Changed(value);
                }
            }
        }
{% if loop.last %}
    }
{% endif %}
{% endfor %}

    return status;
}


} // namespace emulator
} // namespace services
} // namespace ajn
