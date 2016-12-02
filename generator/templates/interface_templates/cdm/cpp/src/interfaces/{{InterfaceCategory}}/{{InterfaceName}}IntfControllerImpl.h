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

#ifndef {{Interface.Name.upper()}}INTFCONTROLLERIMPL_H_
#define {{Interface.Name.upper()}}INTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfController.h>

namespace ajn {
namespace services {

class {{Interface.Name}}IntfControllerListener;

/**
 * {{Interface.Name}} Interface Controller implementation class
 */
class {{Interface.Name}}IntfControllerImpl : public InterfaceController, public {{Interface.Name}}IntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of {{Interface.Name}}IntfControllerImpl
     */
    {{Interface.Name}}IntfControllerImpl(BusAttachment& busAttachment, {{Interface.Name}}IntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of {{Interface.Name}}IntfControllerImpl
     */
    virtual ~{{Interface.Name}}IntfControllerImpl();

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
    {% for property in Interface.UserProperties %}

    /**
     * Get {{property.Name}} property
     {% if "en" in property.doc %}
     * ({{property.doc["en"]}})
     {% endif %}     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Get{{property.Name}}(void* context);
    {% if property.Writable %}

    /**
     * Set {{property.Name}} property
     {% if "en" in property.doc %}
     * ({{property.doc["en"]}})
     {% endif %}
     * @param[in] value The {{property.Name.add_spaces_lower()}} to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Set{{property.Name}}(const {{property.Type.ctype_arg()}} value, void* context);
    {% endif %}
    {% endfor %}
    {% for method in Interface.Methods %}

    /**
     * Call {{method.Name}} method
     {% if "en" in method.doc %}
     * ({{method.doc["en"]}})
     {% endif %}
     {% for arg in method.input_args() %}
     * @param[in] {{arg.Name.camel_case()}} {%if "en" in arg.doc%}{{arg.doc["en"]}}{%else%}Method argument{%endif%}

     {% endfor %}
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus {{method.Name}}({% for arg in method.input_args() %}const {{arg.Type.ctype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context);
    {% endfor %}

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    {% for property in Interface.UserProperties %}
    void Get{{property.Name}}PropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    {% if property.Writable %}
    void Set{{property.Name}}PropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    {% endif %}
    {% endfor %}
    {% for method in Interface.Methods %}
    void {{method.Name}}ReplyHandler(Message& message, void* context);
    {% endfor %}
    {% for signal in Interface.Signals %}
    void {{signal.Name}}(const InterfaceDescription::Member* member, const char* srcPath, Message& message);
    {% endfor %}

    BusAttachment& m_busAttachment;
    {{Interface.Name}}IntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* {{Interface.Name.upper()}}INTFCONTROLLERIMPL_H_ */
