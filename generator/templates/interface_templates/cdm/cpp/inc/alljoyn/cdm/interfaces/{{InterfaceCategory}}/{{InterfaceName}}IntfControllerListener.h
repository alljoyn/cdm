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

#ifndef {{InterfaceName.upper}}INTFCONTROLLERLISTENER_H_
#define {{InterfaceName.upper}}INTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * {{InterfaceName}} Interface Controller Listener class
 */
class {{InterfaceName}}IntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of ChannelIntfControllerListener
     */
    virtual ~{{InterfaceName}}IntfControllerListener() {}

    {{#user_properties}}

    /**
     * Handler for Get{{PropertyName}} completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of {{PropertyName}}
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGet{{PropertyName}}(QStatus status, const qcc::String& objectPath, const {{PropertyType.ctype_arg}} value, void* context) {}

    /**
     * Handler for {{PropertyName}} property changes
     * @param[in] objectPath the object path
     * @param[in] value The value of {{PropertyName}}
     */
    virtual void On{{PropertyName}}Changed(const qcc::String& objectPath, const {{PropertyType.ctype_arg}} value) {}

    {{#PropertyWritable}}
    /**
     * Handler for Set{{PropertyName}} completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSet{{PropertyName}}(QStatus status, const qcc::String& objectPath, void* context) {}

    {{/PropertyWritable}}
    {{/user_properties}}

    {{#signals}}
    /**
     * Handler for {{SignalName}} signal
     * @param[in] objectPath the object path
     */
    virtual void On{{SignalName}}(const qcc::String& objectPath) {}

    {{/signals}}
};

} //namespace services
} //namespace ajn

#endif /* {{InterfaceName.upper}}INTFCONTROLLERLISTENER_H_ */
