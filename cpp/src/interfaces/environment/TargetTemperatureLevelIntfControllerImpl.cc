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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllerListener.h>
#include "TargetTemperatureLevelIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TargetTemperatureLevelIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new TargetTemperatureLevelIntfControllerImpl(busAttachment, dynamic_cast<TargetTemperatureLevelIntfControllerListener&>(listener), cdmProxyObject);
}

TargetTemperatureLevelIntfControllerImpl::TargetTemperatureLevelIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureLevelIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TargetTemperatureLevelIntfControllerImpl::~TargetTemperatureLevelIntfControllerImpl()
{
}

QStatus TargetTemperatureLevelIntfControllerImpl::Init()
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

QStatus TargetTemperatureLevelIntfControllerImpl::GetMaxLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureLevelIntfControllerImpl::GetMaxLevelPropertyCB, context);
    return status;
}

QStatus TargetTemperatureLevelIntfControllerImpl::GetTargetLevel(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetLevel.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureLevelIntfControllerImpl::GetTargetLevelPropertyCB, context);
    return status;
}

QStatus TargetTemperatureLevelIntfControllerImpl::SetTargetLevel(const uint8_t value, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("y", value);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_TargetLevel.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&TargetTemperatureLevelIntfControllerImpl::SetTargetLevelPropertyCB, context);
    return status;
}

QStatus TargetTemperatureLevelIntfControllerImpl::GetSelectableTemperatureLevels(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SelectableTemperatureLevels.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TargetTemperatureLevelIntfControllerImpl::GetSelectableTemperatureLevelsPropertyCB, context);
    return status;
}

void TargetTemperatureLevelIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_TargetLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnTargetLevelChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_MaxLevel.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t value = propValue->v_byte;
                m_interfaceListener.OnMaxLevelChanged(obj.GetPath(), value);
            }
        } else if  (!s_prop_SelectableTemperatureLevels.compare(propNameStr)) {
            if(propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                TemperatureLevels levels;
                for (size_t i = 0; i < numVals; ++i)
                    levels.push_back(vals[i]);
                m_interfaceListener.OnSelectableTemperatureLevelsChanged(obj.GetPath(), levels);
            }
        }
    }
}

void TargetTemperatureLevelIntfControllerImpl::GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetMaxLevel(status, obj->GetPath(), val, context);
}

void TargetTemperatureLevelIntfControllerImpl::GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
            return;
    }
    uint8_t val;
    value.Get("y", &val);
    m_interfaceListener.OnResponseGetTargetLevel(status, obj->GetPath(), val, context);
}

void TargetTemperatureLevelIntfControllerImpl::SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }
    m_interfaceListener.OnResponseSetTargetLevel(status, obj->GetPath(), context);
}

void TargetTemperatureLevelIntfControllerImpl::GetSelectableTemperatureLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    TemperatureLevels levels;
    for (size_t i = 0; i < numVals; ++i)
        levels.push_back(vals[i]);
    m_interfaceListener.OnResponseGetSelectableTemperatureLevels(status, obj->GetPath(), levels, context);
}

} //namespace services
} //namespace ajn
