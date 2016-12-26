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

#ifndef {{Interface.Name.upper()}}MODEL_H_
#define {{Interface.Name.upper()}}MODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}Interface.h>

/**
 * {{Interface.Name}} interface model
 */
typedef struct {
{% for property in Interface.UserProperties %}
{% if property.Readable %}

    /**
     * Get {{property.Name}}
     * @param[out] value current {{property.Name.add_spaces_lower()}}. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*Get{{property.Name}})(void *context, const char *objPath, {{property.Type.tcltype()}}* value);
{% endif %}
{% if property.Writable %}

     /**
     * Set {{property.Name}}
     * @param[in] value The {{property.Name.add_spaces_lower()}} to set
     * @return ER_OK on success
     */
    AJ_Status (*Set{{property.Name}})(void *context, const char *objPath, {{property.Type.tcltype()}} value);
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}

     /**
      * Call {{method.Name}}
{% for a in method.input_args() %}
      * @param[in] {{a.Name}}
{% endfor %}
{% for a in method.output_args() %}
      * @param[out] {{a.Name}} The caller will free the memory if the type is not a scalar.
{% endfor %}
      */
    AJ_Status (*Method{{method.Name}})(void *context, const char *objPath
{%- for a in method.input_args() %}, {{a.Type.tcltype()}} {{a.Name}}{% endfor %}
{%- for a in method.output_args() %}, {{a.Type.tcltype()}}* {{a.Name}}{% endfor %});
{% endfor %}

    AJ_BusAttachment* busAttachment;

} {{Interface.Name}}Model;

#endif /* {{Interface.Name.upper()}}MODEL_H_ */