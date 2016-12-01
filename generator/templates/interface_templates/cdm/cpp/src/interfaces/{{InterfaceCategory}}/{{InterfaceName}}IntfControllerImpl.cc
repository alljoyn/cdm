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
#include <alljoyn/cdm/interfaces/operation/{{InterfaceName}}IntfControllerListener.h>

#include "{{InterfaceName}}IntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* {{InterfaceName}}IntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new {{InterfaceName}}IntfControllerImpl(busAttachment, static_cast<{{InterfaceName}}IntfControllerListener&>(listener), cdmProxyObject);
}

{{InterfaceName}}IntfControllerImpl::{{InterfaceName}}IntfControllerImpl(BusAttachment& busAttachment, {{InterfaceName}}IntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

{{InterfaceName}}IntfControllerImpl::~{{InterfaceName}}IntfControllerImpl()
{
}

QStatus {{InterfaceName}}IntfControllerImpl::Init()
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

{{#user_properties}}



QStatus {{InterfaceName}}IntfControllerImpl::Get{{PropertyName}}(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_{{PropertyName}}.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&{{InterfaceName}}IntfControllerImpl::Get{{PropertyName}}PropertyCB, context);

    return status;
}

{{#PropertyWritable}}
QStatus {{InterfaceName}}IntfControllerImpl::Set{{PropertyName}}(const {{PropertyType.ctype_arg}} value, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("{{PropertyType}}", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_{{PropertyName}}.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&{{InterfaceName}}IntfControllerImpl::Set{{PropertyName}}PropertyCB, context);

    return status;
}
{{/PropertyWritable}}

{{/user_properties}}

void {{InterfaceName}}IntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        {{#user_properties}}
        if (!s_prop_{{PropertyName}}.compare(propNameStr)) {
            if (propValue->typeId == {{PropertyType.ajtypeid}}) {
                m_interfaceListener.On{{PropertyName}}Changed(obj.GetPath(), propValue->{{PropertyType.ajvar}});
            }
        } else{{/user_properties}} {
            QCC_DbgTrace(("Unknown property change signal received"));
        }
    }
}

{{#user_properties}}
void {{InterfaceName}}IntfControllerImpl::Get{{PropertyName}}PropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& msgarg, void* context)
{
    if (!obj) {
        return;
    }

    {{PropertyType.ctype}} value;
    msgarg.Get("{{PropertyType}}", &value);

    m_interfaceListener.OnResponseGet{{PropertyName}}(status, obj->GetPath(), value, context);
}

{{#PropertyWritable}}
void {{InterfaceName}}IntfControllerImpl::Set{{PropertyName}}PropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj) {
        return;
    }

    m_interfaceListener.OnResponseSet{{PropertyName}}(status, obj->GetPath(), context);
}

{{/PropertyWritable}}
{{/user_properties}}



} //namespace services
} //namespace ajn
