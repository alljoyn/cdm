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
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllerListener.h>

#include "EnergyUsageIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* EnergyUsageIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new EnergyUsageIntfControllerImpl(busAttachment, dynamic_cast<EnergyUsageIntfControllerListener&>(listener), cdmProxyObject);
}

EnergyUsageIntfControllerImpl::EnergyUsageIntfControllerImpl(BusAttachment& busAttachment, EnergyUsageIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

EnergyUsageIntfControllerImpl::~EnergyUsageIntfControllerImpl()
{
}

QStatus EnergyUsageIntfControllerImpl::Init()
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

QStatus EnergyUsageIntfControllerImpl::GetCumulativeEnergy(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_CumulativeEnergy.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&EnergyUsageIntfControllerImpl::GetCumulativeEnergyPropertyCB, context);

    return status;
}

QStatus EnergyUsageIntfControllerImpl::GetPrecision(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_Precision.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&EnergyUsageIntfControllerImpl::GetPrecisionPropertyCB, context);

    return status;
}

QStatus EnergyUsageIntfControllerImpl::GetUpdateMinTime(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_UpdateMinTime.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&EnergyUsageIntfControllerImpl::GetUpdateMinTimePropertyCB, context);

    return status;
}

QStatus EnergyUsageIntfControllerImpl::ResetCumulativeEnergy(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_ResetCumulativeEnergy.c_str(), this, (MessageReceiver::ReplyHandler)&EnergyUsageIntfControllerImpl::ResetCumulativeEnergyReplyHandler, NULL, 0, context);

    return status;
}

void EnergyUsageIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_CumulativeEnergy.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double cumulativeEnergy = propValue->v_double;
                m_interfaceListener.OnCumulativeEnergyChanged(obj.GetPath(), cumulativeEnergy);
            }
        } else if (!s_prop_Precision.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_DOUBLE) {
                double precision = propValue->v_double;
                m_interfaceListener.OnPrecisionChanged(obj.GetPath(), precision);
            }
        } else if (!s_prop_UpdateMinTime.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_UINT16) {
                uint16_t updateMinTime = propValue->v_uint16;
                m_interfaceListener.OnUpdateMinTimeChanged(obj.GetPath(), updateMinTime);
            }
        }
    }
}

void EnergyUsageIntfControllerImpl::GetCumulativeEnergyPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    double cumulativeEnergy;
    value.Get("d", &cumulativeEnergy);

    m_interfaceListener.OnResponseGetCumulativeEnergy(status, obj->GetPath(), cumulativeEnergy, context);
}

void EnergyUsageIntfControllerImpl::GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    double precision;
    value.Get("d", &precision);

    m_interfaceListener.OnResponseGetPrecision(status, obj->GetPath(), precision, context);
}

void EnergyUsageIntfControllerImpl::GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint16_t updateMinTime;
    value.Get("q", &updateMinTime);

    m_interfaceListener.OnResponseGetUpdateMinTime(status, obj->GetPath(), updateMinTime, context);
}

void EnergyUsageIntfControllerImpl::ResetCumulativeEnergyReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET) {
        status = ER_FAIL;
    } else {
        size_t numArgs;
        const MsgArg* args;
        message->GetArgs(numArgs, args);

        if (numArgs != 0) {
            return;
        }
    }
    m_interfaceListener.OnResponseResetCumulativeEnergy(status, m_proxyObject.GetPath(), context,
                                                        errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn
