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
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "HvacFanModeIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* HvacFanModeIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new HvacFanModeIntfControllerImpl(busAttachment, static_cast<HvacFanModeIntfControllerListener&>(listener), cdmProxyObject);
}

HvacFanModeIntfControllerImpl::HvacFanModeIntfControllerImpl(BusAttachment& busAttachment, HvacFanModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

HvacFanModeIntfControllerImpl::~HvacFanModeIntfControllerImpl()
{
}

QStatus HvacFanModeIntfControllerImpl::Init()
{
    QStatus status = CdmInterface::Init();
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: Interface init failed.", __func__));
        return status;
    }

    status = m_proxyObject.RegisterPropertiesChangedListener(GetInterfaceName().c_str(), NULL, 0, *this, NULL);
    if (ER_OK != status) {
        QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
        return status;
    }

    return status;
}

QStatus HvacFanModeIntfControllerImpl::GetMode(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Mode.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&HvacFanModeIntfControllerImpl::GetModePropertyCB, context);
    if(status != ER_OK) {
        QCC_LogError(status, ("%s: GetMode failed.", __func__));
    }

    return status;

}


QStatus HvacFanModeIntfControllerImpl::SetMode(const Mode mode, void* context)
{
    QStatus status = ER_OK;
    MsgArg arg;
    arg.Set("q", mode);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_Mode.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&HvacFanModeIntfControllerImpl::SetModePropertyCB, context);
    if(status != ER_OK) {
        QCC_LogError(status, ("%s: SetMode failed.", __func__));
    }
    return status;
}

QStatus HvacFanModeIntfControllerImpl::GetSupportedModes(void* context)
{
    QStatus status = ER_OK;
    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedModes.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&HvacFanModeIntfControllerImpl::GetSupportedModesPropertyCB, context);
    return status;
}

void HvacFanModeIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_Mode.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t value = propValue->v_uint16;
                m_interfaceListener.OnModeChanged(obj.GetPath(), (Mode)value);
            }
        } else if (!s_prop_SupportedModes.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16_ARRAY) {
                std::vector<Mode> supportedmodes;
                uint16_t *vals;
                size_t numVals;
                propValue->Get("aq", &numVals, &vals);

                for(size_t j = 0 ; j<numVals ; j++  )
                {
                    cout << vals[j] << endl;
                    supportedmodes.push_back((Mode)vals[j]);
                }

                m_interfaceListener.OnSupportedModesChanged(obj.GetPath(), supportedmodes);
            }
        }
    }
}

void HvacFanModeIntfControllerImpl::SetModePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetMode(status, obj->GetPath(), context);
}

void HvacFanModeIntfControllerImpl::GetModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint16_t val;
    value.Get("q", &val);
    m_interfaceListener.OnResponseGetMode(status, obj->GetPath(), (Mode)val, context);
}

void HvacFanModeIntfControllerImpl::GetSupportedModesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        cout <<"obj null !!" << endl;
        return;
    }

    std::vector<Mode> supportedmodes;

    if (status == ER_OK) {
        uint16_t *vals;
        size_t numVals;
        value.Get("aq", &numVals, &vals);

        if ( numVals > 0 )
        {
            for(size_t j = 0 ; j<numVals ; j++  )
            {
                supportedmodes.push_back((Mode)vals[j]);
            }
        }
    }
    m_interfaceListener.OnResponseGetSupportedModes(status, obj->GetPath(), supportedmodes, context);
}

} //namespace services
} //namespace ajn
