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
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControllerListener.h>

#include "PlugInUnitsIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* PlugInUnitsIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new PlugInUnitsIntfControllerImpl(busAttachment, dynamic_cast<PlugInUnitsIntfControllerListener&>(listener), cdmProxyObject);
}

PlugInUnitsIntfControllerImpl::PlugInUnitsIntfControllerImpl(BusAttachment& busAttachment, PlugInUnitsIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

PlugInUnitsIntfControllerImpl::~PlugInUnitsIntfControllerImpl()
{
}

QStatus PlugInUnitsIntfControllerImpl::Init()
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

QStatus PlugInUnitsIntfControllerImpl::GetPlugInUnits(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_PlugInUnits.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&PlugInUnitsIntfControllerImpl::GetPlugInUnitsPropertyCB,context);

    return status;
}

void PlugInUnitsIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_PlugInUnits.compare(propNameStr)) {
            if (!propValue[0].HasSignature("a(oub)"))
            {
                return;
            }

            MsgArg* unitEntries;
            size_t numUnitEntries;

            PlugInUnitsInterface::PlugInUnits units;
            PlugInUnitsInterface::PlugInInfo info;
            propValue[0].Get("a(oub)", &numUnitEntries, &unitEntries);
            for (size_t i = 0; i < numUnitEntries; ++i)
            {
                char* objPath = NULL;
                unitEntries[i].Get("(oub)", &objPath, &info.deviceId, &info.pluggedIn);
                info.objectPath = objPath;
                units.push_back(info);
            }
            m_interfaceListener.OnPlugInUnitsChanged(obj.GetPath(), units);
        }
    }
}

void PlugInUnitsIntfControllerImpl::GetPlugInUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    MsgArg* unitEntries;
    size_t numUnitEntries;

    PlugInUnitsInterface::PlugInUnits units;
    PlugInUnitsInterface::PlugInInfo info;
    value.Get("a(oub)", &numUnitEntries, &unitEntries);
    for (size_t i = 0; i < numUnitEntries; ++i)
    {
        char* objPath = NULL;
        unitEntries[i].Get("(oub)", &objPath, &info.deviceId, &info.pluggedIn);
        info.objectPath = objPath;
        units.push_back(info);
    }
    m_interfaceListener.OnResponseGetPlugInUnits(status, obj->GetPath(), units, context);
}

} //namespace services
} //namespace ajn
