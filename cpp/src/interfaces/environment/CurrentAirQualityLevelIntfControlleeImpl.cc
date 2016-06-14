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
#include <alljoyn/hae/interfaces/environment/CurrentAirQualityLevelIntfControlleeListener.h>

#include "CurrentAirQualityLevelIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* CurrentAirQualityLevelIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new CurrentAirQualityLevelIntfControlleeImpl(busAttachment, dynamic_cast<CurrentAirQualityLevelIntfControlleeListener&>(listener), haeBusObject);
}

CurrentAirQualityLevelIntfControlleeImpl::CurrentAirQualityLevelIntfControlleeImpl(BusAttachment& busAttachment, CurrentAirQualityLevelIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_contaminantType(CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH20),
    m_currentLevel(0),
    m_maxLevel(0)
{
}

CurrentAirQualityLevelIntfControlleeImpl::~CurrentAirQualityLevelIntfControlleeImpl()
{
}

QStatus CurrentAirQualityLevelIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();
    return status;
}

QStatus CurrentAirQualityLevelIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_ContaminantType.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetContaminantType(value);
                if (status != ER_OK) {
                    value = GetContaminantType();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetContaminantType(value);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_CurrentLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetCurrentLevel(value);
                if (status != ER_OK) {
                    value = GetCurrentLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCurrentLevel(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxLevel.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetMaxLevel(value);
                if (status != ER_OK) {
                    value = GetMaxLevel();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetMaxLevel(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_ContaminantType.compare(propName))) {
                uint8_t type = GetContaminantType();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = type;
            } else if (!(s_prop_CurrentLevel.compare(propName))) {
                uint8_t value = GetCurrentLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_MaxLevel.compare(propName))) {
                uint8_t value = GetMaxLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus CurrentAirQualityLevelIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void CurrentAirQualityLevelIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus CurrentAirQualityLevelIntfControlleeImpl::SetContaminantType(const uint8_t type)
{
    if (m_contaminantType != type) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = type;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ContaminantType.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_contaminantType = type;
    }

    return ER_OK;
}

QStatus CurrentAirQualityLevelIntfControlleeImpl::SetCurrentLevel(const uint8_t value)
{
    if (m_currentLevel != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_currentLevel = value;
    }

    return ER_OK;
}

QStatus CurrentAirQualityLevelIntfControlleeImpl::SetMaxLevel(const uint8_t value)
{
    if (m_maxLevel != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_maxLevel = value;
    }

    return ER_OK;
}

} //namespace services
} //namespace ajn
