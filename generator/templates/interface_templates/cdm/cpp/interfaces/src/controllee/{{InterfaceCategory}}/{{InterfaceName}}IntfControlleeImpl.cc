{% macro setMsgArg(msgName, valueName, property) %}
    {% if property.Type.ajtypeIsVectorOfStruct(Interface) %}
{
    std::vector<MsgArg> array({{valueName}}.size());
    for (auto& v : {{valueName}}) {
        {{msgName}}.Set("{{property.Type.ajtypeVectorOfStructSig()}}"{% for field in property.Type.ajtypeVectorOfStructFieldGets(Interface) %}, v.{{field}}{% endfor %});
    }
    {{msgName}}.Set("{{property.Type.signature}}", array.size(), array.data());
    {{msgName}}.Stabilize();
}
    {% else %}
CdmMsgCvt<{{property.Type.ctype()}}> converter;
converter.set({{msgName}}, {{valueName}});
    {% endif %}
{%- endmacro %}

{%- macro getMsgArg(msgName, valueName, property) %}
    {% if property.Type.ajtypeIsVectorOfStruct(Interface) %}
{
    MsgArg *entries;
    size_t len;

    {{msgName}}.Get("{{property.Type.signature}}", &len, &entries);
    {{valueName}}.clear();

    for (size_t i = 0; i < len; ++i) {
        {{property.Type.ajtypeVectorOfStructName()}} v;
        {% for field in property.Type.ajtypeVectorOfStructFieldSets(Interface) %}{{field.type}} {{field.name}};
        {% endfor %});
        {{msgName}}.Get("{{property.Type.ajtypeVectorOfStructSig()}}"{% for field in property.Type.ajtypeVectorOfStructFieldSets(Interface) %}, &v.{{field}}{% endfor %});
        {% for field in property.Type.ajtypeVectorOfStructFieldSets(Interface) %}
        v.{{field.name}} = {{field.name}};
        {% endfor %});
        {{valueName}}.push_back(v);
    }
}
    {% else %}
CdmMsgCvt<{{property.Type.ctype()}}> converter;
converter.get({{msgName}}, {{valueName}});
    {% endif %}
{%- endmacro %}
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

#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <interfaces/controllee/operation/{{Interface.Name}}IntfControllee.h>
#include <interfaces/controllee/operation/{{Interface.Name}}IntfControlleeModel.h>


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
    static Impl* CreateInterface(BusAttachment& busAttachment, Ref<{{Interface.Name}}IntfControlleeModel> model, CdmBusObject& cdmBusObject);

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
    void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) override;

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
    QStatus Emit{{property.Name}}Changed(const {{property.Type.ctype()}} newValue);
    {% endif %}
    {% endfor %}
    {% for method in Interface.Methods %}

    /**
     * Handler of {{method.Name}} method
     * @param member
     * @param msg reference of alljoyn Message
     */
    void On{{method.Name}}(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects);
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
    Impl(BusAttachment& busAttachment, Ref<{{Interface.Name}}IntfControlleeModel> model, CdmBusObject& cdmBusObject);


    BusAttachment& m_busAttachment;
    Ref<{{Interface.Name}}IntfControlleeModel> m_{{Interface.Name}}ModelInterface;

    MethodHandlers m_methodHandlers;
};

/*
 * Forwarding
 */
{{Interface.Name}}IntfControllee::{{Interface.Name}}IntfControllee(BusAttachment& busAttachment, Ref<InterfaceControlleeModel> model, CdmBusObject& cdmBusObject)
    : m_impl(Impl::CreateInterface(busAttachment, dynamic_pointer_cast<{{Interface.Name}}IntfControlleeModel>(model), cdmBusObject))
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

QStatus {{Interface.Name}}IntfControllee::Emit{{property.Name}}Changed(const {{property.Type.ctype()}} newValue)
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
    CdmBusObject& cdmBusObject)
{
    {{Interface.Name}}IntfControllee::Impl* interface = new {{Interface.Name}}IntfControllee::Impl(busAttachment, model, cdmBusObject);

    QStatus status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not initialize interface", __func__));
        goto ERROR;
    }

    status = cdmBusObject.RegisterInterface(interface);
    if (status != ER_OK) {
        goto ERROR;
    }

    return interface;

ERROR:
    delete interface;
    return nullptr;
}

{{Interface.Name}}IntfControllee::Impl::Impl(BusAttachment& busAttachment, Ref<{{Interface.Name}}IntfControlleeModel> model, CdmBusObject& cdmBusObject) :
    InterfaceReceiver(cdmBusObject),
    m_busAttachment(busAttachment),
    m_{{Interface.Name}}ModelInterface(model),
    m_methodHandlers()
{}


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
    QStatus status;

    if (!(s_prop_Version.compare(propName))) {
        msgarg.typeId = ALLJOYN_UINT16;
        msgarg.v_uint16 = GetInterfaceVersion();
        return ER_OK;
    } else {
        {% for property in Interface.UserProperties %}
        if (!(s_prop_{{property.Name}}.compare(propName))) {
            {{property.Type.ctype()}} value;
            status = m_{{Interface.Name}}ModelInterface->Get{{property.Name}}(value);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                return ER_FAIL;
            }

{{ setMsgArg("msgarg", "value", property)|indent(3 * 4, True) }}
            return ER_OK;
        } else {%- endfor %} {
            return ER_BUS_NO_SUCH_PROPERTY;
        }
    }
}

QStatus {{Interface.Name}}IntfControllee::Impl::OnSetProperty(const String& propName, MsgArg& msgarg)
{
    QStatus status;

    {% for property in Interface.UserProperties %}
    if (!(s_prop_{{property.Name}}.compare(propName))) {
        if (msgarg.Signature() != "{{property.Type.signature}}") {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        {% if property.Writable %}
        {{property.Type.ctype()}} value;
{{ getMsgArg("msgarg", "value", property)|indent(2 * 4, True) }}
        {% if property.Max != None %}

        if (value > {{property.Max}})
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}
        {% if property.Min != None %}

        if (value < {{property.Min}})
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}
        {% if property.MaxFromProperty != None %}

        {{Interface.PropLUT[property.MaxFromProperty].Type.ctype()}} maxValue;
        status = m_{{Interface.Name}}ModelInterface->Get{{property.MaxFromProperty}}(maxValue);
        if (value > maxValue)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}
        {% if property.MinFromProperty != None %}

        {{Interface.PropLUT[property.MinFromProperty].Type.ctype()}} minValue;
        status = m_{{Interface.Name}}ModelInterface->Get{{property.MinFromProperty}}(minValue);
        if (value < minValue)
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        {% endif %}

        status = m_{{Interface.Name}}ModelInterface->Set{{property.Name}}(value);
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

void {{Interface.Name}}IntfControllee::Impl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            InterfaceReceiver::CdmMethodHandler handler = it->second;
            (this->*handler)(member, msg, sideEffects);
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
QStatus {{Interface.Name}}IntfControllee::Impl::Emit{{property.Name}}Changed(const {{property.Type.ctype()}} newValue)
{
    QStatus status = ER_OK;

    MsgArg val;
{{ setMsgArg("val", "newValue", property)|indent(1 * 4, True) }}
    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_{{property.Name}}.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);

    return status;
}
{% endif %}
{% endfor %}

{% for method in Interface.Methods %}
void {{Interface.Name}}IntfControllee::Impl::On{{method.Name}}(const InterfaceDescription::Member* member, Message& msg, CdmSideEffects& sideEffects) {
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

{% for arg in method.Args %}
    {{arg.Type.ctype()}} arg_{{arg.Name}};
{% endfor %}
{% for arg in method.Args if arg.Direction == "in" %}

    {
        CdmMsgCvt<{{arg.Type.ctype()}}> cvt;
        cvt.get(args[{{loop.index0}}], arg_{{arg.Name}});
    }
{% endfor %}

    ErrorCode errorCode = NOT_ERROR;
{% set comma = joiner(", ") %}
    status = m_{{Interface.Name}}ModelInterface->{{method.Name}}(
{%- for arg in method.Args if arg.Direction == "in" %}{{comma()}}arg_{{arg.Name}}{% endfor %}
{%- for arg in method.Args if arg.Direction == "out" %}{{comma()}}arg_{{arg.Name}}{% endfor %}{{comma()}}errorCode, sideEffects);

{% for arg in method.Args if arg.Direction == "out" %}
{% set hasReply = True %}
    MsgArg reply;
    CdmMsgCvt<{{arg.Type.ctype()}}> replyCvt;
    replyCvt.set(reply, arg_{{arg.Name}});
{% endfor %}

    if (status == ER_OK) {
{% if hasReply is defined %}
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
