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
#include <alljoyn/cdm/interfaces/operation/{{InterfaceName}}IntfControlleeListener.h>

#include "{{InterfaceName}}IntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* {{InterfaceName}}IntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new {{InterfaceName}}IntfControlleeImpl(busAttachment, dynamic_cast<{{InterfaceName}}IntfControlleeListener&>(listener), cdmBusObject);
}

{{InterfaceName}}IntfControlleeImpl::{{InterfaceName}}IntfControlleeImpl(BusAttachment& busAttachment, {{InterfaceName}}IntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    {{#user_properties}}
    m_{{PropertyName.camel_case}}(),
    {{/user_properties}}
    m_methodHandlers()
{
}

{{InterfaceName}}IntfControlleeImpl::~{{InterfaceName}}IntfControlleeImpl()
{
}

QStatus {{InterfaceName}}IntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    {{#methods}}

    const InterfaceDescription::Member* {{MethodName}}Member = m_interfaceDescription->GetMember(s_method_{{MethodName}}.c_str());
    MessageReceiver::MethodHandler {{MethodName}}Handler = static_cast<MessageReceiver::MethodHandler>(&{{InterfaceName}}IntfControlleeImpl::On{{MethodName}});

    m_methodHandlers.push_back(make_pair({{MethodName}}Member, {{MethodName}}Handler));
    {{/methods}}

    return status;
}

QStatus {{InterfaceName}}IntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            {{#user_properties}}
            if (!(s_prop_{{PropertyName}}.compare(propName))) {
                {{PropertyType.ctype}} value;
                status = m_interfaceListener.OnGet{{PropertyName}}(value);
                if (status != ER_OK) {
                    value = Get{{PropertyName}}();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    Set{{PropertyName}}(value); // update the value in {{InterfaceName}}IntfControllee.
                }

                msgarg.typeId = {{PropertyType.ajtypeid}};
                msgarg.{{PropertyType.ajvar}} = value;
            } else{{/user_properties}} {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            {{#user_properties}}
            if (!(s_prop_{{PropertyName}}.compare(propName))) {
                const {{PropertyType.ctype}} value = Get{{PropertyName}}();
                msgarg.typeId = {{PropertyType.ajtypeid}};
                msgarg.{{PropertyType.ajvar}} = value;
            } else{{/user_properties}} {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus {{InterfaceName}}IntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status = ER_OK;

    {{#user_properties}}
    if (!(s_prop_{{PropertyName}}.compare(propName))) {
        if (msgarg.typeId != {{PropertyType.ajtypeid}}) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        {{PropertyType.ctype}} value = msgarg.{{PropertyType.ajvar}};
        status = m_interfaceListener.OnSet{{PropertyName}}(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            Set{{InterfaceName}}(value); // update the value in {{InterfaceName}}IntfControllee.
        }
    } else{{/user_properties}} {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void {{InterfaceName}}IntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

{{#user_properties}}
QStatus {{InterfaceName}}IntfControlleeImpl::Set{{PropertyName}}(const {{PropertyType.ctype_arg}} value)
{
    if (m_{{PropertyName.camel_case}} != value) {
        {{#EmitsChangedSignal}}
        MsgArg msgarg;
        msgarg.typeId = {{PropertyType.ajtypeid}};
        msgarg.{{PropertyType.ajvar}} = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_{{PropertyName}}.c_str(), msgarg, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        {{/EmitsChangedSignal}}
        m_{{PropertyName.camel_case}} = value;
    }
    return ER_OK;
}

{{/user_properties}}

{{#signals}}
QStatus {{InterfaceName}}IntfControlleeImpl::Emit{{SignalName}}()
{
    {{!TODO: Seems like this GetMember might want to be in the init function like for the method calls?}}
    const InterfaceDescription::Member* member = GetInterfaceDescription()->GetMember(s_signal_{{SignalName}}.c_str());
    assert(member);
    {{#SignalSessionless}}
    return m_busObject.Signal(NULL, 0, *member, NULL, 0, 0, ALLJOYN_FLAG_SESSIONLESS);
    {{/SignalSessionless}}
    {{^SignalSessionless}}
    return m_busObject.Signal(NULL, SESSION_ID_ALL_HOSTED, *member, NULL, 0, 0);
    {{/SignalSessionless}}
}

{{/signals}}

} //namespace services
} //namespace ajn
