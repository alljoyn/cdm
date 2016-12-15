/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef {{Interface.Name.upper()}}INTERFACE_H_
#define {{Interface.Name.upper()}}INTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define {{Interface.Name.upper_snake()}} "{{Interface.FullName}}"

/**
 * {{Interface.Name}} interface members
 */
typedef enum {
    {{Interface.Name.upper()}}_PROP_VERSION = 0,
    {% for p in Interface.UserProperties %}
    {{Interface.Name.upper()}}_PROP_{{p.Name.upper_snake()}},
    {% endfor %}
    {% for m in Interface.Methods %}
    {{Interface.Name.upper()}}_METHOD_{{m.Name.upper_snake()}},
    {% endfor %}
    {% for s in Interface.Signals %}
    {{Interface.Name.upper()}}_SIGNAL_{{s.Name.upper_snake()}},
    {% endfor %}
    {{Interface.Name.upper()}}_MEMBER_COUNT
} {{Interface.Name}}Members;
{% for enum in Interface.Enums %}


typedef enum {
{% for value in enum.Values %}
    {{Interface.Name.upper()}}_{{enum.Name.upper_snake()}}_{{value.Name.upper_snake()}} = {{value.Value}}{% if not loop.last %},{% endif %}

{% endfor %}
} {{Interface.Name}}_{{enum.Name}};


typedef struct {
    {{Interface.Name}}_{{enum.Name}}* elems;
    size_t numElems;
} Array_{{Interface.Name}}_{{enum.Name}};


/**
 *  Initialise an array of {{enum.Name}}.
 */
extern void InitArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value, size_t numElems);

/**
 *  Copy an array of {{enum.Name}}.
 */
extern void CopyArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value, Array_{{Interface.Name}}_{{enum.Name}}* copy);

/**
 *  Free an array of {{enum.Name}}.
 */
extern void FreeArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value);

/**
 *  Extend an array of {{enum.Name}}.
 */
extern size_t ExtendArray_{{Interface.Name}}_{{enum.Name}}(Array_{{Interface.Name}}_{{enum.Name}}* value, size_t numElems);
{% endfor %}

{% for struc in Interface.Structs %}


typedef struct {
{% for field in struc.Fields %}
    {{field.Type.tcltype()}} {{field.Name}};
{% endfor %}
} {{Interface.Name}}_{{struc.Name}};


typedef struct {
    {{Interface.Name}}_{{struc.Name}}* elems;
    size_t numElems;
} Array_{{Interface.Name}}_{{struc.Name}};

/**
 *  Free the fields in the {{struc.Name}} but not the struct itself.
 */
extern void FreeFields_{{Interface.Name}}_{{struc.Name}}({{Interface.Name}}_{{struc.Name}}* value);

/**
 *  Free an array of {{struc.Name}}.
 */
extern void FreeArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value);

/**
 *  Initialise an array of {{struc.Name}}.
 */
extern void InitArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value, size_t numElems);

/**
 *  Copy an array of {{struc.Name}}.
 */
extern void CopyArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value, Array_{{Interface.Name}}_{{struc.Name}}* copy);

/**
 *  Extend an array of {{struc.Name}}.
 */
extern size_t ExtendArray_{{Interface.Name}}_{{struc.Name}}(Array_{{Interface.Name}}_{{struc.Name}}* value, size_t numElems);
{% endfor %}


extern const char* const intfDesc{{Interface.Category.capitalize()}}{{Interface.Name}}[{{Interface.Name.upper()}}_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandler{{Interface.Category.capitalize()}}{{Interface.Name}};

{% for property in Interface.UserProperties %}
{% if property.EmitsChangedSignal %}

/**
 * Emits a changed signal for the {{property.Name}} property
 * @param[in] newValue new value of {{property.Name.add_spaces_lower()}}
 * @return ER_OK on success
 */
AJ_Status Cdm_{{Interface.Name}}_Emit{{property.Name}}Changed(AJ_BusAttachment *bus, const char *objPath, {{property.Type.tcltype()}} newValue);
{% endif %}
{% endfor %}
{% for signal in Interface.Signals %}

/**
 * Emits a {{signal.Name}} signal
 * @return ER_OK on success
 */
AJ_Status Cdm_{{Interface.Name}}_Emit{{signal.Name}}();
{% endfor %}

#endif /* {{Interface.Name.upper()}}INTERFACE_H_ */