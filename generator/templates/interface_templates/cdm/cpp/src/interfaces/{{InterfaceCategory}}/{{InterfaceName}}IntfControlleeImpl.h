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

#ifndef {{Interface.Name.upper()}}INTFCONTROLLEEIMPL_H_
#define {{Interface.Name.upper()}}INTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfControllee.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfControlleeModel.h>

namespace ajn {
namespace services {

class {{Interface.Name}}IntfControlleeListener;
class CdmBusObject;

/**
 * {{Interface.Name}} Interface Controllee implementation class
 */
class {{Interface.Name}}IntfControlleeImpl :
    public InterfaceControllee,
    public {{Interface.Name}}IntfControllee {

  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of {{Interface.Name}}IntfControlleeImpl
     */
    {{Interface.Name}}IntfControlleeImpl(BusAttachment& busAttachment, {{Interface.Name}}IntfControlleeModel& model, CdmBusObject& cdmBusObject);

    /**
     * Destructor of {{Interface.Name}}IntfControlleeImpl
     */
    virtual ~{{Interface.Name}}IntfControlleeImpl();

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
    {% for property in Interface.UserProperties %}
    {% if property.EmitsChangedSignal %}

    /**
     * Emits a changed signal for the {{property.Name}} property
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[in] newValue new value of {{property.Name.add_spaces_lower()}}
     * @return ER_OK on success
     */
    virtual QStatus Emit{{property.Name}}Changed(const {{property.Type.ctype()}} newValue);
    {% endif %}
    {% endfor %}
    {% for method in Interface.Methods %}

    /**
     * Handler of {{method.Name}} method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void On{{method.Name}}(const InterfaceDescription::Member* member, Message& msg);
    {% endfor %}
    {% for method in Interface.Methods %}
    {% for mutator in method.Mutators %}

     /**
     * Emits a signal that the {{mutator.Property}} property from the {{mutator.Interface}} interface has been changed
     * @return ER_OK on success
     */
    QStatus Emit{{mutator.Property}}Changed();
    {% endfor %}
    {% endfor %}
    {% for signal in Interface.Signals %}

    /**
     * Emit {{signal.Name}} signal
     * @return ER_OK on success
     */
    virtual QStatus Emit{{signal.Name}}();
    {% endfor %}

  private:
    BusAttachment& m_busAttachment;
    {{Interface.Name}}IntfControlleeModel& m_{{Interface.Name}}ModelInterface;

    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* {{Interface.Name.upper()}}INTFCONTROLLEEIMPL_H_ */
