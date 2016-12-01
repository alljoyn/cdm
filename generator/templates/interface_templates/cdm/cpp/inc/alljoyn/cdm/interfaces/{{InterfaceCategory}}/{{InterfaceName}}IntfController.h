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

#ifndef {{Interface.Name.upper()}}INTFCONTROLLER_H_
#define {{Interface.Name.upper()}}INTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}Interface.h>

namespace ajn {
namespace services {

/**
 * {{Interface.Name}} Interface Controller class
 */
class {{Interface.Name}}IntfController : public {{Interface.Name}}Interface {
  public:
    /**
     * Constructor of {{Interface.Name}}IntfController
     */
    {{Interface.Name}}IntfController() {}

    /**
     * Destructor of {{Interface.Name}}IntfController
     */
    virtual ~{{Interface.Name}}IntfController() {}

    {% for property in Interface.UserProperties %}
    /**
     * Get {{property.Name}}
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Get{{property.Name}}(void* context = NULL) = 0;
    {% if property.Writable %}
    /**
     * Set {{property.Name}}
     * @param[in] value The {{property.Name.add_spaces_lower()}} to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Set{{property.Name}}(const {{property.Type.ctype()}} value, void* context = NULL) = 0;
    {% endif %}
    {% endfor %}

    {% for method in Interface.Methods %}
    {# TODO: This should only take input args #}
    /**
     * Call {{method.Name}} method
     {% for arg in method.Args %}
     * @param[in] {{arg.Name.camel_case()}} Method argument
     {% endfor %}
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus {{method.Name}}({% for arg in method.Args %}const {{arg.Type.ctype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context = NULL) = 0;
    {% endfor %}
};

} //namespace services
} //namespace ajn

#endif /* {{Interface.Name.upper()}}INTFCONTROLLER_H_ */
