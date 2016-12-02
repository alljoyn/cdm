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
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/{interface_category}/{interface_name}IntfControllerListener.h>

#include "{interface_name}IntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* {interface_name}IntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new {interface_name}IntfControllerImpl(busAttachment, dynamic_cast<{interface_name}IntfControllerListener&>(listener), cdmProxyObject);
}

{interface_name}IntfControllerImpl::{interface_name}IntfControllerImpl(BusAttachment& busAttachment, {interface_name}IntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

{interface_name}IntfControllerImpl::~{interface_name}IntfControllerImpl()
{
}

QStatus {interface_name}IntfControllerImpl::Init()
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

    /**
     * TODO: Register signal handler
     */

    return status;
}

void {interface_name}IntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    /*
     * TODO: implements properties changed
     */
}

/**
 * TODO: define functions to request the set/get properties
 * GetProperty function of read-only property must not be defined in the controller side.
 */

/*
 * TODO: define functions to request the method call
 */

/*
 * TODO: define callback fuctions that receive the response of SetProperty/GetProperty
 */

/*
 * TODO: define method reply handler
 */

/*
 * TODO: define signal handler
 */

} //namespace services
} //namespace ajn