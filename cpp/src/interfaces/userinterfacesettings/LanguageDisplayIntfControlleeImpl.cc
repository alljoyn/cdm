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
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControlleeListener.h>
#include <algorithm>

#include "LanguageDisplayIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* LanguageDisplayIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new LanguageDisplayIntfControlleeImpl(busAttachment, dynamic_cast<LanguageDisplayIntfControlleeListener&>(listener), cdmBusObject);
}

LanguageDisplayIntfControlleeImpl::LanguageDisplayIntfControlleeImpl(BusAttachment& busAttachment, LanguageDisplayIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

LanguageDisplayIntfControlleeImpl::~LanguageDisplayIntfControlleeImpl()
{
}

QStatus LanguageDisplayIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();
    /**
     * TODO: add method handler
     */
    return status;
}

QStatus LanguageDisplayIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if(!s_prop_DisplayLanguage.compare(propName)) {
                qcc::String displayLanguage;
                status = m_interfaceListener.OnGetDisplayLanguage(displayLanguage);
                if(status != ER_OK) {
                    QCC_LogError(status, ("%s: failed to get display language prop", __func__));
                }
                else {
                    //update and emit
                    SetDisplayLanguage(displayLanguage);
                }
                val.typeId = ALLJOYN_STRING;
                val.Set("s", displayLanguage.c_str());
                val.Stabilize();
            } else if (!s_prop_SupportedDisplayLanguages.compare(propName)) {
                std::vector<qcc::String> supportedDisplayLanguages = GetSupportedDisplayLanguages();

                const char **vals = (const char**)malloc(supportedDisplayLanguages.size() * 3);
                memset(vals, 0 , supportedDisplayLanguages.size() * 3);

                size_t i = 0;
                std::vector<qcc::String>::const_iterator citer;
                for (citer = supportedDisplayLanguages.begin(); citer != supportedDisplayLanguages.end(); citer++, i++) {
                            vals[i] = citer->c_str();
                        }

                val.Set("as", supportedDisplayLanguages.size(), vals);
                val.Stabilize();
                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if(!s_prop_DisplayLanguage.compare(propName)) {
                qcc::String displayLanguage = GetDisplayLanguage();
                val.typeId = ALLJOYN_STRING;
                val.Set("s", displayLanguage.c_str());
                val.Stabilize();
            } else if(!s_prop_SupportedDisplayLanguages.compare(propName)) {

                std::vector<qcc::String> supportedDisplayLanguages = GetSupportedDisplayLanguages();

                const char **vals = (const char**)malloc(supportedDisplayLanguages.size() * 3);
                memset(vals, 0 , supportedDisplayLanguages.size() * 3);

                size_t i = 0;
                std::vector<qcc::String>::const_iterator citer;
                for (citer = supportedDisplayLanguages.begin(); citer != supportedDisplayLanguages.end(); citer++, i++) {
                            vals[i] = citer->c_str();
                        }

                val.Set("as", supportedDisplayLanguages.size(), vals);
                val.Stabilize();

                delete[] vals;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

bool LanguageDisplayIntfControlleeImpl::CheckValidationOfDisplayLanguage(const qcc::String& displayLanguage) {
    std::vector<qcc::String>::iterator it;
    it = std::find(m_supportedDisplayLanguages.begin(), m_supportedDisplayLanguages.end(), displayLanguage);
    return it != m_supportedDisplayLanguages.end();
}

QStatus LanguageDisplayIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;
    if(!s_prop_DisplayLanguage.compare(propName)) {
        if(val.typeId != ALLJOYN_STRING){
            status = ER_BUS_BAD_VALUE_TYPE;
            return status;
        } else {
            qcc::String inputVal(val.v_string.str);
            if(!CheckValidationOfDisplayLanguage(inputVal)) {
                status = ER_INVALID_DATA;
                QCC_LogError(status, ("%s: property value not set ", __func__));
                return status;
            }
            status = m_interfaceListener.OnSetDisplayLanguage(val.v_string.str);
            if(status != ER_OK) {
                status = ER_INVALID_DATA;
                QCC_LogError(status, ("%s: property value not set ", __func__));
            } else {
                status = SetDisplayLanguage(qcc::String(val.v_string.str));
            }
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }
    return status;
}

void LanguageDisplayIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus LanguageDisplayIntfControlleeImpl::SetDisplayLanguage(const qcc::String& displayLanguage)
{
    if(!CheckValidationOfDisplayLanguage(displayLanguage)) {
        QCC_LogError(ER_INVALID_DATA, ("%s: property value not set ", __func__));
        return ER_INVALID_DATA;
    }

    if(displayLanguage != m_displayLanguage)
    {
        MsgArg arg;
        arg.Set("s", displayLanguage.c_str());
        arg.Stabilize();
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_DisplayLanguage.c_str(), arg, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_displayLanguage = displayLanguage;
    }
    return ER_OK;
}

QStatus LanguageDisplayIntfControlleeImpl::SetSupportedDisplayLanguages(const std::vector<qcc::String>& supportedDisplayLanguages)
{
    MsgArg arg;

    const char **vals = (const char**)malloc(supportedDisplayLanguages.size() * 3);
    memset(vals, 0 , supportedDisplayLanguages.size() * 3);
    size_t i = 0;
    std::vector<qcc::String>::const_iterator citer;
    for (citer = supportedDisplayLanguages.begin(); citer != supportedDisplayLanguages.end(); citer++, i++) {
                vals[i] = citer->c_str();
            }

    arg.Set("as", supportedDisplayLanguages.size(), vals);
    arg.Stabilize();

    if(m_supportedDisplayLanguages.size() > 0)
        m_supportedDisplayLanguages.clear();

    for(i = 0; i < supportedDisplayLanguages.size(); i ++)
        m_supportedDisplayLanguages.push_back(supportedDisplayLanguages[i]);

    m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedDisplayLanguages.c_str(), arg, SESSION_ID_ALL_HOSTED ,ALLJOYN_FLAG_GLOBAL_BROADCAST);
    delete[] vals;
    return ER_OK;
}

} //namespace services
} //namespace ajn