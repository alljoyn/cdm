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

#ifndef {{InterfaceName.upper}}INTFCONTROLLER_H_
#define {{InterfaceName.upper}}INTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/{{InterfaceCategory}}/{{InterfaceName}}Interface.h>

namespace ajn {
namespace services {

/**
 * {{InterfaceName}} Interface Controller class
 */
class {{InterfaceName}}IntfController : public {{InterfaceName}}Interface {
  public:
    /**
     * Constructor of {{InterfaceName}}IntfController
     */
    {{InterfaceName}}IntfController() {}

    /**
     * Destructor of {{InterfaceName}}IntfController
     */
    virtual ~{{InterfaceName}}IntfController() {}

    {{#user_properties}}
    /**
     * Get {{PropertyName}}
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Get{{PropertyName}}(void* context = NULL) = 0;
    {{#PropertyWritable}}
    /**
     * Set {{PropertyName}}
     * @param[in] value The {{PropertyName.add_spaces_lower}} to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Set{{PropertyName}}(const {{PropertyType.ctype}} value, void* context = NULL) = 0;
    {{/PropertyWritable}}
    {{/user_properties}}

    {{#methods}}
    {{!TODO: This should only take in args}}
    /**
     * Call {{MethodName}} method
     {{#args}}
     * @param[in] {{ArgName.camel_case}} Method argument
     {{/args}}
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus {{MethodName}}({{#args}}const {{ArgType.ctype_arg}} {{ArgName.camel_case}}, {{/args}}void* context = NULL) = 0;
    {{/methods}}
};

} //namespace services
} //namespace ajn

#endif /* {{InterfaceName.upper}}INTFCONTROLLER_H_ */
