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

#ifndef {{InterfaceName.upper}}INTFCONTROLLERIMPL_H_
#define {{InterfaceName.upper}}INTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/{{InterfaceName}}IntfController.h>

namespace ajn {
namespace services {

class {{InterfaceName}}IntfControllerListener;
class CdmProxyBusObject;

/**
 * {{InterfaceName}} Interface Controller implementation class
 */
class {{InterfaceName}}IntfControllerImpl : public InterfaceController, public {{InterfaceName}}IntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of {{InterfaceName}}IntfControllerImpl
     */
    {{InterfaceName}}IntfControllerImpl(BusAttachment& busAttachment, {{InterfaceName}}IntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of {{InterfaceName}}IntfControllerImpl
     */
    virtual ~{{InterfaceName}}IntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    {{#user_properties}}
    /**
     * Get {{PropertyName}}
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Get{{PropertyName}}(void* context = NULL);
    {{#PropertyWritable}}
    /**
     * Set {{PropertyName}}
     * @param[in] value The {{PropertyName.add_spaces_lower}} to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Set{{PropertyName}}(const {{PropertyType.ctype}} value, void* context = NULL);
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
    virtual QStatus {{MethodName}}({{#args}}const {{ArgType.ctype_arg}} {{ArgName.camel_case}}, {{/args}}void* context = NULL);
    {{/methods}}

  private:
    {{InterfaceName}}IntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    {{#user_properties}}
    void Get{{PropertyName}}PropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    {{#PropertyWritable}}
    void Set{{PropertyName}}PropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    {{/PropertyWritable}}
    {{/user_properties}}

    BusAttachment& m_busAttachment;
    {{InterfaceName}}IntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* {{InterfaceName.upper}}INTFCONTROLLERIMPL_H_ */
