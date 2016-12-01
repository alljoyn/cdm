/*
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
 */

package org.alljoyn.smartspaces.{{InterfaceCategory}};

import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.Signature;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.smartspaces.EnumBase;

@BusInterface(name="{{FullInterfaceName}}", descriptionLanguage="en")
@Secure
public interface {{InterfaceName}} {
    {{#properties}}
    @BusProperty({{#get_emits_changed_signal}}annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, {{/get_emits_changed_signal}}signature="{{PropertyType.signature}}")
    public {{#PropertyType.javatype_primitive}}{{PropertyType.javatype_primitive}}{{/PropertyType.javatype_primitive}}{{^PropertyType.javatype_primitive}}{{PropertyType.javatype}}{{/PropertyType.javatype_primitive}} get{{PropertyName}}();

    {{#PropertyWritable}}
    @BusProperty({{#get_emits_changed_signal}}annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, {{/get_emits_changed_signal}}signature="{{PropertyType.signature}}")
    public void set{{PropertyName}}({{PropertyType.javatype_primitive}} {{PropertyName.camel_case}});

    {{/PropertyWritable}}
    {{/properties}}
    {{#methods}}
    @BusMethod(name="{{MethodName}}"{{#input_signature}}, signature="{{input_signature}}"{{/input_signature}}{{#output_signature}}, replySignature = "{{output_signature}}"{{/output_signature}})
    public {{#output_arg}}{{ArgType.javatype}}{{/output_arg}}{{^output_arg}}void{{/output_arg}} {{MethodName.camel_case}}({{#input_args}}{{ArgType.javatype_primitive}} {{ArgName}}{{^last}}, {{/last}}{{/input_args}});

    {{/methods}}
    {{#signals}}
    @BusSignal(name="{{SignalName}}")
    public void {{SignalName.camel_case}}();

    {{/signals}}
    {{#enums}}
    public enum {{EnumName}} implements EnumBase<{{#enum_type}}{{enum_type.javatype_class}}{{/enum_type}}{{^enum_type}}Integer{{/enum_type}}> {
        {{#values}}
        {{EnumValueName}}(({{#enum_type}}{{enum_type.javatype_primitive}}{{/enum_type}}{{^enum_type}}int{{/enum_type}}){{EnumValue}}){{^Last}},{{/Last}}{{#Last}}{};{{/Last}}
        {{/values}}

        private {{#enum_type}}{{enum_type.javatype_class}}{{/enum_type}}{{^enum_type}}Integer{{/enum_type}} value;
        private {{EnumName}}({{#enum_type}}{{enum_type.javatype_primitive}}{{/enum_type}}{{^enum_type}}int{{/enum_type}} value) {
            this.value = value;
        }

        public {{#enum_type}}{{enum_type.javatype_class}}{{/enum_type}}{{^enum_type}}Integer{{/enum_type}} toValue() {
            return this.value;
        }
    }

    {{/enums}}
    {{#structs}}
    public class {{StructName}} {
        {{#fields}}
        @Position({{FieldPosition}})
        @Signature("{{FieldType.ajtype_primitive}}")
        public {{FieldType.javatype_primitive}} {{FieldName}};

        {{/fields}}
        @Override
        public String toString() {
            return "[" + {{#fields}}" {{FieldName}}=" + "\"" + {{FieldName}} + "\"" + {{/fields}}" ]";
        }
    }

    {{/structs}}
}