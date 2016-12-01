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

#ifndef {{Interface.Name.upper()}}INTFCONTROLLERLISTENER_H_
#define {{Interface.Name.upper()}}INTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * {{Interface.Name}} Interface Controller Listener class
 */
class {{Interface.Name}}IntfControllerListener : public InterfaceControllerListener {
  public:
    /**
     * Destructor of ChannelIntfControllerListener
     */
    virtual ~{{Interface.Name}}IntfControllerListener() {}

    {% for property in Interface.UserProperties %}

    /**
     * Handler for Get{{property.Name}} completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of {{property.Name}}
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGet{{property.Name}}(QStatus status, const qcc::String& objectPath, const {{property.Type.ctype_arg()}} value, void* context) {}

    /**
     * Handler for {{property.Name}} property changes
     * @param[in] objectPath the object path
     * @param[in] value The value of {{property.Name}}
     */
    virtual void On{{property.Name}}Changed(const qcc::String& objectPath, const {{property.Type.ctype_arg()}} value) {}

    {% if property.Writable %}
    /**
     * Handler for Set{{property.Name}} completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSet{{property.Name}}(QStatus status, const qcc::String& objectPath, void* context) {}

    {% endif %}
    {% endfor %}

    {% for signal in Interface.Signals %}
    /**
     * Handler for {{signal.Name}} signal
     * @param[in] objectPath the object path
     */
    virtual void On{{signal.Name}}(const qcc::String& objectPath) {}

    {% endfor %}
};

} //namespace services
} //namespace ajn

#endif /* {{Interface.Name.upper()}}INTFCONTROLLERLISTENER_H_ */
