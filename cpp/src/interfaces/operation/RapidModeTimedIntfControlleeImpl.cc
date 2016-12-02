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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControlleeListener.h>

#include "RapidModeTimedIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* RapidModeTimedIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new RapidModeTimedIntfControlleeImpl(busAttachment, dynamic_cast<RapidModeTimedIntfControlleeListener&>(listener), cdmBusObject);
}

RapidModeTimedIntfControlleeImpl::RapidModeTimedIntfControlleeImpl(BusAttachment& busAttachment, RapidModeTimedIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_rapidModeMinutesRemaining(0),
    m_maxSetMinutes(60),
    m_maxSetMinutesInit(false)
{
}

RapidModeTimedIntfControlleeImpl::~RapidModeTimedIntfControlleeImpl()
{
}

QStatus RapidModeTimedIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus RapidModeTimedIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_RapidModeMinutesRemaining.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetRapidModeMinutesRemaining(value);
                if (status != ER_OK) {
                    value = GetRapidModeMinutesRemaining();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetRapidModeMinutesRemaining(value);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_MaxSetMinutes.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetMaxSetMinutes(value);
                if (status != ER_OK) {
                    value = GetMaxSetMinutes();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxSetMinutes(value);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_RapidModeMinutesRemaining.compare(propName))) {
                const uint16_t value = GetRapidModeMinutesRemaining();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_MaxSetMinutes.compare(propName))) {
                const uint16_t value = GetMaxSetMinutes();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus RapidModeTimedIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_RapidModeMinutesRemaining.compare(propName))) {
        if (val.typeId != ALLJOYN_UINT16) {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        uint16_t value = val.v_uint16;
        if (!IsRapidModeMinutesRemainingValid(value)) {
            // return ErrorMsg org.alljoyn.Error.InvalidValue
            QCC_LogError(ER_BUS_PROPERTY_VALUE_NOT_SET, ("%s: value is invalid", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        status = m_interfaceListener.OnSetRapidModeMinutesRemaining(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetRapidModeMinutesRemaining(value);
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void RapidModeTimedIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus RapidModeTimedIntfControlleeImpl::SetRapidModeMinutesRemaining(const uint16_t value)
{
    if (!IsRapidModeMinutesRemainingValid(value)) {
        QCC_LogError(ER_INVALID_DATA, ("%s: Out of range.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_rapidModeMinutesRemaining != value) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_RapidModeMinutesRemaining.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_rapidModeMinutesRemaining = value;
    }
    return ER_OK;
}

QStatus RapidModeTimedIntfControlleeImpl::SetMaxSetMinutes(const uint16_t value)
{
    if (m_maxSetMinutesInit) {
        QCC_LogError(ER_FAIL, ("%s: MaxSetMinutes is constant.", __func__));
        return ER_FAIL;
    }

    m_maxSetMinutes = value;
    m_maxSetMinutesInit = true;
    return ER_OK;
}

bool RapidModeTimedIntfControlleeImpl::IsRapidModeMinutesRemainingValid(uint16_t value)
{
    if (value > m_maxSetMinutes) {
        return false;
    }

    return true;
}

} //namespace services
} //namespace ajn
