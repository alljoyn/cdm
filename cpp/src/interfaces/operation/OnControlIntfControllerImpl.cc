/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllerListener.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "OnControlIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* OnControlIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new OnControlIntfControllerImpl(busAttachment, dynamic_cast<OnControlIntfControllerListener&>(listener), cdmProxyObject);
}

OnControlIntfControllerImpl::OnControlIntfControllerImpl(BusAttachment& busAttachment, OnControlIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

OnControlIntfControllerImpl::~OnControlIntfControllerImpl()
{
}

QStatus OnControlIntfControllerImpl::Init()
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


QStatus OnControlIntfControllerImpl::SwitchOn(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_SwitchOn.c_str(), this, (MessageReceiver::ReplyHandler)&OnControlIntfControllerImpl::SwitchOnReplyHandler, NULL, 0, context);
    return status;

}

void OnControlIntfControllerImpl::SwitchOnReplyHandler(Message& message, void* context)
{
    qcc::String errorMsg;
    const char* errorName = message->GetErrorName(&errorMsg);
    QStatus status = (message->GetType() == MESSAGE_METHOD_RET) ? ER_OK : ER_FAIL;
    m_interfaceListener.OnResponseSwitchOn(status, m_proxyObject.GetPath(),
            context, errorName, errorMsg.c_str());
}

void OnControlIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    // This interface doesn't have any property.
}

} //namespace services
} //namespace ajn