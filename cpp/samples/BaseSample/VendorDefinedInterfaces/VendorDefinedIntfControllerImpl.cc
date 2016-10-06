/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "VendorDefinedIntfControllerListener.h"
#include "VendorDefinedIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* VendorDefinedIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new VendorDefinedIntfControllerImpl(busAttachment, dynamic_cast<VendorDefinedIntfControllerListener&>(listener), cdmProxyObject);
}

VendorDefinedIntfControllerImpl::VendorDefinedIntfControllerImpl(BusAttachment& busAttachment, VendorDefinedIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

VendorDefinedIntfControllerImpl::~VendorDefinedIntfControllerImpl()
{
}

QStatus VendorDefinedIntfControllerImpl::Init()
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

    const InterfaceDescription* intf = GetInterfaceDescription();
    if (intf) {
        const InterfaceDescription::Member* testSignal = intf->GetMember(s_signal_TestSignal.c_str());
        if (testSignal) {
            status = m_busAttachment.RegisterSignalHandler(this, static_cast<SignalHandler>(&VendorDefinedIntfControllerImpl::TestSignalCB), testSignal, NULL);
            if (ER_OK != status) {
                QCC_LogError(status, ("%s: RegisterPropertiesChangedListener failed.", __func__));
            }
        } else {
            status = ER_FAIL;
            QCC_LogError(status, ("%s: ChannelListChaned signal is not exist.", __func__));
        }
    } else {
        status = ER_FAIL;
        QCC_LogError(status, ("%s: The interface description is not exist.", __func__));
    }

    return status;
}

void VendorDefinedIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    /*
     * TODO: implements properties changed
     */
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_TestProperty.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_INT32) {
                uint32_t property = propValue->v_int32;
                m_interfaceListener.OnTestPropertyChanged(obj.GetPath(), property);
            }
        }
    }
}

QStatus VendorDefinedIntfControllerImpl::SetTestProperty(const int32_t property, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("i", property);
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_TestProperty.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&VendorDefinedIntfControllerImpl::SetTestPropertyCB, context);

    return status;
}

QStatus VendorDefinedIntfControllerImpl::GetTestProperty(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_TestProperty.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&VendorDefinedIntfControllerImpl::GetTestPropertyCB, context);

    return status;
}

void VendorDefinedIntfControllerImpl::SetTestPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if (!obj) {
        return;
    }

    m_interfaceListener.OnResponseSetTestProperty(status, obj->GetPath(), context);
}

void VendorDefinedIntfControllerImpl::GetTestPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    int32_t property;
    value.Get("i", &property);

    m_interfaceListener.OnResponseGetTestProperty(status, obj->GetPath(), property, context);
}

QStatus VendorDefinedIntfControllerImpl::TestMethod(int32_t arg1, void* context)
{
    QStatus status = ER_OK;

    MsgArg args;
    args.Set("i", arg1);
    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_TestMethod.c_str(),
            this,
            static_cast<MessageReceiver::ReplyHandler>(&VendorDefinedIntfControllerImpl::TestMethodCB),
            &args, 1, context);

    return status;
}

void VendorDefinedIntfControllerImpl::TestMethodCB(Message& msg, void* context)
{
    QStatus status = ER_OK;
    qcc::String errorMessage;
    const char* errorName = msg->GetErrorName(&errorMessage);
    if (msg->GetType() != MESSAGE_METHOD_RET) {
        status = ER_FAIL;
    }
    m_interfaceListener.OnResponseTestMethod(status, m_proxyObject.GetPath(), context,
            errorName, errorMessage.c_str());
}

void VendorDefinedIntfControllerImpl::TestSignalCB(const InterfaceDescription::Member* member, const char* srcPath, Message& message)
{
    String path = String(srcPath);
    m_interfaceListener.OnTestSignal(path);
}

} //namespace services
} //namespace ajn