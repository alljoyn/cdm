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
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "MoistureOutputLevelIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {


CdmInterface* MoistureOutputLevelIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new MoistureOutputLevelIntfControlleeImpl(busAttachment, static_cast<MoistureOutputLevelIntfControlleeListener&>(listener), cdmBusObject);
}

MoistureOutputLevelIntfControlleeImpl::MoistureOutputLevelIntfControlleeImpl(BusAttachment& busAttachment, MoistureOutputLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_moistureOutputLevel(0),
    m_maxMoistureOutputLevel(10),
    m_autoMode(0)
{
}

MoistureOutputLevelIntfControlleeImpl::~MoistureOutputLevelIntfControlleeImpl()
{
}

QStatus MoistureOutputLevelIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus MoistureOutputLevelIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_MoistureOutputLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMoistureOutputLevel(value);
                if (status != ER_OK) {
                    value = GetMoistureOutputLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMoistureOutputLevel(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxMoistureOutputLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMaxMoistureOutputLevel(value);
                if (status != ER_OK) {
                    value = GetMaxMoistureOutputLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxMoistureOutputLevel(value);
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
                    SetAutoMode(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_MoistureOutputLevel.compare(propName))) {
                const uint8_t value = GetMoistureOutputLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxMoistureOutputLevel.compare(propName))) {
                const uint8_t value = GetMaxMoistureOutputLevel();
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

QStatus MoistureOutputLevelIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_MoistureOutputLevel.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        uint8_t value = val.v_byte;
        if (!IsMoistureOutputLevelValid(value)) {
            // return ErrorMsg org.alljoyn.Error.InvalidValue
            QCC_LogError(ER_BUS_PROPERTY_VALUE_NOT_SET, ("%s: value is invalid", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        status = m_interfaceListener.OnSetMoistureOutputLevel(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetMoistureOutputLevel(value);
        }
    } else if (!(s_prop_AutoMode.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        if (m_autoMode == 0xFF) {
            // return ErrorMsg org.alljoyn.Error.FeatureNotAvailable
            QCC_LogError(ER_BUS_SET_PROPERTY_REJECTED, ("%s: HorizontalAutoMode is not supported", __func__));
            return ER_BUS_SET_PROPERTY_REJECTED;
        }

        uint8_t value = val.v_byte;
        if (value == 0xFF) {      // The controller shall not set 0xFF(not supported)
            QCC_LogError(ER_INVALID_DATA, ("%s: Setting HorizontalAutoMode for 0xFF is rejected", __func__));
            return ER_INVALID_DATA;
        }

        if (!IsAutoModeValid(value)) {
            // return ErrorMsg org.alljoyn.Error.InvalidValue
            QCC_LogError(ER_BUS_PROPERTY_VALUE_NOT_SET, ("%s: value is invalid", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        status = m_interfaceListener.OnSetAutoMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetAutoMode(value);
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void MoistureOutputLevelIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{
    QStatus status = ER_OK;
    bool isFound = false;
    MethodHandlers::const_iterator it;
    for (it = m_methodHandlers.begin(); it != m_methodHandlers.end(); ++it) {
        if (it->first == member) {
            MessageReceiver::MethodHandler handler = it->second;
            (this->*handler)(member, msg);
            isFound = true;
        }
    }

    if (!isFound) {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}


QStatus MoistureOutputLevelIntfControlleeImpl::SetMoistureOutputLevel(const uint8_t value)
{
    if (!IsMoistureOutputLevelValid(value)) {
        QCC_LogError(ER_FAIL, ("%s: MoistureOutputLevel is out of range. ", __func__));
        return ER_FAIL;
    }

    if (m_maxMoistureOutputLevel != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MoistureOutputLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_moistureOutputLevel = value;
    }

    return ER_OK;
}

QStatus MoistureOutputLevelIntfControlleeImpl::SetMaxMoistureOutputLevel(const uint8_t value)
{
    if (m_maxMoistureOutputLevel != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxMoistureOutputLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_maxMoistureOutputLevel = value;
    }

    return ER_OK;
}

QStatus MoistureOutputLevelIntfControlleeImpl::SetAutoMode(const uint8_t autoMode)
{
    if (!IsAutoModeValid(autoMode)) {
        QCC_LogError(ER_FAIL, ("%s: value is not valid. ", __func__));
        return ER_FAIL;
    }

    if (m_autoMode != autoMode) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = autoMode;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_AutoMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_autoMode = autoMode;
    }

    return ER_OK;
}

bool MoistureOutputLevelIntfControlleeImpl::IsMoistureOutputLevelValid(uint8_t value)
{
    if (value > m_maxMoistureOutputLevel) {
        return false;
    }

    return true;
}

bool MoistureOutputLevelIntfControlleeImpl::IsAutoModeValid(uint8_t autoMode)
{
    if (m_autoMode == 0xFF) {
        return false;
    }

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
