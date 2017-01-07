{% import "tcl_macros" as tcl_macros with context %}
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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/{{InterfaceCategory}}/{{Interface.Name}}Interface.h>
#include <ajtcl/cdm/interfaces/{{InterfaceCategory}}/{{Interface.Name}}Model.h>

#define INTERFACE_VERSION {{Interface.Version}}
#define INTERFACE_NAME {{Interface.Name.upper_snake()}}

const char* const intfDesc{{Interface.Category.capitalize()}}{{Interface.Name}}[] = {
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



void FreeFields_{{Interface.Name}}_{{struc.Name}}({{Interface.Name}}_{{struc.Name}}* value)
{
{% for field in struc.Fields %}
    {{tcl_macros.freeType(field.Type, "value->"~field.Name)}}
{% endfor %}
}


void InitArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof({{Interface.Name}}_{{struc.Name}}), numElems);
}


/* Note: this only allows fields that are char*, not any other kind of pointer */
void CopyArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value, Array_{{Interface.Name}}_{{struc.Name}}* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof({{Interface.Name}}_{{struc.Name}}));
        for (size_t i = 0; i < value->numElems; ++i) {
{% for field in struc.Fields %}
{% if field.Type.ajtypeIsString() %}
            copy->elems[i].{{field.Name}} = strdup(value->elems[i].{{field.Name}});
{% else %}
            copy->elems[i].{{field.Name}} = value->elems[i].{{field.Name}};
{% endif %}
{% endfor %}
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_{{Interface.Name}}_{{struc.Name}}(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof({{Interface.Name}}_{{struc.Name}}), numElems);
}
{% endfor %}
{% for enum in Interface.Enums %}


void InitArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof({{Interface.Name}}_{{enum.Name}}), numElems);
}


void CopyArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value, Array_{{Interface.Name}}_{{enum.Name}}* copy)
{
    Copy_Array((CDM_Array*)value, sizeof({{Interface.Name}}_{{enum.Name}}), (CDM_Array*)copy);
}


void FreeArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof({{Interface.Name}}_{{enum.Name}}), numElems);
}
{% endfor %}

{% for p in Interface.UserProperties %}
{% if p.Readable %}



static AJ_Status {{Interface.Name}}_Get{{p.Name}}(AJ_BusAttachment* busAttachment, const char* objPath, {{p.Type.tcltype()}}* out)
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

    model->busAttachment = busAttachment;
    return model->Get{{p.Name}}(model, objPath, out);
}
{% endif %}
{% if p.Writable %}
{% if p.ValueIn or p.Type.ajtypeIsEnum() %}

static AJ_Status Validate{{p.Name}}({{Interface.Name}}Model* model, const char* objPath, {{p.Type.tcltype()}} value)
{
    AJ_Status status{% if not p.ValueIn %} = AJ_OK{%endif%};
    {% if p.ValueIn %}
    {{Interface.PropLUT[p.ValueIn].Type.tcltype()}} validValues;
    status = model->Get{{p.ValueIn}}(model, objPath, &validValues);
    if (status != AJ_OK)
        return status;

    status = (valueIn_{{Interface.PropLUT[p.ValueIn].Type.tcltype()}}(value, &validValues) == 1) ? AJ_OK : AJ_ERR_NO_MATCH;

    Free{{Interface.PropLUT[p.ValueIn].Type.tcltype()}}(&validValues);
    {% endif %}
    {% if p.Type.ajtypeIsEnum() %}
    {% set enum = p.Type.ajtypeIsEnum() %}

    switch (value)
    {
        {% for ename in enum.Values %}
        case {{Interface.Name.upper()}}_{{enum.Name.upper_snake()}}_{{ename.Name.upper_snake()}}:
        {% endfor %}
            break;

        default:
            return AJ_ERR_INVALID;
    }
    {% endif %}
    return status;
}
{% endif %}
{% if p.Clamp %}

static AJ_Status clamp{{p.Name}}({{Interface.Name}}Model* model, const char* objPath, {{p.Type.tcltype()}} value, {{p.Type.tcltype()}} *out)
{
    AJ_Status status;
    {% if p.Min != None %}

    {{p.Type.tcltype()}} minValue = {{p.Min}};
    {% endif %}
    {% if p.MinFromProperty != None %}

    {{p.Type.tcltype()}} minValue;
    status = model->Get{{p.MinFromProperty}}(model, objPath, &minValue);
    if (status != AJ_OK)
        return status;
    {% endif %}
    {% if p.Max != None %}

    {{p.Type.tcltype()}} maxValue = {{p.Max}};{% endif %}
    {% if p.MaxFromProperty != None %}

    {{p.Type.tcltype()}} maxValue;
    status = model->Get{{p.MaxFromProperty}}(model, objPath, &maxValue);
    if (status != AJ_OK)
        return status;
    {% endif %}

    {{p.Type.tcltype()}} stepValue = 0;
    {% if p.StepFromProperty != None %}
    status = model->Get{{p.StepFromProperty}}(model, objPath, &stepValue);
    if (status != AJ_OK)
        return status;
    {% endif %}

    *out = clamp_{{p.Type.tclTypeName()}}(value, minValue, maxValue, stepValue);
    return AJ_OK;
}
{% endif %}

static AJ_Status {{Interface.Name}}_Set{{p.Name}}(AJ_BusAttachment* busAttachment, const char* objPath, {{p.Type.tcltype()}} value)
{
    AJ_Status status;

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
    {% if p.CustomCheck %}

    {% include ["patch/" ~ Interface.Name ~ "_Validate" ~ p.Name ~ ".c", "patch/TODO.c"] ignore missing with context %}
    {% else %}
    {% if p.Clamp %}

    status = clamp{{p.Name}}(model, objPath, value, &value);
    if (status != AJ_OK)
        return status;
    {% endif %}
    {% if p.ValueIn or p.Type.ajtypeIsEnum() %}

    status = Validate{{p.Name}}(model, objPath, value);
    if (status != AJ_OK)
        return status;
    {% endif %}
    {% endif %}

    model->busAttachment = busAttachment;
    status = model->Set{{p.Name}}(model, objPath, value);
    return status;
}
{% endif %}
{% if p.EmitsChangedSignal %}
{% if p.Type.ajtypeStructName() %}
{% set name = p.Type.ajtypeStructName() %} 
{% for struc in Interface.Structs %}
{%   if struc.Name == name %}



static AJ_Status Marshal{{p.Name}}(AJ_Message* msg, void* structure, const char* structSignature)
{
    {{Interface.Name}}_{{name}}* value = ({{Interface.Name}}_{{name}}*)structure;
    {# This assumes that fields in structs are only scalars or strings #}
{% for field in struc.Fields %}
    AJ_MarshalArgs(msg, "{{field.Type.tclMarshalSig()}}", value->{{field.Name}});
{% endfor %}
    return AJ_OK;
}
{%   endif %}
{% endfor %}
{% endif %}



AJ_Status Cdm_{{Interface.Name}}_Emit{{p.Name}}Changed(AJ_BusAttachment *bus, const char *objPath, {{p.Type.tcltype()}} newValue)
{
{% if p.Type.ajtypeIsArray() %}
{%   if p.Type.ajtypeStructName() %}
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "{{p.Name}}", "{{p.Type.signature}}", newValue.elems, newValue.numElems, sizeof(*newValue.elems), Marshal{{p.Name}});
{%   else %}
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "{{p.Name}}", "{{p.Type.signature}}", newValue.elems, newValue.numElems);
{%   endif %}
{% else %}
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "{{p.Name}}", "{{p.Type.signature}}", newValue);
{% endif %}
}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}


static AJ_Status Cdm_{{Interface.Name}}_Call{{method.Name}}(AJ_BusAttachment* busAttachment, const char *objPath
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

    model->busAttachment = busAttachment;
    return model->Method{{method.Name}}(model, objPath 
{%- for a in method.input_args() %}, {{tcl_macros.castTo(a.Type)}}{{a.Name}}{% endfor %}
{%- for a in method.output_args() %}, {{a.Name}}{% endfor %});
}
{% endfor %}



/*
   Handler functions
*/
static AJ_Status {{Interface.Name}}_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
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
            status = {{Interface.Name}}_Get{{p.Name}}(busAttachment, objPath, &{{p.Name.snake()}});
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
            {{p.Type.tcltype(enumByName = False)}} {{p.Name.snake()}};
            status = AJ_UnmarshalArgs(msg, "{{p.Type.signature}}", &{{p.Name.snake()}});
            if (status == AJ_OK) {
                status = {{Interface.Name}}_Set{{p.Name}}(busAttachment, objPath, {{tcl_macros.castTo(p.Type)}}{{p.Name.snake()}});
                if (status == AJ_OK) {
                    status= Cdm_{{Interface.Name}}_Emit{{p.Name}}Changed(busAttachment, objPath, {{p.Name.snake()}});
                }
            }
            break;
        }
        {% endif %}
        {% endfor %}
    }

    return status;
}



static AJ_Status {{Interface.Name}}_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;
{% for method in Interface.Methods %}
{% if loop.first %}

    switch (memberIndex) {
{% endif %}

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

        status = Cdm_{{Interface.Name}}_Call{{method.Name}}(busAttachment, objPath
{%- for arg in method.input_args() %}, {{arg.Name.snake()}}{% endfor %}
{%- for arg in method.output_args() %}, &{{arg.Name.snake()}}{% endfor %});

        {# Be careful that the method might emit a signal. We must be careful to start the
           next message after a signal has been sent. #}
        AJ_Message reply;
        AJ_MarshalReplyMsg(msg, &reply);

{% if method.output_args() %}
        if (status == AJ_OK) {
{% for arg in method.output_args() %}
            status |= AJ_MarshalArgs(&reply, "{{arg.Type.signature}}", {{tcl_macros.unpackArgs(arg.Type, arg.Name.snake())}});
{% endfor %}
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(&reply);
            }
        }
{% else %}
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }
{% endif %}

{% for arg in method.output_args() %}
{{ tcl_macros.freeType(arg.Type, arg.Name.snake())|indent(2 * 4, True) }}
{% endfor %}
        break;
    }
{% if loop.last %}
    }
{% endif %}
{% endfor %}

    return status;
}



const InterfaceHandler intfHandler{{Interface.Category.capitalize()}}{{Interface.Name}} = {
    {{Interface.Name}}_OnGetProperty,
    {{Interface.Name}}_OnSetProperty,
    {{Interface.Name}}_OnMethodHandler
};
