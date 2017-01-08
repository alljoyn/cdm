{% import "macros" as macros with context %}
/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <interfaces/controllee/{{Interface.Category}}/{{Interface.Name}}IntfControllee.h>
#include <interfaces/controllee/{{Interface.Category}}/{{Interface.Name}}IntfControlleeModel.h>

#include "../CdmInterfaceValidation.h"


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

/**
 * {{Interface.Name}} Interface Controllee implementation class
 */
class {{Interface.Name}}IntfControllee::Impl :
    public InterfaceReceiver,
    public {{Interface.Name}}Interface
{

  public:
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<{{Interface.Name}}IntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee);

    /**
     * Initialize interface
     * @return status
     */
    QStatus Init() override;

    /**
     * a callback function for getting property.
     * @param[in] propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    QStatus OnGetProperty(const qcc::String& propName, MsgArg& val) override;

    /**
     * a callback function for setting property.
     * @param[in] propName  Identifies the property to set
     * @param[in] val       The property value to set. The type of this value is the actual value type.
     */
    QStatus OnSetProperty(const qcc::String& propName, MsgArg& val) override;

    /**
     * method handler
     * @param[in] member    Method interface member entry.
     * @param[in] message   The received method call message.
     */
    void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg) override;

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    const MethodHandlers& GetMethodHanders() const override { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    BusAttachment& GetBusAttachment() const override { return m_busAttachment; }
    {% for property in Interface.UserProperties %}
    {% if property.EmitsChangedSignal %}

    /**
     * Emits a changed signal for the {{property.Name}} property
     * @param[in] newValue new value of {{property.Name.add_spaces_lower()}}
     * @return ER_OK on success
     */
    QStatus Emit{{property.Name}}Changed(const {{property.Type.cpptype_arg()}} newValue);
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
    {% for signal in Interface.Signals %}

    /**
     * Emit {{signal.Name}} signal
     * @return ER_OK on success
     */
    QStatus Emit{{signal.Name}}();
    {% endfor %}

  private:
    /**
     * Constructor of {{Interface.Name}}IntfControllee::Impl
     */
    Impl(BusAttachment& busAttachment, Ref<{{Interface.Name}}IntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee);
    {% for property in Interface.UserProperties %}
    {% if property.Writable %}
    {% if property.ValueIn or property.Type.ajtypeIsEnum() %}

    QStatus Validate{{property.Name}}({{property.Type.cpptype_arg()}} value);
    {% endif %}
    {% if property.Clamp %}

    QStatus clamp{{property.Name}}({{property.Type.cpptype_arg()}} value, {{property.Type.cpptype_arg()}}& out);
    {% endif %}
    {% endif %}
    {% endfor %}

    BusAttachment& m_busAttachment;
    CdmControllee& m_cdmControllee;
    MethodHandlers m_methodHandlers;

    Ref<{{Interface.Name}}IntfControlleeModel> m_{{Interface.Name}}ModelInterface;
};

/*
 * Forwarding
 */
{{Interface.Name}}IntfControllee::{{Interface.Name}}IntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<{{Interface.Name}}IntfControlleeModel>(model), cdmBusObject, cdmControllee))
{}


{{Interface.Name}}IntfControllee::~{{Interface.Name}}IntfControllee()
{
    delete m_impl;
}

const qcc::String& {{Interface.Name}}IntfControllee::GetInterfaceName() const
{
    return m_impl->GetInterfaceName();
}
{% for property in Interface.UserProperties %}
{% if property.EmitsChangedSignal %}

QStatus {{Interface.Name}}IntfControllee::Emit{{property.Name}}Changed(const {{property.Type.cpptype_arg()}} newValue)
{
    return (m_impl == nullptr) ? ER_FAIL : m_impl->Emit{{property.Name}}Changed(newValue);
}
{% endif %}
{% endfor %}

{% for signal in Interface.Signals %}
QStatus {{Interface.Name}}IntfControllee::Emit{{signal.Name}}()
{
    return m_impl->Emit{{signal.Name}}();
}

{% endfor %}

/*
 * Implementation
 */
 {{Interface.Name}}IntfControllee::Impl* {{Interface.Name}}IntfControllee::Impl::CreateInterface(
    BusAttachment& busAttachment,
    Ref<{{Interface.Name}}IntfControlleeModel> model,
    CdmBusObject& cdmBusObject,
    CdmControllee& cdmControllee)
{
    {{Interface.Name}}IntfControllee::Impl* interface = new {{Interface.Name}}IntfControllee::Impl(busAttachment, model, cdmBusObject, cdmControllee);

    QStatus status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not initialize interface", __func__));
        goto ERROR_CLEANUP;
    }

    status = cdmBusObject.RegisterInterface(interface);
    if (status != ER_OK) {
        goto ERROR_CLEANUP;
    }

    return interface;

ERROR_CLEANUP:
    delete interface;
    return nullptr;
}

{{Interface.Name}}IntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<{{Interface.Name}}IntfControlleeModel> model, CdmBusObject& cdmBusObject, CdmControllee& cdmControllee) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_cdmControllee(cdmControllee),
    m_methodHandlers(),
    m_{{Interface.Name}}ModelInterface(model)
{
    ignore_unused(m_cdmControllee);
}


QStatus {{Interface.Name}}IntfControllee::Impl::Init()
{
    QStatus status = CdmInterface::Init();
    {% for method in Interface.Methods %}

    const InterfaceDescription::Member* {{method.Name}}Member = m_interfaceDescription->GetMember(s_method_{{method.Name}}.c_str());
    InterfaceReceiver::CdmMethodHandler {{method.Name}}Handler = static_cast<InterfaceReceiver::CdmMethodHandler>(&Impl::On{{method.Name}});

    m_methodHandlers.push_back(make_pair({{method.Name}}Member, {{method.Name}}Handler));
    {% endfor %}

    return status;
}

QStatus {{Interface.Name}}IntfControllee::Impl::OnGetProperty(const String& propName, MsgArg& msgarg)
{
    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        {% for property in Interface.UserProperties %}
        if (!(s_prop_{{property.Name}}.compare(propName))) {
            {{property.Type.cpptype()}} value;
            auto status = m_{{Interface.Name}}ModelInterface->Get{{property.Name}}(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

{{ macros.setMsgArg("msgarg", "value", property.Type)|indent(3 * 4, True) }}
            return ER_OK;
        } else {%- endfor %} {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus {{Interface.Name}}IntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    {% for property in Interface.UserProperties %}
    if (!(s_prop_{{property.Name}}.compare(propName))) {
        if (msgarg.Signature() != "{{property.Type.signature}}") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
        {% if property.Writable %}
        {{property.Type.cpptype()}} value;
{{ macros.getMsgArg("msgarg", "value", property.Type)|indent(2 * 4, True) }}

        {{property.Type.cpptype()}} validValue = value;
        {% if property.CustomCheck %}

        {% include ["patch/" ~ Interface.Name ~ "_Validate" ~ property.Name ~ ".cc", "patch/TODO.cc"] ignore missing with context %}
        {% else %}
        {% if property.Clamp %}

        if (clamp{{property.Name}}(value, validValue) != ER_OK)
            return ER_INVALID_DATA;
        {% endif %}
        {% if property.ValueIn or property.Type.ajtypeIsEnum() %}

        if (Validate{{property.Name}}(validValue) != ER_OK)
            return ER_INVALID_DATA;
        {% endif %}
        {% endif %}

        QStatus status = m_{{Interface.Name}}ModelInterface->Set{{property.Name}}(validValue);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }
        {% if property.EmitsChangedSignal %}

        if (m_cdmControllee.EmitChangedSignalOnSetProperty())
            Emit{{property.Name}}Changed(validValue);
        {% endif %}

        return ER_OK;
        {% else %}
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}
    } else {%- endfor %} {
        return ER_BUS_NO_SUCH_PROPERTY;
    }
}

void {{Interface.Name}}IntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            InterfaceReceiver::CdmMethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        auto status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}
{% for property in Interface.UserProperties %}
{% if property.EmitsChangedSignal %}

QStatus {{Interface.Name}}IntfControllee::Impl::Emit{{property.Name}}Changed(const {{property.Type.cpptype_arg()}} newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
{{ macros.setMsgArg("val", "newValue", property.Type)|indent(1 * 4, True) }}
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_{{property.Name}}.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}
void {{Interface.Name}}IntfControllee::Impl::On{{method.Name}}(const InterfaceDescription::Member* member, Message& msg) {
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

{% for arg in method.Args %}
    {{arg.Type.cpptype()}} arg_{{arg.Name}};
{% endfor %}
{% for arg in method.input_args() %}

    {
        CdmMsgCvt<{{arg.Type.cpptype()}}> cvt;
        cvt.get(args[{{loop.index0}}], arg_{{arg.Name}});
    }
{% endfor %}

    ErrorCode errorCode = NOT_ERROR;
{% set comma = joiner(", ") %}
    auto status = m_{{Interface.Name}}ModelInterface->{{method.Name}}(
{%- for arg in method.input_args() %}{{comma()}}arg_{{arg.Name}}{% endfor %}
{%- for arg in method.output_args() %}{{comma()}}arg_{{arg.Name}}{% endfor %}{{comma()}}errorCode, m_cdmControllee);

{% set numArgs = method.output_args()|length %}
{% for arg in method.output_args() %}
    // TODO this only allows one output arg
    MsgArg reply;
    CdmMsgCvt<{{arg.Type.cpptype()}}> replyCvt;
    replyCvt.set(reply, arg_{{arg.Name}});
{% endfor %}

    if (status == ER_OK) {
{% if numArgs > 0 %}
        m_busObject.ReplyMethodCall(msg, &reply, 1);
{% else %}
        m_busObject.ReplyMethodCall(msg, status);
{% endif %}
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
{% endfor %}
{% for signal in Interface.Signals %}

QStatus {{Interface.Name}}IntfControllee::Impl::Emit{{signal.Name}}()
{
    {# TODO: Seems like this GetMember might want to be in the init function like for the method calls? #}
    const InterfaceDescription::Member* member = GetInterfaceDescription()->GetMember(s_signal_{{signal.Name}}.c_str());
    QCC_ASSERT(member);
    {% if signal.Sessionless %}
    return m_busObject.Signal(NULL, 0, *member, NULL, 0, 0, ALLJOYN_FLAG_SESSIONLESS);
    {% else %}
    return m_busObject.Signal(NULL, SESSION_ID_ALL_HOSTED, *member, NULL, 0, 0);
    {% endif %}
}

{% endfor %}
{% for property in Interface.UserProperties %}
{% if property.Writable %}
{% if property.ValueIn or property.Type.ajtypeIsEnum() %}

QStatus {{Interface.Name}}IntfControllee::Impl::Validate{{property.Name}}({{property.Type.cpptype_arg()}} value)
{
    {% if property.Type.ajtypeIsEnum() %}
    {% set enum = property.Type.ajtypeIsEnum() %}
    switch (value)
    {
        {% for ename in enum.Values %}
        case {{Interface.Name}}Interface::{{macros.enumName(enum, ename)}}:
        {% endfor %}
            break;
        {% for ename in enum.InvalidValues %}
        case {{Interface.Name}}Interface::{{macros.enumName(enum, ename)}}:
        {% endfor %}
        default:
            return ER_INVALID_DATA;
    }
    {% endif %}
    {% if property.ValueIn %}

    {{Interface.PropLUT[property.ValueIn].Type.cpptype()}} validValues;
    if (m_{{Interface.Name}}ModelInterface->Get{{property.ValueIn}}(validValues) != ER_OK)
        return ER_FAIL;

    if (std::find(validValues.begin(), validValues.end(), value) == validValues.end())
        return ER_INVALID_DATA;

    {% endif %}
    return ER_OK;
}
{% endif %}
{% if property.Clamp %}

QStatus {{Interface.Name}}IntfControllee::Impl::clamp{{property.Name}}({{property.Type.cpptype_arg()}} value, {{property.Type.cpptype_arg()}}& out)
{
    {% if property.Min != None and property.MinFromProperty == None %}

    {{property.Type.cpptype()}} minValue = {{property.Min}};
    {% endif %}
    {% if property.MinFromProperty != None %}

    {{Interface.PropLUT[property.MinFromProperty].Type.cpptype()}} minValue;
    if (m_{{Interface.Name}}ModelInterface->Get{{property.MinFromProperty}}(minValue) != ER_OK)
        return ER_FAIL;
    {% endif %}
    {% if property.Max != None %}

    {{property.Type.cpptype()}} maxValue = {{property.Max}};{% endif %}
    {% if property.MaxFromProperty != None %}

    {{Interface.PropLUT[property.MaxFromProperty].Type.cpptype()}} maxValue;
    if (m_{{Interface.Name}}ModelInterface->Get{{property.MaxFromProperty}}(maxValue) != ER_OK)
        return ER_FAIL;
    {% endif %}

    {{property.Type.cpptype()}} stepValue = 0;
    {% if property.StepFromProperty != None %}
    if (m_{{Interface.Name}}ModelInterface->Get{{property.StepFromProperty}}(stepValue) != ER_OK)
        return ER_FAIL;
    {% endif %}

    out = clamp<{{property.Type.cpptype()}}>(value, minValue, maxValue, stepValue);
    return ER_OK;
}
{% endif %}
{% endif %}
{% endfor %}

} //namespace services
} //namespace ajn
