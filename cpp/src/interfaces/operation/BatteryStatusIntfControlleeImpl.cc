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
#include <alljoyn/hae/interfaces/operation/BatteryStatusIntfControlleeListener.h>

#include "BatteryStatusIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* BatteryStatusIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new BatteryStatusIntfControlleeImpl(busAttachment, dynamic_cast<BatteryStatusIntfControlleeListener&>(listener), haeBusObject);
}

BatteryStatusIntfControlleeImpl::BatteryStatusIntfControlleeImpl(BusAttachment& busAttachment, BatteryStatusIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_currentValue(MAX_BATTERY),
    m_isCharging(false)
{
}

BatteryStatusIntfControlleeImpl::~BatteryStatusIntfControlleeImpl()
{
}

QStatus BatteryStatusIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();
    /**
     * TODO: add method handler
     */
    return status;
}

QStatus BatteryStatusIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_CurrentValue.compare(propName))) {
                uint8_t currentValue = 0;
                status = m_interfaceListener.OnGetCurrentValue(currentValue);
                if (status != ER_OK) {
                    currentValue = GetCurrentValue();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCurrentValue(currentValue);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = currentValue;
            } else if (!(s_prop_IsCharging.compare(propName))) {
                bool isCharging = false;
                status = m_interfaceListener.OnGetIsCharging(isCharging);
                if (status != ER_OK) {
                    isCharging = GetIsCharging();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetIsCharging(isCharging);
                }
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = isCharging;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_CurrentValue.compare(propName))) {
                const uint8_t currentValue = GetCurrentValue();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = currentValue;
            } else if (!(s_prop_IsCharging.compare(propName))) {
                const bool isCharging = GetIsCharging();
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = isCharging;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        }
    }

    return status;
}

QStatus BatteryStatusIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    /*
     * TODO: implement SetProperty
     */

    return status;
}

void BatteryStatusIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

QStatus BatteryStatusIntfControlleeImpl::SetCurrentValue(const uint8_t value)
{
    if (MIN_BATTERY > value || MAX_BATTERY < value) {
        QCC_LogError(ER_INVALID_DATA, ("%s: value is invalid.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_currentValue != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentValue.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_currentValue = value;
    }
    return ER_OK;
}

QStatus BatteryStatusIntfControlleeImpl::SetIsCharging(const bool isCharging)
{
    if (m_isCharging != isCharging) {
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = isCharging;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_IsCharging.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_isCharging = isCharging;
    }
    return ER_OK;
}

} //namespace services
} //namespace ajn
