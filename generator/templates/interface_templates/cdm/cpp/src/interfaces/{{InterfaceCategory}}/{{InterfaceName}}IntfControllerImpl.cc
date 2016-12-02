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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfControllerListener.h>

#include "{{Interface.Name}}IntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* {{Interface.Name}}IntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new {{Interface.Name}}IntfControllerImpl(busAttachment, dynamic_cast<{{Interface.Name}}IntfControllerListener&>(listener), cdmProxyObject);
}

{{Interface.Name}}IntfControllerImpl::{{Interface.Name}}IntfControllerImpl(BusAttachment& busAttachment, {{Interface.Name}}IntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

{{Interface.Name}}IntfControllerImpl::~{{Interface.Name}}IntfControllerImpl()
{
}

QStatus {{Interface.Name}}IntfControllerImpl::Init()
{
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
    }

    return status;
}
{% for property in Interface.UserProperties %}

QStatus {{Interface.Name}}IntfControllerImpl::Get{{property.Name}}(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_{{property.Name}}.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&{{Interface.Name}}IntfControllerImpl::Get{{property.Name}}PropertyCB, context);
    return status;
}
{% if property.Writable %}

QStatus {{Interface.Name}}IntfControllerImpl::Set{{property.Name}}(const {{property.Type.ctype_arg()}} value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("{{property.Type}}", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_{{property.Name}}.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&{{Interface.Name}}IntfControllerImpl::Set{{property.Name}}PropertyCB, context);
    return status;
}
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}

QStatus {{Interface.Name}}IntfControllerImpl::{{method.Name}}({% for arg in method.input_args() %}const {{arg.Type.ctype_arg()}} {{arg.Name.camel_case()}}, {% endfor %}void* context)
{


}
{% endfor %}

void {{Interface.Name}}IntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        {%+ for property in Interface.UserProperties %}if (!s_prop_{{property.Name}}.compare(propNameStr)) {
            if (propValue->typeId == {{property.Type.ajtypeid()}}) {
                m_interfaceListener.On{{property.Name}}Changed(obj.GetPath(), propValue->{{property.Type.ajvar()}});
            }
        } else {% endfor %}{
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}
{% for property in Interface.UserProperties %}

void {{Interface.Name}}IntfControllerImpl::Get{{property.Name}}PropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    {{property.Type.ctype()}} val;
    value.Get("{{property.Type}}", &val);
    m_interfaceListener.OnResponseGet{{property.Name}}(status, obj->GetPath(), val, context);
}
{% if property.Writable %}

void {{Interface.Name}}IntfControllerImpl::Set{{property.Name}}PropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSet{{property.Name}}(status, obj->GetPath(), context);
}
{% endif %}
{% endfor %}
} //namespace services
} //namespace ajn
