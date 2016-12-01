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

#ifndef {{InterfaceName.upper}}INTFCONTROLLEELISTENER_H_
#define {{InterfaceName.upper}}INTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * {{InterfaceName}} Interface Controllee Listener class
 */
class {{InterfaceName}}IntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of {{InterfaceName}}IntfControlleeListener
     */
    virtual ~{{InterfaceName}}IntfControlleeListener() {}

    {{#user_properties}}
    /**
     * Handler for getting {{PropertyName}} property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] out_value current {{PropertyName.add_spaces_lower}}
     * @return ER_OK on success
     */
    virtual QStatus OnGet{{PropertyName}}({{PropertyType.ctype}}& out_value) = 0;
    {{#PropertyWritable}}

    /**
     * Handler for setting {{PropertyName}} property
     * @param[in] value The {{PropertyName.add_spaces_lower}} to set
     * @return ER_OK on success
     */
    virtual QStatus OnSet{{PropertyName}}(const {{PropertyType.ctype}}& value) = 0;
    {{/PropertyWritable}}
    {{/user_properties}}

    {{#methods}}
    /**
     * Handler for method {{MethodName}}
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus On{{MethodName}}({{! TODO: support method arguments! }}ErrorCode& error) = 0;
    {{/methods}}
};

} //namespace services
} //namespace ajn

#endif /* {{InterfaceName.upper}}INTFCONTROLLEELISTENER_H_ */
