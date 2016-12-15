/*
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
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
 */

package org.alljoyn.smartspaces.{{Interface.Category}};

import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.Signature;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.smartspaces.EnumBase;

@BusInterface(name="{{Interface.FullName}}", descriptionLanguage="en")
@Secure
public interface {{Interface.Name}} {
    {% for property in Interface.Properties %}
    @BusProperty({% if property.EmitsChangedSignal %}annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, {% endif %}signature="{{property.Type.signature}}")
    public {{property.Type.javatype_any()}} get{{property.Name}}();

    {% if property.Writable %}
    @BusProperty({% if property.EmitsChangedSignal %}annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, {% endif %}signature="{{property.Type.signature}}")
    public void set{{property.Name}}({{property.Type.javatype_primitive()}} {{property.Name.camel_case()}});

    {% endif %}
    {% endfor %}
    {% for method in Interface.Methods %}
    @BusMethod(name="{{method.Name}}"
    {%- if method.input_signature() %}, signature="{{method.input_signature()}}"{% endif -%}
    {%- if method.output_signature() %}, replySignature = "{{method.output_signature()}}"{% endif -%}
    )
    public {% if method.output_arg() %}{{method.output_arg().Type.javatype()}}{% else %}void{% endif %} {{method.Name.camel_case()}}({% for arg in method.input_args() %}{{arg.Type.javatype_primitive()}} {{arg.Name}}{% if not loop.last %}, {% endif %}{% endfor %});

    {% endfor %}
    {% for signal in Interface.Signals %}
    @BusSignal(name="{{signal.Name}}")
    public void {{signal.Name.camel_case()}}();

    {% endfor %}
    {% for enum in Interface.Enums %}
    public enum {{enum.Name}} implements EnumBase<{{enum.enum_type().javatype_class()}}> {
        {% for value in enum.Values %}
        {{value.Name}}(({{enum.enum_type().javatype_primitive()}}){{value.Value}}) {%- if not loop.last %},{% else %}{};{% endif %}

        {% endfor %}

        private {{enum.enum_type().javatype_class()}} value;
        private {{enum.Name}}({{enum.enum_type().javatype_primitive()}} value) {
            this.value = value;
        }

        public {{enum.enum_type().javatype_class()}} toValue() {
            return this.value;
        }
    }

    {% endfor %}
    {% for struct in Interface.Structs %}
    public class {{struct.Name}} {
        {% for field in struct.Fields %}
        @Position({{loop.index0}})
        @Signature("{{field.Type.ajtype_primitive()}}")
        public {{field.Type.javatype_primitive()}} {{field.Name}};

        {% endfor %}
        @Override
        public String toString() {
            return "[" + {% for field in struct.Fields %}" {{field.Name}}=" + "\"" + {{field.Name}} + "\"" + {% endfor %}" ]";
        }
    }

    {% endfor %}
}