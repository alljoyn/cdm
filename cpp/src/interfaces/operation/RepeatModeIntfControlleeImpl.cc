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
#include <alljoyn/hae/interfaces/operation/RepeatModeIntfControlleeListener.h>

#include "RepeatModeIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* RepeatModeIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new RepeatModeIntfControlleeImpl(busAttachment, dynamic_cast<RepeatModeIntfControlleeListener&>(listener), haeBusObject);
}

RepeatModeIntfControlleeImpl::RepeatModeIntfControlleeImpl(BusAttachment& busAttachment, RepeatModeIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

RepeatModeIntfControlleeImpl::~RepeatModeIntfControlleeImpl()
{
}

QStatus RepeatModeIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();
    /**
     * TODO: add method handler
     */
    return status;
}

QStatus RepeatModeIntfControlleeImpl::OnGetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (!(s_prop_RepeatMode.compare(propName))) {
            bool repeatMode;
            if (s_retrievingActualPropertyValue) {
                status = m_interfaceListener.OnGetRepeatMode(repeatMode);
                if (status != ER_OK) {
                    repeatMode = GetRepeatMode();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetRepeatMode(repeatMode); // update the value in RepeatModeIntfControllee.
                }
            } else {
                repeatMode = GetRepeatMode();
            }

            val.typeId = ALLJOYN_BOOLEAN;
            val.v_bool = repeatMode;
        }
    }

    return status;
}

QStatus RepeatModeIntfControlleeImpl::OnSetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_RepeatMode.compare(propName))) {
        if (val.typeId != ALLJOYN_BOOLEAN) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        bool repeatMode = val.v_bool;
        status = m_interfaceListener.OnSetRepeatMode(repeatMode);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetRepeatMode(repeatMode); // update the value in RepeatModeIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }
    return status;
}

void RepeatModeIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus RepeatModeIntfControlleeImpl::SetRepeatMode(const bool value)
{
    QStatus status = ER_OK;

    if (m_RepeatMode != value) {
        m_RepeatMode = value;
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_RepeatMode.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }
    return status;
}

} //namespace services
} //namespace ajn
