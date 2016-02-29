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
#include <alljoyn/hae/interfaces/environment/WindDirectionIntfControlleeListener.h>
#include <alljoyn/hae/HaeBusObject.h>
#include "WindDirectionIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {


HaeInterface* WindDirectionIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new WindDirectionIntfControlleeImpl(busAttachment, static_cast<WindDirectionIntfControlleeListener&>(listener), haeBusObject);
}

WindDirectionIntfControlleeImpl::WindDirectionIntfControlleeImpl(BusAttachment& busAttachment, WindDirectionIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_HorizontalDirection(0),
    m_HorizontalMax(10),
    m_HorizontalAutoMode(0),
    m_VerticalDirection(0),
    m_VerticalMax(10),
    m_VerticalAutoMode(0)
{
}

WindDirectionIntfControlleeImpl::~WindDirectionIntfControlleeImpl()
{
}

QStatus WindDirectionIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();

    return status;
}

QStatus WindDirectionIntfControlleeImpl::OnGetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;


    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_HorizontalDirection.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetHorizontalDirection(value);
                if (status != ER_OK) {
                    value = GetHorizontalDirection();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetHorizontalDirection(value); // update WindDirection in WindDirectionIntfControllee.
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_HorizontalMax.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetHorizontalMax(value);
                if (status != ER_OK) {
                    value = GetHorizontalMax();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetHorizontalMax(value); // update MaxDirection in WindDirectionIntfControllee.
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_HorizontalAutoMode.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetHorizontalAutoMode(value);
                if (status != ER_OK) {
                    value = GetHorizontalAutoMode();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetHorizontalAutoMode(value); // update AutoMode in WindDirectionIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_VerticalDirection.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetVerticalDirection(value);
                if (status != ER_OK) {
                    value = GetVerticalDirection();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetVerticalDirection(value); // update WindDirection in WindDirectionIntfControllee.
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_VerticalMax.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetVerticalMax(value);
                if (status != ER_OK) {
                    value = GetVerticalMax();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetVerticalMax(value); // update MaxDirection in WindDirectionIntfControllee.
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_VerticalAutoMode.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetVerticalAutoMode(value);
                if (status != ER_OK) {
                    value = GetVerticalAutoMode();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetVerticalAutoMode(value); // update AutoMode in WindDirectionIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }

        } else {
            if (!(s_prop_HorizontalDirection.compare(propName))) {
                const uint16_t value = GetHorizontalDirection();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_HorizontalMax.compare(propName))) {
                const uint16_t value = GetHorizontalMax();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_HorizontalAutoMode.compare(propName))) {
                const uint8_t value = GetHorizontalAutoMode();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_VerticalDirection.compare(propName))) {
                const uint16_t value = GetVerticalDirection();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_VerticalMax.compare(propName))) {
                const uint16_t value = GetVerticalMax();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_VerticalAutoMode.compare(propName))) {
                const uint8_t value = GetVerticalAutoMode();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus WindDirectionIntfControlleeImpl::OnSetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_HorizontalDirection.compare(propName))) {
        if (val.typeId != ALLJOYN_UINT16) {
            return ER_BUS_NO_SUCH_PROPERTY;
        }

        if (m_HorizontalMax == 0) {
            // return ErrorMsg org.alljoyn.Error.FeatureNotAvailable
            QCC_LogError(ER_BUS_SET_PROPERTY_REJECTED, ("%s: HorizontalDirection feature is not available", __func__));
            return ER_BUS_SET_PROPERTY_REJECTED;
        }

        uint16_t value = adjustHorizontalDirection(val.v_uint16);
        status = m_interfaceListener.OnSetHorizontalDirection(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetHorizontalDirection(value); // update the value in WindDirectionIntfControllee.
        }
    } else if (!(s_prop_HorizontalAutoMode.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        if (m_HorizontalAutoMode == 0xFF) {
            // return ErrorMsg org.alljoyn.Error.FeatureNotAvailable
            QCC_LogError(ER_BUS_SET_PROPERTY_REJECTED, ("%s: HorizontalAutoMode is not supported", __func__));
            return ER_BUS_SET_PROPERTY_REJECTED;
        }

        uint8_t value = val.v_byte;
        if (value == 0xFF) {      // The controller shall not set 0xFF(not supported)
            QCC_LogError(ER_INVALID_DATA, ("%s: Setting HorizontalAutoMode for 0xFF is rejected", __func__));
            return ER_INVALID_DATA;
        }

        if (!isHorizontalAutoModeValid(value)) {
            // return ErrorMsg org.alljoyn.Error.InvalidValue
            QCC_LogError(ER_BUS_PROPERTY_VALUE_NOT_SET, ("%s: value is invalid", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        status = m_interfaceListener.OnSetHorizontalAutoMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetHorizontalAutoMode(value); // update the value in WindDirectionIntfControllee.
        }

    } else if (!(s_prop_VerticalDirection.compare(propName))) {
        if (val.typeId != ALLJOYN_UINT16) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }

        if (m_VerticalMax == 0) {
            // return ErrorMsg org.alljoyn.Error.FeatureNotAvailable
            QCC_LogError(ER_BUS_SET_PROPERTY_REJECTED, ("%s: VerticalDirection feature is not available", __func__));
            return ER_BUS_SET_PROPERTY_REJECTED;
        }

        uint16_t value = val.v_uint16;
        status = m_interfaceListener.OnSetVerticalDirection(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetVerticalDirection(value); // update the value in WindDirectionIntfControllee.
        }
    } else if (!(s_prop_VerticalAutoMode.compare(propName))) {
        if (val.typeId != ALLJOYN_BYTE) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }

        if (m_VerticalAutoMode == 0xFF) {
            // return ErrorMsg org.alljoyn.Error.FeatureNotAvailable
            QCC_LogError(ER_BUS_SET_PROPERTY_REJECTED, ("%s: VerticalAutoMode is not supported", __func__));
            return ER_BUS_SET_PROPERTY_REJECTED;
        }

        uint8_t value = val.v_byte;
        if (value == 0xFF) {      // The controller shall not set 0xFF(not supported)
            QCC_LogError(ER_INVALID_DATA, ("%s: Setting VerticalAutoMode for 0xFF is rejected", __func__));
            return ER_INVALID_DATA;
        }

        if (!isVerticalAutoModeValid(value)) {
            // return ErrorMsg org.alljoyn.Error.InvalidValue
            QCC_LogError(ER_BUS_PROPERTY_VALUE_NOT_SET, ("%s: value is invalid", __func__));
            return ER_BUS_PROPERTY_VALUE_NOT_SET;
        }

        status = m_interfaceListener.OnSetVerticalAutoMode(value);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetVerticalAutoMode(value); // update the value in WindDirectionIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void WindDirectionIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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
        QCC_LogError(status, ("%s: could not found method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}


QStatus WindDirectionIntfControlleeImpl::SetHorizontalDirection(const uint16_t value)
{
    if (m_HorizontalMax == 0) {
        QCC_LogError(ER_FAIL, ("%s: Setting horizontal wind direction is not supported. ", __func__));
        return ER_FAIL;
    }

    if ( value < 0 || value > this->m_HorizontalMax ) {
        QCC_LogError(ER_FAIL, ("%s: HorizontalDirection is out of range. ", __func__));
        return ER_FAIL;
    }

    if (m_HorizontalDirection != value) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_HorizontalDirection.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_HorizontalDirection = value;
    }

    return ER_OK;
}

QStatus WindDirectionIntfControlleeImpl::SetHorizontalMax(const uint16_t value)
{
    if (m_HorizontalMax != value) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_HorizontalMax.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_HorizontalMax = value;
    }

    return ER_OK;
}

QStatus WindDirectionIntfControlleeImpl::SetHorizontalAutoMode(const uint8_t value)
{
    if (!isHorizontalAutoModeValid(value)) {
        QCC_LogError(ER_FAIL, ("%s: value is not valid. ", __func__));
        return ER_FAIL;
    }

    if (m_HorizontalAutoMode != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_HorizontalAutoMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_HorizontalAutoMode = value;
    }

    return ER_OK;
}


QStatus WindDirectionIntfControlleeImpl::SetVerticalDirection(const uint16_t value)
{
    if (m_VerticalMax == 0) {
        QCC_LogError(ER_FAIL, ("%s: Setting horizontal wind direction is not supported. ", __func__));
        return ER_FAIL;
    }

    if ( value < 0 || value > this->m_VerticalMax ) {
        QCC_LogError(ER_FAIL, ("%s: VerticalDirection is out of range. ", __func__));
        return ER_FAIL;
    }

    if (m_VerticalDirection != value) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_VerticalDirection.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_VerticalDirection = value;
    }

    return ER_OK;
}

QStatus WindDirectionIntfControlleeImpl::SetVerticalMax(const uint16_t value)
{
    if (m_VerticalMax != value) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_VerticalMax.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_VerticalMax = value;
    }

    return ER_OK;
}

QStatus WindDirectionIntfControlleeImpl::SetVerticalAutoMode(const uint8_t value)
{
    if (!isVerticalAutoModeValid(value)) {
        QCC_LogError(ER_FAIL, ("%s: value is not valid. ", __func__));
        return ER_FAIL;
    }

    if (m_VerticalAutoMode != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_VerticalAutoMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_VerticalAutoMode = value;
    }

    return ER_OK;
}

uint16_t WindDirectionIntfControlleeImpl::adjustHorizontalDirection(uint16_t horizontalDirection)
{
    return horizontalDirection > m_HorizontalMax ? m_HorizontalMax : horizontalDirection;
}

bool WindDirectionIntfControlleeImpl::isHorizontalAutoModeValid(uint8_t horizontalAutoMode) {
    if (m_HorizontalAutoMode == 0xFF)
        return false;

    switch (horizontalAutoMode) {
    case 0x00:
    case 0x01:
    case 0xFF:
        return true;
    default:
        return false;
    }
}

uint16_t WindDirectionIntfControlleeImpl::adjustVerticalDirection(uint16_t verticalDirection)
{
    return verticalDirection > m_VerticalMax ? m_VerticalMax : verticalDirection;
}

bool WindDirectionIntfControlleeImpl::isVerticalAutoModeValid(uint8_t verticalAutoMode) {
    if (m_VerticalAutoMode == 0xFF)
        return false;

    switch (verticalAutoMode) {
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
