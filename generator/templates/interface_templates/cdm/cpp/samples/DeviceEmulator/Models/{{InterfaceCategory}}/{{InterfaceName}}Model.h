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

#include <interfaces/controllee/{{InterfaceCategory}}/{{Interface.Name}}IntfControlleeModel.h>

namespace ajn {
namespace services {
namespace emulator {


class {{Interface.Name}}Model : public virtual {{Interface.Name}}IntfControlleeModel {
  public:
    {{Interface.Name}}Model(const std::string& busPath);
    {% for property in Interface.UserProperties %}

    /**
     * Get {{property.Name}}
     * @return current {{property.Name.add_spaces_lower()}}
     */
    QStatus Get{{property.Name}}({{property.Type.cpptype()}}& out) const override;
    {% if property.Writable %}

     /**
     * Set {{property.Name}}
     * @param[in] value The {{property.Name.add_spaces_lower()}} to set
     * @return ER_OK on success
     */
    QStatus Set{{property.Name}}(const {{property.Type.cpptype_arg()}} value) override;
    {% endif %}
    {% endfor %}

    {% for method in Interface.Methods %}
    /**
     * Handler for method {{method.Name}}
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
{% set comma = joiner(", ") %}
    QStatus {{method.Name}}(
{%- for arg in method.input_args() %}{{comma()}}{{arg.Type.cpptype_arg()}} arg_{{arg.Name}}{% endfor %}
{%- for arg in method.output_args() %}{{comma()}}{{arg.Type.cpptype()}}& arg_{{arg.Name}}{% endfor %}{{comma()-}}
    ErrorCode& error, CdmControllee& controllee) override;
    {% endfor %}

  private:
    std::string m_busPath;
};

} // namespace emulator
} // namespace services
} // namespace ajn

#endif /* {{Interface.Name.upper()}}MODEL_H_ */