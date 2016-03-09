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

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeProxyBusObject.h>
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfControllerListener.h>

#include "WaterLevelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* WaterLevelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new WaterLevelIntfControllerImpl(busAttachment, dynamic_cast<WaterLevelIntfControllerListener&>(listener), haeProxyObject);
}

WaterLevelIntfControllerImpl::WaterLevelIntfControllerImpl(BusAttachment& busAttachment, WaterLevelIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

WaterLevelIntfControllerImpl::~WaterLevelIntfControllerImpl()
{
}

QStatus WaterLevelIntfControllerImpl::Init()
{
    QStatus status = HaeInterface::Init();
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

void WaterLevelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i)
    {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_CurrentLevel.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_BYTE)
            {
                uint8_t volume = propValue->v_byte;
                m_interfaceListener.CurrentLevelProprtyChanged(obj.GetPath(), volume);
            }
        }
        else if (!s_prop_MaxLevel.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_BYTE)
            {
                uint8_t volume = propValue->v_byte;
                m_interfaceListener.MaxLevelProprtyChanged(obj.GetPath(), volume);
            }
        }
        else if (!s_prop_SupplySource.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_BYTE)
            {
                uint8_t volume = propValue->v_byte;
                m_interfaceListener.SupplySourceProprtyChanged(obj.GetPath(), (WaterLevelSupplySource)volume);
            }
        }
    }
}
QStatus WaterLevelIntfControllerImpl::GetCurrentLevel(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_CurrentLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WaterLevelIntfControllerImpl::OnGetCurrentLevelPropertyCB, context);

    return status;
}

QStatus WaterLevelIntfControllerImpl::GetSupplySource(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupplySource.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WaterLevelIntfControllerImpl::OnGetSupplySourcePropertyCB, context);

    return status;
}

QStatus WaterLevelIntfControllerImpl::GetMaxLevel(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&WaterLevelIntfControllerImpl::OnGetMaxLevelPropertyCB, context);

    return status;
}

void WaterLevelIntfControllerImpl::OnGetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    uint8_t maxLevel;
    value.Get("y", & maxLevel);
    m_interfaceListener.OnGetMaxLevelPropertyCallback(status, obj->GetPath(),maxLevel, context);
}
void WaterLevelIntfControllerImpl::OnGetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    uint8_t currLevel;
    value.Get("y", & currLevel);
    m_interfaceListener.OnGetCurrentLevelPropertyCallback(status, obj->GetPath(),currLevel, context);
}
void WaterLevelIntfControllerImpl::OnGetSupplySourcePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    uint8_t suppSrc;
    value.Get("y", & suppSrc);
    m_interfaceListener.OnGetSupplySourcePropertyCallback(status, obj->GetPath(),(WaterLevelSupplySource)suppSrc, context);
}

} //namespace services
} //namespace ajn
