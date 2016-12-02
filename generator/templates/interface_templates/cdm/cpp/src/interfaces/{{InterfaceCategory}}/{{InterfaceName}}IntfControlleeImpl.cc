/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/{{Interface.Name}}IntfControlleeModel.h>

#include "{{Interface.Name}}IntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* {{Interface.Name}}IntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new {{Interface.Name}}IntfControlleeImpl(busAttachment, dynamic_cast<{{Interface.Name}}IntfControlleeModel&>(listener), cdmBusObject);
}

{{Interface.Name}}IntfControlleeImpl::{{Interface.Name}}IntfControlleeImpl(BusAttachment& busAttachment, {{Interface.Name}}IntfControlleeModel& model, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_{{Interface.Name}}ModelInterface(model),
    m_methodHandlers()
{
}

{{Interface.Name}}IntfControlleeImpl::~{{Interface.Name}}IntfControlleeImpl()
{
}

QStatus {{Interface.Name}}IntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    {% for method in Interface.Methods %}

    const InterfaceDescription::Member* {{method.Name}}Member = m_interfaceDescription->GetMember(s_method_{{method.Name}}.c_str());
    MessageReceiver::MethodHandler {{method.Name}}Handler = static_cast<MessageReceiver::MethodHandler>(&{{Interface.Name}}IntfControlleeImpl::On{{method.Name}});

    m_methodHandlers.push_back(make_pair({{method.Name}}Member, {{method.Name}}Handler));
    {% endfor %}

    return status;
}

QStatus {{Interface.Name}}IntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        {% for property in Interface.UserProperties %}
        if (!(s_prop_{{property.Name}}.compare(propName))) {
            {{property.Type.ctype()}} value;
            status = m_{{Interface.Name}}ModelInterface.Get{{property.Name}}(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }
            msgarg.typeId = {{property.Type.ajtypeid()}};
            msgarg.{{property.Type.ajvar()}} = value;

            return ER_OK;
        } else {%- endfor %} {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus {{Interface.Name}}IntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    {% for property in Interface.UserProperties %}
    if (!(s_prop_{{property.Name}}.compare(propName))) {
        if (msgarg.typeId != {{property.Type.ajtypeid()}}) {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        {% if property.Writable %}
        {{property.Type.ctype()}} value = msgarg.{{property.Type.ajvar()}};
        {% if property.Max != None %}

        if (value > {{property.Max}})
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}
        {% if property.Min != None %}

        if (value < {{property.Min}})
            return ER_BUS_PROPERTY_VALUE_NOT_SET;

        {% endif %}
        status = m_{{Interface.Name}}ModelInterface.Set{{property.Name}}(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }
        {% if property.EmitsChangedSignal %}

        Emit{{property.Name}}Changed(value);
        {% endif %}

        return ER_OK;
        {% else %}
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}
    } else {%- endfor %} {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void {{Interface.Name}}IntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

{% for property in Interface.UserProperties %}
{% if property.EmitsChangedSignal %}
QStatus {{Interface.Name}}IntfControlleeImpl::Emit{{property.Name}}Changed(const {{property.Type.ctype()}} newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
    val.typeId = {{property.Type.ajtypeid()}};
    val.v_bool = newValue;
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_{{property.Name}}.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}
void {{Interface.Name}}IntfControlleeImpl::On{{method.Name}}(const InterfaceDescription::Member* member, Message& msg) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    ErrorCode errorCode = NOT_ERROR;
    status = m_{{Interface.Name}}ModelInterface.{{method.Name}}(errorCode);

    if (status == ER_OK) {
        m_busObject.ReplyMethodCall(msg, status);
        {% for mutator in method.Mutators %}
        Emit{{mutator.Property}}Changed();
        {% endfor %}
    } else {
        if (errorCode == NOT_ERROR) {
            QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
            m_busObject.ReplyMethodCall(msg, status);
        } else {
                m_busObject.ReplyMethodCall(msg, CdmInterface::GetInterfaceErrorName(errorCode).c_str(),
                        CdmInterface::GetInterfaceErrorMessage(errorCode).c_str());
        }
    }
}
{% for mutator in method.Mutators %}

QStatus {{Interface.Name}}IntfControlleeImpl::Emit{{mutator.Property}}Changed()
{
    QStatus status = ER_OK;

    MsgArg val;
    val.typeId = {{mutator.PropertyType.ajtypeid()}};
    val.v_bool = {{mutator.DefaultValue}};
    m_busObject.EmitPropChanged("{{mutator.Interface}}", "{{mutator.Property}}", val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
{% endfor %}
{% endfor %}

{% for signal in Interface.Signals %}
QStatus {{Interface.Name}}IntfControlleeImpl::Emit{{signal.Name}}()
{
    {# TODO: Seems like this GetMember might want to be in the init function like for the method calls? #}
    const InterfaceDescription::Member* member = GetInterfaceDescription()->GetMember(s_signal_{{signal.Name}}.c_str());
    assert(member);
    {% if signal.Sessionless %}
    return m_busObject.Signal(NULL, 0, *member, NULL, 0, 0, ALLJOYN_FLAG_SESSIONLESS);
    {% else %}
    return m_busObject.Signal(NULL, SESSION_ID_ALL_HOSTED, *member, NULL, 0, 0);
    {% endif %}
}

{%- endfor %}
} //namespace services
} //namespace ajn
