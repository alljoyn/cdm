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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "{{Interface.Name}}ModelImpl.h"
#include "../../../Utils/HAL.h"

{% include ("patch/" ~ Interface.Name ~ "Model_header.c") ignore missing with context %}

{% for struc in Interface.Structs %}



static int HAL_Encode_{{Interface.Name}}_{{struc.Name}}(FILE* fp, {{Interface.Name}}_{{struc.Name}} value) UNUSED_OK;

static int HAL_Encode_{{Interface.Name}}_{{struc.Name}}(FILE* fp, {{Interface.Name}}_{{struc.Name}} value)
{
    HAL_Encode_OpenStruct(fp);
{% for field in struc.Fields %}
    {{field.Type.tclHalEncoder()}}(fp, value.{{field.Name}});
{% endfor %}
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_{{Interface.Name}}_{{struc.Name}}(FILE* fp, {{Interface.Name}}_{{struc.Name}}* value) UNUSED_OK;

static int HAL_Decode_{{Interface.Name}}_{{struc.Name}}(FILE* fp, {{Interface.Name}}_{{struc.Name}}* value)
{
    HAL_Decode_OpenStruct(fp);
{% for field in struc.Fields %}
    {{ tcl_macros.halDecode(field.Type, "value->"~field.Name) }}
{% endfor %}
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_{{Interface.Name}}_{{struc.Name}}(FILE* fp, Array_{{Interface.Name}}_{{struc.Name}} value) UNUSED_OK;

static int HAL_Encode_Array_{{Interface.Name}}_{{struc.Name}}(FILE* fp, Array_{{Interface.Name}}_{{struc.Name}} value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_{{Interface.Name}}_{{struc.Name}}(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_{{Interface.Name}}_{{struc.Name}}(FILE* fp, Array_{{Interface.Name}}_{{struc.Name}}* value) UNUSED_OK;

static int HAL_Decode_Array_{{Interface.Name}}_{{struc.Name}}(FILE* fp, Array_{{Interface.Name}}_{{struc.Name}}* value)
{
    InitArray_{{Interface.Name}}_{{struc.Name}}(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_{{Interface.Name}}_{{struc.Name}}(value, 1);
        HAL_Decode_{{Interface.Name}}_{{struc.Name}}(fp, &value->elems[i]);
    }
    return AJ_OK;
}
{% endfor %}
{% for enum in Interface.Enums %}


static int HAL_Encode_{{Interface.Name}}_{{enum.Name}}(FILE* fp, {{Interface.Name}}_{{enum.Name}} value) UNUSED_OK;

static int HAL_Encode_{{Interface.Name}}_{{enum.Name}}(FILE* fp, {{Interface.Name}}_{{enum.Name}} value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_{{Interface.Name}}_{{enum.Name}}(FILE* fp, {{Interface.Name}}_{{enum.Name}}* value) UNUSED_OK;

static int HAL_Decode_{{Interface.Name}}_{{enum.Name}}(FILE* fp, {{Interface.Name}}_{{enum.Name}}* value)
{
    *value = ({{Interface.Name}}_{{enum.Name}})(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_{{Interface.Name}}_{{enum.Name}}(FILE* fp, Array_{{Interface.Name}}_{{enum.Name}} value) UNUSED_OK;

static int HAL_Encode_Array_{{Interface.Name}}_{{enum.Name}}(FILE* fp, Array_{{Interface.Name}}_{{enum.Name}} value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_{{Interface.Name}}_{{enum.Name}}(FILE* fp, Array_{{Interface.Name}}_{{enum.Name}}* value) UNUSED_OK;

static int HAL_Decode_Array_{{Interface.Name}}_{{enum.Name}}(FILE* fp, Array_{{Interface.Name}}_{{enum.Name}}* value)
{
    InitArray_{{Interface.Name}}_{{enum.Name}}(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_{{Interface.Name}}_{{enum.Name}}(value, 1);
        value->elems[i] = ({{Interface.Name}}_{{enum.Name}})(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}
{% endfor %}

{% include ("patch/" ~ Interface.Name ~ "Model_static.c") ignore missing with context %}

{% for property in Interface.UserProperties %}
{% set halC = tcl_macros.halCType(property.Type) %}
{% set hal = property.Type.tclHalEncoder() %}
{% if property.Readable %}


static AJ_Status Get{{property.Name}}(void *context, const char *objPath, {{property.Type.tcltype()}} *out)
{
    AJ_Status result = AJ_OK;
    {{halC}} value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "{{Interface.Name}}", "{{property.Name}}");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "{{Interface.Name}}", "{{property.Name}}");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        {{property.Type.tclHalEncoder()}}(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "{{Interface.Name}}", "{{property.Name}}");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    {{tcl_macros.halDecode(property.Type, "value")}}
    *out = {{tcl_macros.castTo(property.Type)}}value;
    fclose(fp);
    return result;
}
{% endif %}
{% if property.Writable %}



static AJ_Status Set{{property.Name}}(void *context, const char *objPath, {{property.Type.tcltype()}} input)
{
    AJ_Status result = AJ_OK;
    {{halC}} value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "{{Interface.Name}}", "{{property.Name}}");
    {{hal}}(fp, value);
    fclose(fp);
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
