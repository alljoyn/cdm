/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfControllerListener.h>

#include "AlertsIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* AlertsIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new AlertsIntfControllerImpl(busAttachment, dynamic_cast<AlertsIntfControllerListener&>(listener), cdmProxyObject);
}

AlertsIntfControllerImpl::AlertsIntfControllerImpl(BusAttachment& busAttachment, AlertsIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

AlertsIntfControllerImpl::~AlertsIntfControllerImpl()
{
}

QStatus AlertsIntfControllerImpl::Init()
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

QStatus AlertsIntfControllerImpl::GetAlerts(void * context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_Alerts.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&AlertsIntfControllerImpl::GetAlertsPropertyCB,context);

    return status;
}

QStatus AlertsIntfControllerImpl::GetAlertCodesDescription(const qcc::String& language, void* context)
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].typeId = ALLJOYN_STRING;
    args[0].v_string.str = language.c_str();
    args[0].v_string.len = language.size();

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_GetAlertCodesDescription.c_str(), this, (MessageReceiver::ReplyHandler)&AlertsIntfControllerImpl::GetAlertCodesDescriptionReplyHandler, args, 1, context);

    return status;
}

QStatus AlertsIntfControllerImpl::AcknowledgeAlert(const uint16_t alertCode, void * context)
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].typeId = ALLJOYN_UINT16;
    args[0].v_uint16 = alertCode;

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_AcknowledgeAlert.c_str(), this, (MessageReceiver::ReplyHandler)&AlertsIntfControllerImpl::AcknowledgeAlertReplyHandler, args, 1, context);

    return status;
}

QStatus AlertsIntfControllerImpl::AcknowledgeAllAlerts(void * context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_AcknowledgeAllAlerts.c_str(), this, (MessageReceiver::ReplyHandler)&AlertsIntfControllerImpl::AcknowledgeAllAlertsReplyHandler, NULL, 0, context);

    return status;
}

void AlertsIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;
    AlertsInterface::Alerts alerts;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_Alerts.compare(propNameStr)) {
            if (!propValue[0].HasSignature("a(yqb)"))
            {
                return;
            }

            MsgArg* alertEntries;
            size_t numAlertEntries;

            AlertsInterface::AlertRecord alertRecord;
            propValue[0].Get("a(yqb)", &numAlertEntries, &alertEntries);
            for (size_t i = 0; i < numAlertEntries; ++i)
            {
                uint8_t severity;
                uint16_t alertCode;
                bool acknowledgeNeeded;

                alertEntries[i].Get("(yqb)", &severity, &alertCode, &acknowledgeNeeded);
                alertRecord.severity = (Severity)severity;
                alertRecord.alertCode = alertCode;
                alertRecord.needAcknowledgement = acknowledgeNeeded;
                alerts.push_back(alertRecord);
            }
            m_interfaceListener.OnAlertsChanged(obj.GetPath(), alerts);
        }
    }
}

void AlertsIntfControllerImpl::GetAlertsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    MsgArg* entries;
    size_t numEntries;
    AlertsInterface::Alerts alerts;

    AlertsInterface::AlertRecord alertRecord;
    value.Get("a(yqb)", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i)
    {
        uint8_t severity;
        uint16_t alertCode;
        bool acknowledgeNeeded;

        entries[i].Get("(yqb)", &severity, &alertCode, &acknowledgeNeeded);
        alertRecord.severity = (Severity)severity;
        alertRecord.alertCode = alertCode;
        alertRecord.needAcknowledgement = acknowledgeNeeded;
        alerts.push_back(alertRecord);
    }

    m_interfaceListener.OnResponseGetAlerts(status, obj->GetPath(), alerts, context);
}
void AlertsIntfControllerImpl::GetAlertCodesDescriptionReplyHandler(Message& message, void* context)
{
    cout << "AlertsIntfControllerImpl::GetAlertCodesDescriptionReplyHandler" << endl;
    AlertsInterface::AlertCodesDescriptors descriptions;
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }
    else
    {
        size_t numArgs;
        const MsgArg* args;
        message->GetArgs(numArgs, args);

        if (!args[0].HasSignature("a(qs)"))
        {
            return;
        }

        MsgArg* entries;
        size_t numEntries;
        AlertsInterface::AlertCodesDescriptor desc;

        args[0].Get("a(qs)", &numEntries, &entries);
        for (size_t i = 0; i < numEntries; ++i)
        {
            const char* codeDesc;
            uint16_t alertCode;
            entries[i].Get("(qs)", &alertCode, &codeDesc);
            desc.alertCode = alertCode;
            desc.description = String(codeDesc);
            descriptions.push_back(desc);
        }
    }
    m_interfaceListener.OnResponseGetAlertCodesDescription(status, m_proxyObject.GetPath(), descriptions, context, errorName, errorMessage.c_str());
}
void AlertsIntfControllerImpl::AcknowledgeAlertReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }

    m_interfaceListener.OnResponseAcknowledgeAlert(status, m_proxyObject.GetPath(), context, errorName, errorMessage.c_str());
}
void AlertsIntfControllerImpl::AcknowledgeAllAlertsReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }

    m_interfaceListener.OnResponseAcknowledgeAllAlerts(status, m_proxyObject.GetPath(), context, errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn