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

#ifndef {{InterfaceName.upper}}INTFCONTROLLEEIMPL_H_
#define {{InterfaceName.upper}}INTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/{{InterfaceName}}IntfControllee.h>

namespace ajn {
namespace services {

class {{InterfaceName}}IntfControlleeListener;
class CdmBusObject;

/**
 * {{InterfaceName}} Interface Controllee implementation class
 */
class {{InterfaceName}}IntfControlleeImpl : public InterfaceControllee, public {{InterfaceName}}IntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of {{InterfaceName}}IntfControlleeImpl
     */
    {{InterfaceName}}IntfControlleeImpl(BusAttachment& busAttachment, {{InterfaceName}}IntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of {{InterfaceName}}IntfControlleeImpl
     */
    virtual ~{{InterfaceName}}IntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param[in] propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param[in] propName  Identifies the property to set
     * @param[in] val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * method handler
     * @param[in] member    Method interface member entry.
     * @param[in] message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    {{#user_properties}}
    /**
     * Get {{PropertyName}}
     * @return current {{PropertyName.add_spaces_lower}}
     */
    virtual const {{PropertyType.ctype}} Get{{PropertyName}}() const { return m_{{PropertyName.camel_case}}; }

    /**
     * Set {{PropertyName}}
     * @param[in] value The {{PropertyName.add_spaces_lower}} to set
     * @return ER_OK on success
     */
    virtual QStatus Set{{PropertyName}}(const {{PropertyType.ctype_arg}} value);
    {{/user_properties}}

    {{#signals}}
    /**
     * Emit {{SignalName}} signal
     * @return ER_OK on success
     */
    virtual QStatus Emit{{SignalName}}();

    {{/signals}}

  private:
    {{InterfaceName}}IntfControlleeImpl();

    BusAttachment& m_busAttachment;
    {{InterfaceName}}IntfControlleeListener& m_interfaceListener;

    {{#user_properties}}
    {{PropertyType.ctype}} m_{{PropertyName.camel_case}};
    {{/user_properties}}

    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* {{InterfaceName.upper}}INTFCONTROLLEEIMPL_H_ */
