/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "VendorDefinedIntfControlleeListener.h"
#include "VendorDefinedIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* VendorDefinedIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new VendorDefinedIntfControlleeImpl(busAttachment, dynamic_cast<VendorDefinedIntfControlleeListener&>(listener), cdmBusObject);
}

VendorDefinedIntfControlleeImpl::VendorDefinedIntfControlleeImpl(BusAttachment& busAttachment, VendorDefinedIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_testProperty(100)
{
}

VendorDefinedIntfControlleeImpl::~VendorDefinedIntfControlleeImpl()
{
}

QStatus VendorDefinedIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_TestMethod.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&VendorDefinedIntfControlleeImpl::OnTestMethod);

    m_methodHandlers.push_back(make_pair(member, methodHandler));

    return status;
}

QStatus VendorDefinedIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            /*
             * TODO: implement the GetProperty using VendorDefinedIntfControlleeListener
             */
            if (!(s_prop_TestProperty.compare(propName))) {
                int property;
                status = m_interfaceListener.OnGetTestProperty(property);
                if (status != ER_OK) {
                    property = GetTestProperty();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetTestProperty(property);
                }

                val.typeId = ALLJOYN_INT32;
                val.v_int32 = property;
            }
        } else {
            /*
             * TODO: implement the GetProperty using current property value
             */
            if (!(s_prop_TestProperty.compare(propName))) {
                int property = GetTestProperty();
                val.typeId = ALLJOYN_INT32;
                val.v_int32 = property;
            }
       }
    }

    return status;
}

QStatus VendorDefinedIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    /*
     * TODO: implement SetProperty
     */
    if (!(s_prop_TestProperty.compare(propName))) {
        if (val.typeId != ALLJOYN_INT32) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        int property = val.v_int32;
        status = m_interfaceListener.OnSetTestProperty(property);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetTestProperty(property);
        }
    }
    return status;
}

void VendorDefinedIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus VendorDefinedIntfControlleeImpl::SetTestProperty(int property)
{
    if (m_testProperty != property) {
        MsgArg val;
        val.typeId = ALLJOYN_INT32;
        val.v_int32 = property;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_TestProperty.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_testProperty = property;
    }
    return ER_OK;
}

QStatus VendorDefinedIntfControlleeImpl::EmitTestSignal()
{
    const InterfaceDescription::Member* member = GetInterfaceDescription()->GetMember(s_signal_TestSignal.c_str());
    assert(member);
    return m_busObject.Signal(NULL, SESSION_ID_ALL_HOSTED, *member, NULL, 0, 0);
}

void VendorDefinedIntfControlleeImpl::OnTestMethod(const InterfaceDescription::Member* member, Message& msg)
{
    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1) {
        int32_t arg1 = 0;
        args->Get("i", &arg1);

        qcc::String errorName, errorMessage;
        QStatus status = m_interfaceListener.OnTestMethod(arg1, errorName, errorMessage);

        if (status == ER_OK) {
            status = m_busObject.ReplyMethodCall(msg, status);
        }
        else {
            if (errorName.empty()) {
                QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                m_busObject.ReplyMethodCall(msg, status);
            } else {
                m_busObject.ReplyMethodCall(msg, errorName.c_str(), errorMessage.c_str());
            }
        }
    }
    else {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}

} //namespace services
} //namespace ajn