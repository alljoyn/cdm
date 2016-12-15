{% import "macros" as macros with context %}
/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controller/InterfaceController.h>
#include <interfaces/controller/{{Interface.Category}}/{{Interface.Name}}IntfControllerListener.h>
#include <interfaces/controller/{{Interface.Category}}/{{Interface.Name}}IntfController.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {
//======================================================================

typedef Ref<{{Interface.Name}}IntfControllerListener> MyInterfaceListener;


class {{Interface.Name}}IntfController::Impl : public InterfaceController
{
  public:

    Impl(
        {{Interface.Name}}IntfController& outer,
        BusAttachment& busAttachment,
        MyInterfaceListener listener,
        Ref<ProxyBusObject> proxyBusObject
        )
      : InterfaceController(proxyBusObject),
        m_outer(outer),
        m_busAttachment(busAttachment),
        m_interfaceListener(listener)
    {
    }

    QStatus Init();

    const char* GetInterfaceName() const
    {
        return m_outer.GetInterfaceName().c_str();
    }

{% for property in Interface.UserProperties %}
    QStatus Get{{property.Name}}(void* context);
{% if property.Writable %}
    QStatus Set{{property.Name}}(const {{property.Type.cpptype_arg()}} value, void* context);
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}
    virtual QStatus {{method.Name}}({% for arg in method.input_args() %}const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context);
{% endfor %}

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

    // The outer facet
    {{Interface.Name}}IntfController& m_outer;

    // and inherit m_proxyObject from InterfaceController
    BusAttachment& m_busAttachment;
    MyInterfaceListener m_interfaceListener;
};

//======================================================================

QStatus {{Interface.Name}}IntfController::Impl::Init()
{
    auto status = m_proxyObject->RegisterPropertiesChangedListener(GetInterfaceName(), NULL, 0, *this, NULL);

    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    const InterfaceDescription* intf = m_outer.GetInterfaceDescription();
    if (intf) {
{% for signal in Interface.Signals %}
        const InterfaceDescription::Member* member = intf->GetMember(s_signal_{{signal.Name}}.c_str());
        if (member) {
            status = m_busAttachment.RegisterSignalHandler(this, static_cast<SignalHandler>(&{{Interface.Name}}IntfController::Impl::{{signal.Name}}), member, NULL);
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: RegisterSignalHandler for {{signal.Name}} signal failed.", __func__));
            }
        } else {
            status = ER_FAIL;
            QCC_LogError(status, ("%s: {{signal.Name}} signal does not exist.", __func__));
        }
{% endfor %}
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: The interface description does not exist.", __func__));
    }

    return status;
}



{% for property in Interface.UserProperties %}

QStatus {{Interface.Name}}IntfController::Impl::Get{{property.Name}}(void* context)
{
    auto status = m_proxyObject->GetPropertyAsync(GetInterfaceName(), s_prop_{{property.Name}}.c_str(), this,
                (ProxyBusObject::Listener::GetPropertyCB)&{{Interface.Name}}IntfController::Impl::Get{{property.Name}}PropertyCB, context);
    return status;
}
{% if property.Writable %}

QStatus {{Interface.Name}}IntfController::Impl::Set{{property.Name}}(const {{property.Type.cpptype_arg()}} value, void* context)
{
    MsgArg arg;
{{ macros.setMsgArg("arg", "value", property.Type)|indent(1 * 4, True)  }}

    auto status = m_proxyObject->SetPropertyAsync(GetInterfaceName(), s_prop_{{property.Name}}.c_str(), arg, this,
                (ProxyBusObject::Listener::SetPropertyCB)&{{Interface.Name}}IntfController::Impl::Set{{property.Name}}PropertyCB, context);
    return status;
}
{% endif %}
{% endfor %}


{% for method in Interface.Methods %}

{% set comma = joiner(", ") %}
QStatus {{Interface.Name}}IntfController::Impl::{{method.Name}}(
{%- for arg in method.input_args() %}{{comma()}}const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}{% endfor %}
{{comma()}}void* context)
{
    // Method call
{% for arg in method.input_args() %}
{% if loop.first %}
    static const size_t numInputs = {{loop.length}};
    MsgArg args[numInputs];

{% endif %}
{{ macros.setMsgArg("args["~loop.index0~"]", arg.Name.camel_case(), arg.Type)|indent(1 * 4, True)  }}
{% else %}{# if there are no args #}
    static const size_t numInputs = 0;
    MsgArg* args = 0;
{% endfor %}

    auto status = m_proxyObject->MethodCallAsync(GetInterfaceName(), s_method_{{method.Name}}.c_str(), this,
                (MessageReceiver::ReplyHandler)&{{Interface.Name}}IntfController::Impl::{{method.Name}}ReplyHandler,
                args, numInputs, context);
    return status;
}
{% endfor %}



void {{Interface.Name}}IntfController::Impl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        {%+ for property in Interface.UserProperties %}if (s_prop_{{property.Name}} == propNameStr) {
            {{property.Type.cpptype()}} val;
{{ macros.getMsgArg("(*propValue)", "val", property.Type)|indent(3 * 4, True) }}
            m_interfaceListener->On{{property.Name}}Changed(obj.GetPath(), val);
        } else {% endfor %}{
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

//======================================================================
// Callbacks

{% for property in Interface.UserProperties %}

void {{Interface.Name}}IntfController::Impl::Get{{property.Name}}PropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (obj) {
        {{property.Type.cpptype()}} val;
{{ macros.getMsgArg("value", "val", property.Type)|indent(2 * 4, True) }}
        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = CdmMsgCvt<{{property.Type.cpptype()}}>().str(value);
            QCC_DbgPrintf(("%s: received property %s=%s", __func__, "{{property.Name}}", s.c_str()));
        }
        m_interfaceListener->OnResponseGet{{property.Name}}(status, obj->GetPath(), val, context);
    }
}



{% if property.Writable %}
void {{Interface.Name}}IntfController::Impl::Set{{property.Name}}PropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    QCC_DbgPrintf(("%s: set completed", __func__));
    if (obj) {
        m_interfaceListener->OnResponseSet{{property.Name}}(status, obj->GetPath(), context);
    }
}
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}



void {{Interface.Name}}IntfController::Impl::{{method.Name}}ReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    size_t numArgs = 0;
    const MsgArg* args = 0;

{% for arg in method.output_args() %}
    {{arg.Type.cpptype()}} arg_{{arg.Name}};
{% endfor %}

    if (message->GetType() == MESSAGE_METHOD_RET) {
        message->GetArgs(numArgs, args);
{% for arg in method.output_args() %}
        CdmMsgCvt<{{arg.Type.cpptype()}}> cvt_{{arg.Name}};
        cvt_{{arg.Name}}.get(args[{{loop.index0}}], arg_{{arg.Name}});

        if (_QCC_DbgPrintCheck(DBG_GEN_MESSAGE, QCC_MODULE)) {
            auto s = cvt_{{arg.Name}}.str(args[{{loop.index0}}]);
            QCC_DbgPrintf(("%s: received reply with %s=%s", __func__, "{{arg.Name}}", s.c_str()));
        }
{% endfor %}
    } else {
        status = ER_FAIL;
    }

    m_interfaceListener->OnResponse{{method.Name}}(status, m_proxyObject->GetPath(){% for arg in method.output_args() %}, arg_{{arg.Name}}{% endfor %}, context, errorName, errorMessage.c_str());
}
{% endfor %}
{% for signal in Interface.Signals %}



void {{Interface.Name}}IntfController::Impl::{{signal.Name}}(const InterfaceDescription::Member* member, const char* srcPath, Message& message)
{
    String path = String(srcPath);

    QCC_DbgPrintf(("%s: received signal %s", __func__, "{{signal.Name}}"));
    m_interfaceListener->On{{signal.Name}}(path);
}
{% endfor %}

//======================================================================
// Forward to the impl

{{Interface.Name}}IntfController::{{Interface.Name}}IntfController(
    BusAttachment& busAttachment,
    Ref<InterfaceControllerListener> listener,
    Ref<ProxyBusObject> cdmProxyObject
    )
  : m_impl(new Impl(*this, busAttachment, dynamic_pointer_cast<{{Interface.Name}}IntfControllerListener>(listener), cdmProxyObject))
{
}



{{Interface.Name}}IntfController::~{{Interface.Name}}IntfController()
{
    delete m_impl;
}



Ref<CdmInterface> {{Interface.Name}}IntfController::CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    return mkRef<{{Interface.Name}}IntfController>(busAttachment, dynamic_pointer_cast<{{Interface.Name}}IntfControllerListener>(listener), cdmProxyObject);
}



QStatus {{Interface.Name}}IntfController::Init()
{
    // Call the superclass Init
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    return m_impl->Init();
}



BusAttachment& {{Interface.Name}}IntfController::GetBusAttachment() const
{
    return m_impl->m_busAttachment;
}
{% for property in Interface.UserProperties %}



QStatus {{Interface.Name}}IntfController::Get{{property.Name}}(void* context)
{
    return m_impl->Get{{property.Name}}(context);
}
{% if property.Writable %}



QStatus {{Interface.Name}}IntfController::Set{{property.Name}}(const {{property.Type.cpptype_arg()}} value, void* context)
{
    return m_impl->Set{{property.Name}}(value, context);
}
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}



QStatus {{Interface.Name}}IntfController::{{method.Name}}(
{%- for arg in method.input_args() %}const {{arg.Type.cpptype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context)
{
    return m_impl->{{method.Name}}({%- for arg in method.input_args() %}{{arg.Name.camel_case()}}, {% endfor %}context);
}
{% endfor %}

//======================================================================
} //namespace services
} //namespace ajn