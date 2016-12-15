{% import "tcl_macros" as tcl_macros with context %}
/******************************************************************************
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
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "{{Interface.Name}}ModelImpl.h"
#include "../../../Utils/HAL.h"
{% include ("patch/" ~ Interface.Name ~ "Model_header.c") ignore missing with context %}
{% for struc in Interface.Structs %}



static Element* HAL_Encode_{{Interface.Name}}_{{struc.Name}}({{Interface.Name}}_{{struc.Name}} value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_{{Interface.Name}}_{{struc.Name}}({{Interface.Name}}_{{struc.Name}} value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
{% for field in struc.Fields %}
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "{{field.Name}}");
        BSXML_AddChild(field, {{field.Type.tclHalEncoder()}}(value.{{field.Name}}, field));
    }
{% endfor %}
    return struc;
}



static void HAL_Decode_{{Interface.Name}}_{{struc.Name}}(Element* elem, {{Interface.Name}}_{{struc.Name}}* value) UNUSED_OK;

static void HAL_Decode_{{Interface.Name}}_{{struc.Name}}(Element* elem, {{Interface.Name}}_{{struc.Name}}* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == {{struc.Fields|length}}) {
{% for field in struc.Fields %}
        {{ tcl_macros.halDecode(field.Type, "value->"~field.Name, "elem->children["~loop.index0~"]") }}
{% endfor %}
    }
}



static Element* HAL_Encode_Array_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}} value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}} value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_{{Interface.Name}}_{{struc.Name}}(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_{{Interface.Name}}_{{struc.Name}}(Element* elem, Array_{{Interface.Name}}_{{struc.Name}}* value) UNUSED_OK;

static void HAL_Decode_Array_{{Interface.Name}}_{{struc.Name}}(Element* elem, Array_{{Interface.Name}}_{{struc.Name}}* value)
{
    InitArray_{{Interface.Name}}_{{struc.Name}}(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_{{Interface.Name}}_{{struc.Name}}(value, 1);
            HAL_Decode_{{Interface.Name}}_{{struc.Name}}(elem->children[i], &value->elems[j]);
        }
    }
}
{% endfor %}
{% for enum in Interface.Enums %}


static Element* HAL_Encode_{{Interface.Name}}_{{enum.Name}}({{Interface.Name}}_{{enum.Name}} value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_{{Interface.Name}}_{{enum.Name}}({{Interface.Name}}_{{enum.Name}} value, Element* parent)
{
    return HAL_Encode_Int(value, parent);
}



static void HAL_Decode_{{Interface.Name}}_{{enum.Name}}(Element* elem, {{Interface.Name}}_{{enum.Name}}* value) UNUSED_OK;

static void HAL_Decode_{{Interface.Name}}_{{enum.Name}}(Element* elem, {{Interface.Name}}_{{enum.Name}}* value)
{
    *value = ({{Interface.Name}}_{{enum.Name}})(int)HAL_Decode_Int(elem);
}



static Element* HAL_Encode_Array_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}} value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}} value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Int(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_{{Interface.Name}}_{{enum.Name}}(Element* elem, Array_{{Interface.Name}}_{{enum.Name}}* value) UNUSED_OK;

static void HAL_Decode_Array_{{Interface.Name}}_{{enum.Name}}(Element* elem, Array_{{Interface.Name}}_{{enum.Name}}* value)
{
    InitArray_{{Interface.Name}}_{{enum.Name}}(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_{{Interface.Name}}_{{enum.Name}}(value, 1);
            value->elems[j] = ({{Interface.Name}}_{{enum.Name}})(int)HAL_Decode_Int(elem->children[i]);
        }
    }
}
{% endfor %}

{% include ("patch/" ~ Interface.Name ~ "Model_static.c") ignore missing with context %}

{% for property in Interface.UserProperties %}
{% set halC = tcl_macros.halCType(property.Type) %}
{% set halI = tcl_macros.halInit(property.Type) %}
{% set hal = property.Type.tclHalEncoder() %}
{% if property.Readable %}


static AJ_Status Get{{property.Name}}(void *context, const char *objPath, {{property.Type.tcltype()}} *out)
{
    AJ_Status result = AJ_OK;
    {{halC}} value = {{halI}};

    Element* elem = HAL_ReadProperty("/cdm/emulated", "{{Interface.FullName}}", "{{property.Name}}");

    if (elem) {
        {{tcl_macros.halDecode(property.Type, "value", "elem")}}
        BSXML_FreeElement(elem);
    }

    *out = {{tcl_macros.castTo(property.Type)}}value;
    return result;
}
{% endif %}
{% if property.Writable %}



static AJ_Status Set{{property.Name}}(void *context, const char *objPath, {{property.Type.tcltype()}} input)
{
    AJ_Status result = AJ_OK;
    {{halC}} value = input;

    Element* elem = {{hal}}(value, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "{{Interface.FullName}}", "{{property.Name}}", elem);
    BSXML_FreeElement(elem);

    return result;
}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}



static AJ_Status Method{{method.Name}}(void *context, const char *objPath
{%- for a in method.input_args() %}, {{a.Type.tcltype()}} {{a.Name}}{% endfor %}
{%- for a in method.output_args() %}, {{a.Type.tcltype()}}* {{a.Name}}{% endfor %})
{
{% include ["patch/" ~ Interface.Name ~ "Model_" ~ method.Name ~ ".c", "patch/TODO.c"] ignore missing with context %}
}
{% endfor %}



static {{Interface.Name}}Model model = {
{% set comma = joiner(", ") %}
{% for property in Interface.UserProperties %}
{% if property.Readable %}
    {{comma()}}Get{{property.Name}}
{% endif %}
{% if property.Writable %}
    {{comma()}}Set{{property.Name}}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}
    {{comma()}}Method{{method.Name}}
{% endfor %}
};


{{Interface.Name}}Model *Get{{Interface.Name}}Model(void)
{
    return &model;
}