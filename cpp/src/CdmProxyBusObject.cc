/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>
#include <alljoyn/cdm/interfaces/CdmInterfaceTypes.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

#include <alljoyn/cdm/CdmProxyBusObject.h>
#include "InterfaceFactory.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmProxyBusObject::CdmProxyBusObject(BusAttachment& busAttachment, std::string const& busName, qcc::String const& objectPath, SessionId sessionId) :
        ProxyBusObject(busAttachment, busName.c_str(), objectPath.c_str(), sessionId),
        m_busAttachment(busAttachment)
{

}

CdmProxyBusObject::~CdmProxyBusObject()
{
    for (map<String, CdmInterface*>::iterator it = m_cdmInterfacesMap.begin(); it != m_cdmInterfacesMap.end(); ++it) {
        delete it->second;
    }
    m_cdmInterfacesMap.clear();
}

CdmInterface* CdmProxyBusObject::CreateInterface(const CdmInterfaceType type, InterfaceControllerListener& listener)
{
    QStatus status = ER_OK;
    CdmInterface* interface = NULL;

    if (InterfaceTypesMap.find(type) == InterfaceTypesMap.end()) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: Function call argument 1 is invalid.", __func__));
        return NULL;
    }

    map<CdmInterfaceType, String>::const_iterator it = InterfaceTypesMap.find(type);
    if (it != InterfaceTypesMap.end()) {
        const String interfaceName = it->second;
        if (m_cdmInterfacesMap[interfaceName] == NULL) {
            interface = InterfaceFactory::GetInstance()->CreateIntfController(type, listener, *this);
            if (!interface) {
                QCC_LogError(ER_FAIL, ("%s: could not create interface.", __func__));
                return NULL;
            }

            const InterfaceDescription* description = interface->GetInterfaceDescription();
            status = AddInterface(*description);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: could not add interface.", __func__));
                delete interface;
                return NULL;
            }

            m_cdmInterfacesMap[interfaceName] = interface;
        } else {
            QCC_LogError(ER_FAIL, ("%s: the interface instance already exists.", __func__));
            return NULL;
        }
    } else {
        QCC_LogError(ER_FAIL, ("%s: interface type not found.", __func__));
        return NULL;
    }
    return interface;
}

} //namespace services
} //namespace ajn