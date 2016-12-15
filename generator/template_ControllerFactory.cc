/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <qcc/Debug.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/common/LogModule.h>

#include "interfaces/controller/ControllerFactory.h"

INCLUDE_MARKER

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {
//======================================================================

ControllerFactory& ControllerFactory::Instance()
{
    static ControllerFactory* s_instance = 0;

    if (!s_instance) {
        s_instance = new ControllerFactory();
    }

    return *s_instance;
}



ControllerFactory::ControllerFactory() :
    m_busAttachment(0)
{
CREATE_MARKER
}



QStatus ControllerFactory::InitControllerFactory(BusAttachment* busAttachment)
{
    if (!busAttachment) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: bus attachment is null.", __func__));
        return ER_BAD_ARG_1;
    }
    m_busAttachment = busAttachment;
    return ER_OK;
}



CreateIntfControllerFptr ControllerFactory::GetCreateIntfControllerFptr(const string& ifaceName)
{
    auto iter = m_controllerCreators.find(ifaceName);

    if (iter == m_controllerCreators.end()) {
        QCC_LogError(ER_FAIL, ("%s: could not find interface", __func__));
        return nullptr;
    }

    return iter->second;
}



Ref<CdmInterface> ControllerFactory::CreateIntfController(const string& ifaceName, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    QStatus status = ER_OK;

    if (!m_busAttachment) {
        QCC_LogError(ER_FAIL, ("%s: could not initialized controller", __func__));
        return nullptr;
    }

    CreateIntfControllerFptr handler = GetCreateIntfControllerFptr(ifaceName);
    if (!handler) {
        QCC_LogError(status, ("%s: could not find interface", __func__));
        return nullptr;
    }

    auto interface = handler(*m_busAttachment, listener, cdmProxyObject);
    if (!interface) {
        QCC_LogError(status, ("%s: could not create interface", __func__));
        return nullptr;
    }

    status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not init interface", __func__));
        return nullptr;
    }

    return interface;
}



QStatus ControllerFactory::RegisterIntfController(const std::string& interfaceName, CreateIntfControllerFptr createIntfController)
{
    auto iter = m_controllerCreators.find(interfaceName);

    if (iter != m_controllerCreators.end()) {
        return ER_DUPLICATE_KEY;
    }

    m_controllerCreators[interfaceName] = createIntfController;
    return ER_OK;
}



QStatus ControllerFactory::UnregisterIntfController(const std::string& interfaceName, CreateIntfControllerFptr createIntfController)
{
    auto iter = m_controllerCreators.find(interfaceName);

    if (iter == m_controllerCreators.end()) {
        return ER_FAIL;
    }

    m_controllerCreators.erase(interfaceName);
    return ER_OK;
}

//======================================================================
}
}