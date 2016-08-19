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
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "FanSpeedLevelIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* FanSpeedLevelIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new FanSpeedLevelIntfControlleeImpl(busAttachment, dynamic_cast<FanSpeedLevelIntfControlleeListener&>(listener), cdmBusObject);
}

FanSpeedLevelIntfControlleeImpl::FanSpeedLevelIntfControlleeImpl(BusAttachment& busAttachment, FanSpeedLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_FanSpeedLevel(0),
    m_MaxFanSpeedLevel(10),
    m_AutoMode(0)
{
}

FanSpeedLevelIntfControlleeImpl::~FanSpeedLevelIntfControlleeImpl()
{
}

QStatus FanSpeedLevelIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus FanSpeedLevelIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {

            if (!(s_prop_FanSpeedLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetFanSpeedLevel(value);
                if (status != ER_OK) {
                    value = GetFanSpeedLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetFanSpeedLevel(value); // update the value in FanSpeedLevelIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxFanSpeedLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMaxFanSpeedLevel(value);
                if (status != ER_OK) {
                    value = GetMaxFanSpeedLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxFanSpeedLevel(value); // update the value in FanSpeedLevelIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_AutoMode.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetAutoMode(value);
                if (status != ER_OK) {
                    value = GetAutoMode();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetAutoMode(value); // update the value in FanSpeedLevelIntfControllee.
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_FanSpeedLevel.compare(propName))) {
                const uint8_t value = GetFanSpeedLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxFanSpeedLevel.compare(propName))) {
                const uint8_t value = GetMaxFanSpeedLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_AutoMode.compare(propName))) {
                const uint8_t value = GetAutoMode();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }
    return status;
}

QStatus FanSpeedLevelIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_FanSpeedLevel.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint8_t value = val.v_byte;
        if (value == FAN_TURNED_OFF) {
            QCC_LogError(ER_INVALID_DATA, ("%s: 0x00 can't be set.", __func__));
            return ER_INVALID_DATA;
        } else if (value > m_MaxFanSpeedLevel) {
            QCC_LogError(ER_INVALID_DATA, ("%s: Out of range.", __func__));
            return ER_INVALID_DATA;
        }
        status = m_interfaceListener.OnSetFanSpeedLevel(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetFanSpeedLevel(value); // update the value in FanSpeedLevelIntfControllee.
        }
    } else if (!(s_prop_AutoMode.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        if (m_AutoMode == 0xFF) {
            QCC_LogError(ER_INVALID_DATA, ("%s: Feature not available.", __func__));
            return ER_INVALID_DATA;
        }

        uint8_t value = val.v_byte;
        if (value == 0xFF) {
            QCC_LogError(ER_INVALID_DATA, ("%s: Not allowed to set AutoMode to 0xFF.", __func__));
            return ER_INVALID_DATA;
        } else if (!IsAutoModeValid(value)) {
            QCC_LogError(ER_INVALID_DATA, ("%s: Value is invalid.", __func__));
            return ER_INVALID_DATA;
        }
        status = m_interfaceListener.OnSetAutoMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetAutoMode(value); // update the value in FanSpeedLevelIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void FanSpeedLevelIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus FanSpeedLevelIntfControlleeImpl::SetFanSpeedLevel(const uint8_t value)
{
    if (value > m_MaxFanSpeedLevel) {
        QCC_LogError(ER_INVALID_DATA, ("%s: Out of range.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_FanSpeedLevel != value) {
        m_FanSpeedLevel = value;
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_FanSpeedLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return ER_OK;
}

QStatus FanSpeedLevelIntfControlleeImpl::SetMaxFanSpeedLevel(const uint8_t value)
{
    if (m_MaxFanSpeedLevel != value) {
        m_MaxFanSpeedLevel = value;
    }

    return ER_OK;
}

QStatus FanSpeedLevelIntfControlleeImpl::SetAutoMode(const uint8_t value)
{
    if (!IsAutoModeValid(value)) {
        QCC_LogError(ER_INVALID_DATA, ("%s: value is invalid.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_AutoMode != value) {
        m_AutoMode = value;
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_AutoMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }

    return ER_OK;
}

bool FanSpeedLevelIntfControlleeImpl::IsAutoModeValid(uint8_t autoMode)
{
    switch (autoMode) {
    case 0x00:
    case 0x01:
    case 0xFF:
        return true;
    default:
        return false;
    }
}

} //namespace services
} //namespace ajn
