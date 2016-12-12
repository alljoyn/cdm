{% import "tcl_macros" as tcl_macros with context %}
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

#include <stdlib.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/{{InterfaceCategory}}/{{Interface.Name}}Interface.h>
#include <ajtcl/cdm/interfaces/{{InterfaceCategory}}/{{Interface.Name}}Model.h>

#define INTERFACE_VERSION {{Interface.Version}}
#define INTERFACE_NAME {{Interface.Name.upper_snake()}}

const char* const intfDescOperation{{Interface.Name}}[] = {
    "${{Interface.FullName}}",
    {% for p in Interface.Properties %}
    "@{{p.Name}}{{p.tcl_access_char()}}{{p.Type.signature}}",
    {% endfor %}
    {% for m in Interface.Methods %}
    "?{{m.Name}}{% for a in m.input_args() %} {{a.Name}}<{{a.Type.signature}}{% endfor %}{% for a in m.output_args() %} {{a.Name}}>{{a.Type.signature}}{% endfor %}",
    {% endfor %}
    {% for s in Interface.Signals %}
    "!{{s.Name}}",
    {% endfor %}
    NULL
};
{% for struc in Interface.Structs %}



void FreeFields_{{struc.Name}}({{struc.Name}}* value)
{
{% for field in struc.Fields %}
{% if field.Type.ajtypeIsString() %}
    free(value->{{field.Name}});
{% endif %}
{% if field.Type.ajtypeStructName() %}
    FreeFields_{{field.Type.ajtypeStructName()}}(&value->{{field.Name}});
    free(value->{{field.Name}});
{% endif %}
{% endfor %}
}


void FreeArray_{{struc.Name}}(Array_{{struc.Name}}* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_{{struc.Name}}(&value->elems[i]);
    }
    free(value->elems);
}
{% endfor %}

{% for enum in Interface.Enums %}


void FreeArray_{{Interface.Name}}{{enum.Name}}(Array_{{Interface.Name}}{{enum.Name}}* value)
{
    free(value->elems);
}
{% endfor %}

{% for p in Interface.UserProperties %}
{% if p.Readable %}



static AJ_Status {{Interface.Name}}_Get{{p.Name}}(const char* objPath, {{p.Type.tcltype()}}* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    {{Interface.Name}}Model* model = ({{Interface.Name}}Model*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->Get{{p.Name}}) {
        return AJ_ERR_NULL;
    }

    return model->Get{{p.Name}}(model, objPath, out);
}
{% endif %}
{% if p.Writable %}



static AJ_Status {{Interface.Name}}_Set{{p.Name}}(const char* objPath, {{p.Type.tcltype()}} value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    {{Interface.Name}}Model* model = ({{Interface.Name}}Model*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->Set{{p.Name}}) {
        return AJ_ERR_NULL;
    }

    return model->Set{{p.Name}}(model, objPath, value);
}
{% endif %}

{% if p.EmitsChangedSignal %}



AJ_Status Cdm_{{Interface.Name}}_Emit{{p.Name}}Changed(AJ_BusAttachment *bus, const char *objPath, {{p.Type.tcltype()}} newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "{{p.Name}}", "{{p.Type.signature}}", {{tcl_macros.unpackArgs(p.Type, "newValue")}});
}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}


static AJ_Status Cdm_{{Interface.Name}}_Call{{method.Name}}(const char *objPath
{%- for a in method.input_args() %}, {{a.Type.tcltype()}} {{a.Name}}{% endfor %}
{%- for a in method.output_args() %}, {{a.Type.tcltype()}}* {{a.Name}}{% endfor %})
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    {{Interface.Name}}Model* model = ({{Interface.Name}}Model*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->Method{{method.Name}}) {
        return AJ_ERR_NULL;
    }

    return model->Method{{method.Name}}(model, objPath 
{%- for a in method.input_args() %}, {{a.Name}}{% endfor %}
{%- for a in method.output_args() %}, {{a.Name}}{% endfor %});
}
{% endfor %}



//
// Handler functions
//
static AJ_Status {{Interface.Name}}_OnGetProperty(AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case {{Interface.Name.upper()}}_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;
        {% for p in Interface.UserProperties %}
        {% if p.Readable %}

        case {{Interface.Name.upper()}}_PROP_{{p.Name.upper_snake()}}:
        {
            {{p.Type.tcltype()}} {{p.Name.snake()}};
            status = {{Interface.Name}}_Get{{p.Name}}(objPath, &{{p.Name.snake()}});
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "{{p.Type.signature}}", {{tcl_macros.unpackArgs(p.Type, p.Name.snake())}});
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
{{ tcl_macros.freeType(p.Type, p.Name.snake())|indent(4 * 4, True) }}
            }
            break;
        }
        {% endif %}
        {% endfor %}
    }

    return status;
}



static AJ_Status {{Interface.Name}}_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case {{Interface.Name.upper()}}_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
        {% for p in Interface.UserProperties %}
        {% if p.Writable %}

        case {{Interface.Name.upper()}}_PROP_{{p.Name.upper_snake()}}:
        {
            {{p.Type.tcltype()}} {{p.Name.snake()}};
            status = AJ_UnmarshalArgs(msg, "{{p.Type.signature}}", &{{p.Name.snake()}});
            if (status == AJ_OK) {
                status = {{Interface.Name}}_Set{{p.Name}}(objPath, {{p.Name.snake()}});
            }
            break;
        }
        {% endif %}
        {% endfor %}
    }

    return status;
}



static AJ_Status {{Interface.Name}}_OnMethodHandler(AJ_Message* msg, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
{% for method in Interface.Methods %}

    case {{Interface.Name.upper()}}_METHOD_{{method.Name.upper_snake()}}:
    {
{% for arg in method.input_args() %}
        {{arg.Type.tcltype()}} {{arg.Name.snake()}};
        status = AJ_UnmarshalArgs(msg, "{{arg.Type.signature}}", &{{arg.Name.snake()}});

        if (status != AJ_OK) {
            return status;
        }
{% endfor %}
{% for arg in method.output_args() %}
        {{arg.Type.tcltype()}} {{arg.Name.snake()}};
{% endfor %}

        status = Cdm_{{Interface.Name}}_Call{{method.Name}}(objPath
{%- for arg in method.input_args() %}, {{arg.Name.snake()}}{% endfor %}
{%- for arg in method.output_args() %}, &{{arg.Name.snake()}}{% endfor %});

{% if method.output_args() %}
        if (status == AJ_OK) {
{% for arg in method.output_args() %}
            status |= AJ_MarshalArgs(replyMsg, "{{arg.Type.signature}}", {{tcl_macros.unpackArgs(arg.Type, arg.Name.snake())}});
{% endfor %}
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(replyMsg);
            }
        }
{% else %}
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(replyMsg);
        }
{% endif %}

{% for arg in method.output_args() %}
{{ tcl_macros.freeType(arg.Type, arg.Name.snake())|indent(2 * 4, True) }}
{% endfor %}
        break;
    }
{% endfor %}
    }

    return status;
}



const InterfaceHandler intfHandlerOperation{{Interface.Name}} = {
    {{Interface.Name}}_OnGetProperty,
    {{Interface.Name}}_OnSetProperty,
    {{Interface.Name}}_OnMethodHandler
};
