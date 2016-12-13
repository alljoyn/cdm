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

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControllerListener.h>

#include "TimeDisplayIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* TimeDisplayIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new TimeDisplayIntfControllerImpl(busAttachment, dynamic_cast<TimeDisplayIntfControllerListener&>(listener), cdmProxyObject);
}

TimeDisplayIntfControllerImpl::TimeDisplayIntfControllerImpl(BusAttachment& busAttachment, TimeDisplayIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

TimeDisplayIntfControllerImpl::~TimeDisplayIntfControllerImpl()
{
}

QStatus TimeDisplayIntfControllerImpl::Init()
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

void TimeDisplayIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_DisplayTimeFormat.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t timeFormat = propValue->v_byte;
                m_interfaceListener.DisplayTimeFormatPropertyChanged(obj.GetPath(), timeFormat);
            }
        } else if(!s_prop_SupportedDisplayTimeFormats.compare(propNameStr)) {
            uint8_t *vals;
            size_t numVals;
            std::vector<uint8_t> supportedTimeFormats;
            propValue->Get("ay", &numVals, &vals);

            cout << "Selectable Levels: " << endl;
            for (size_t i = 0; i < numVals; ++i) {
                supportedTimeFormats.push_back(vals[i]);
            }
            m_interfaceListener.SupportedDisplayTimeFormatsPropertyChanged(obj.GetPath(), supportedTimeFormats);
        }
    }
}

QStatus TimeDisplayIntfControllerImpl::GetDisplayTimeFormat(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_DisplayTimeFormat.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TimeDisplayIntfControllerImpl::GetDisplayTimeFormatPropertyCB,context);

    return status;
}
QStatus TimeDisplayIntfControllerImpl::SetDisplayTimeFormat(const uint8_t timeFormat, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("y", timeFormat);

    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_DisplayTimeFormat.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&TimeDisplayIntfControllerImpl::SetDisplayTimeFormatPropertyCB,context);

    return status;
}
QStatus TimeDisplayIntfControllerImpl::GetSupportedDisplayTimeFormats(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedDisplayTimeFormats.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&TimeDisplayIntfControllerImpl::GetSupportedDisplayTimeFormatsPropertyCB,context);

    return status;
}

void TimeDisplayIntfControllerImpl::GetDisplayTimeFormatPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    uint8_t timeFormat;
    value.Get("y", &timeFormat);

    m_interfaceListener.GetDisplayTimeFormatPropertyCallback(status,obj->GetPath(),timeFormat,context);
}
void TimeDisplayIntfControllerImpl::SetDisplayTimeFormatPropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj){
        return;
    }
    m_interfaceListener.SetDisplayTimeFormatPropertyCallback(status,obj->GetPath(),context);
}
void TimeDisplayIntfControllerImpl::GetSupportedDisplayTimeFormatsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{

    if(!obj){
        return;
    }

    uint8_t *vals;
    size_t numVals;
    std::vector<uint8_t> supportedTimeFormats;
    value.Get("ay", &numVals, &vals);

    cout << "Supported Time Formats: " << endl;
    for (size_t i = 0; i < numVals; ++i) {
        supportedTimeFormats.push_back(vals[i]);
    }

    m_interfaceListener.GetSupportedDisplayTimeFormatsPropertyCallback(status,obj->GetPath(), supportedTimeFormats, context);
}

} //namespace services
} //namespace ajn