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

#ifndef {{Interface.Name.upper()}}INTERFACE_H_
#define {{Interface.Name.upper()}}INTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>

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
} {{Interface.Name}}{{enum.Name}};


typedef struct {
    {{Interface.Name}}{{enum.Name}}* elems;
    size_t numElems;
} Array_{{Interface.Name}}{{enum.Name}};

/**
 *  Free an array of {{Interface.Name}}{{enum.Name}}.
 */
extern void FreeArray_{{Interface.Name}}{{enum.Name}}(Array_{{Interface.Name}}{{enum.Name}}* value);
{% endfor %}

{% for struc in Interface.Structs %}


typedef struct {
{% for field in struc.Fields %}
    {{field.Type.tcltype()}} {{field.Name}};
{% endfor %}
} {{struc.Name}};


typedef struct {
    {{struc.Name}}* elems;
    size_t numElems;
} Array_{{struc.Name}};

/**
 *  Free the fields in the {{struc.Name}} but not the struct itself.
 */
extern void FreeFields_{{struc.Name}}({{struc.Name}}* value);

/**
 *  Free an array of {{struc.Name}}.
 */
extern void FreeArray_{{struc.Name}}(Array_{{struc.Name}}* value);
{% endfor %}


extern const char* const intfDescOperation{{Interface.Name}}[{{Interface.Name.upper()}}_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperation{{Interface.Name}};

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