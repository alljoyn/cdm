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

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeBusObject.h>
#include <alljoyn/hae/interfaces/operation/EnergyUsageIntfControlleeListener.h>

#include "EnergyUsageIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* EnergyUsageIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new EnergyUsageIntfControlleeImpl(busAttachment, dynamic_cast<EnergyUsageIntfControlleeListener&>(listener), haeBusObject);
}

EnergyUsageIntfControlleeImpl::EnergyUsageIntfControlleeImpl(BusAttachment& busAttachment, EnergyUsageIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_cumulativeEnergy(0.0),
    m_precision(0.0),
    m_updateMinTime(0)
{
}

EnergyUsageIntfControlleeImpl::~EnergyUsageIntfControlleeImpl()
{
}

QStatus EnergyUsageIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();
    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_ResetCumulativeEnergy.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&EnergyUsageIntfControlleeImpl::OnResetCumulativeEnergy);

    m_methodHandlers.push_back(make_pair(member, methodHandler));
    return status;
}

QStatus EnergyUsageIntfControlleeImpl::OnGetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_CumulativeEnergy.compare(propName))) {
                double cumulativeEnergy;
                status = m_interfaceListener.OnGetCumulativeEnergy(cumulativeEnergy);
                if (status != ER_OK) {
                    cumulativeEnergy = GetCumulativeEnergy();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCumulativeEnergy(cumulativeEnergy);
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = cumulativeEnergy;
            } else if (!(s_prop_Precision.compare(propName))) {
                double precision;
                status = m_interfaceListener.OnGetPrecision(precision);
                if (status != ER_OK) {
                    precision = GetPrecision();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetPrecision(precision);
                }

                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = precision;
            } else if (!(s_prop_UpdateMinTime.compare(propName))) {
                uint16_t updateMinTime;
                status = m_interfaceListener.OnGetUpdateMinTime(updateMinTime);
                if (status != ER_OK) {
                    updateMinTime = GetUpdateMinTime();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetUpdateMinTime(updateMinTime);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = updateMinTime;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_CumulativeEnergy.compare(propName))) {
                const double cumulativeEnergy = GetCumulativeEnergy();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = cumulativeEnergy;
            } else if (!(s_prop_Precision.compare(propName))) {
                const double precision = GetPrecision();
                val.typeId = ALLJOYN_DOUBLE;
                val.v_double = precision;
            } else if (!(s_prop_UpdateMinTime.compare(propName))) {
                const uint16_t updateMinTime = GetUpdateMinTime();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = updateMinTime;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus EnergyUsageIntfControlleeImpl::OnSetProperty(const String propName, MsgArg& val)
{
    return ER_BUS_NO_SUCH_PROPERTY;
}

void EnergyUsageIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
            break;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not found method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

QStatus EnergyUsageIntfControlleeImpl::SetCumulativeEnergy(const double cumulativeEnergy)
{
    if (m_cumulativeEnergy != cumulativeEnergy) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = cumulativeEnergy;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CumulativeEnergy.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_cumulativeEnergy = cumulativeEnergy;
    }
    return ER_OK;
}

QStatus EnergyUsageIntfControlleeImpl::SetPrecision(const double precision)
{
    if (m_precision != precision) {
        MsgArg val;
        val.typeId = ALLJOYN_DOUBLE;
        val.v_double = precision;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_Precision.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_precision = precision;
    }
    return ER_OK;
}

QStatus EnergyUsageIntfControlleeImpl::SetUpdateMinTime(const uint16_t updateMinTime)
{
    if (m_updateMinTime != updateMinTime) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = updateMinTime;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_UpdateMinTime.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_updateMinTime = updateMinTime;
    }
    return ER_OK;
}

void EnergyUsageIntfControlleeImpl::OnResetCumulativeEnergy(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 0) {
        ErrorCode errorCode = NOT_ERROR;

        status = m_interfaceListener.OnResetCumulativeEnergy(errorCode);
        if (status == ER_OK) {
            SetCumulativeEnergy(0.0);
            status = m_busObject.ReplyMethodCall(msg, status);
        } else {
            if (errorCode == NOT_ERROR) {
                QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                m_busObject.ReplyMethodCall(msg, status);
            } else {
                m_busObject.ReplyMethodCall(msg, HaeInterface::GetInterfaceErrorName(errorCode).c_str(),
                                            HaeInterface::GetInterfaceErrorMessage(errorCode).c_str());
            }
        }
    } else {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}

} //namespace services
} //namespace ajn
