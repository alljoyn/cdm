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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Util.h>

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControlleeListener.h>

#include "WaterLevelIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* WaterLevelIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new WaterLevelIntfControlleeImpl(busAttachment, dynamic_cast<WaterLevelIntfControlleeListener&>(listener), cdmBusObject);
}

WaterLevelIntfControlleeImpl::WaterLevelIntfControlleeImpl(BusAttachment& busAttachment, WaterLevelIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_currentLevel(2),
    m_supplySource(SUPPLY_SOURCE_PIPE),
    m_maxLevel(5)
{
}

WaterLevelIntfControlleeImpl::~WaterLevelIntfControlleeImpl()
{
}

QStatus WaterLevelIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    return status;
}

QStatus WaterLevelIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if(!s_prop_CurrentLevel.compare(propName)) {
                uint8_t currLevel;
                status = m_interfaceListener.OnGetCurrentLevel(currLevel);
                if(status !=  ER_OK) {
                    QCC_LogError(status, ("%s: failed to get property.", __func__));
                    currLevel = GetCurrentLevel();
                } else {
                    SetCurrentLevel(currLevel);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = currLevel;
            } else if (!s_prop_MaxLevel.compare(propName)) {
                uint8_t maxLevel;
                status = m_interfaceListener.OnGetCurrentLevel(maxLevel);
                if(status !=  ER_OK) {
                    QCC_LogError(status, ("%s: failed to get property.", __func__));
                    maxLevel = GetMaxLevel();
                } else {
                    SetMaxLevel(maxLevel);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = maxLevel;
            } else if (!s_prop_SupplySource.compare(propName)) {
                WaterLevelSupplySource suppSrc;
                status = m_interfaceListener.OnGetSupplySource(suppSrc);
                if(status !=  ER_OK) {
                    QCC_LogError(status, ("%s: failed to get property.", __func__));
                    suppSrc = GetSupplySource();
                } else {
                    SetSupplySource(suppSrc);
                }
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = (uint8_t)suppSrc;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if(!s_prop_CurrentLevel.compare(propName)) {
                uint8_t currLevel;
                currLevel = GetCurrentLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = currLevel;
            } else if (!s_prop_MaxLevel.compare(propName)) {
                uint8_t maxLevel;
                maxLevel = GetMaxLevel();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = maxLevel;
            } else if (!s_prop_SupplySource.compare(propName)) {
                WaterLevelSupplySource suppSrc;
                suppSrc = GetSupplySource();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = (uint8_t)suppSrc;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus WaterLevelIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void WaterLevelIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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
QStatus WaterLevelIntfControlleeImpl::SetCurrentLevel(const uint8_t currentLevel)
{
    WaterLevelSupplySource src = GetSupplySource();

    if((src == WaterLevelSupplySource::SUPPLY_SOURCE_NOT_SUPPORTED || src == WaterLevelSupplySource::SUPPLY_SOURCE_PIPE) && currentLevel !=0 )
    {
        return ER_FAIL;
    }

    if(currentLevel > m_maxLevel)
    {
        QCC_LogError(ER_FAIL, ("%s: CurrentLevel is more than MaxLevel. ", __func__));
        return ER_FAIL;
    }

    if(currentLevel != m_currentLevel)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_BYTE;
        arg.v_byte = currentLevel;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CurrentLevel.c_str(), arg, 0 ,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_currentLevel = currentLevel;
    }
    return ER_OK;
}

QStatus WaterLevelIntfControlleeImpl::SetMaxLevel(const uint8_t maxLevel)
{
    WaterLevelSupplySource src = GetSupplySource();
    if((src == WaterLevelSupplySource::SUPPLY_SOURCE_NOT_SUPPORTED || src == WaterLevelSupplySource::SUPPLY_SOURCE_PIPE) && maxLevel !=0 )
    {
        return ER_FAIL;
    }

    if(maxLevel != m_maxLevel)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_BYTE;
        arg.v_byte = maxLevel;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_MaxLevel.c_str(), arg, 0 ,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_maxLevel = maxLevel;
    }
    return ER_OK;
}

QStatus WaterLevelIntfControlleeImpl::SetSupplySource(const WaterLevelSupplySource supplySource)
{
    if(supplySource!= m_supplySource)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_BYTE;
        arg.v_byte = (uint8_t)supplySource;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupplySource.c_str(), arg, 0 ,ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_supplySource = supplySource;
    }
    if(m_supplySource == WaterLevelSupplySource::SUPPLY_SOURCE_NOT_SUPPORTED || m_supplySource == WaterLevelSupplySource::SUPPLY_SOURCE_PIPE)
    {
        SetMaxLevel(0);
        SetCurrentLevel(0);
    }

    return ER_OK;
}

} //namespace services
} //namespace ajn