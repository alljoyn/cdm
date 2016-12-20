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
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControlleeListener.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include "AudioVideoInputIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* AudioVideoInputIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new AudioVideoInputIntfControlleeImpl(busAttachment, static_cast<AudioVideoInputIntfControlleeListener&>(listener), cdmBusObject);
}

AudioVideoInputIntfControlleeImpl::AudioVideoInputIntfControlleeImpl(BusAttachment& busAttachment, AudioVideoInputIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_inputSourceId (0)
{
}

AudioVideoInputIntfControlleeImpl::~AudioVideoInputIntfControlleeImpl()
{
}

QStatus AudioVideoInputIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus AudioVideoInputIntfControlleeImpl::SetInputSourceId(const uint16_t inputSourceId)
{
    if (m_supportedInputSources.find(inputSourceId) == m_supportedInputSources.end()) {
        QCC_LogError(ER_INVALID_DATA, ("%s: InputSourceId is not exist in SupportedInputSources.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_inputSourceId != inputSourceId) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = inputSourceId;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_InputSourceId.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_inputSourceId = inputSourceId;
    }
    return ER_OK;
}

QStatus AudioVideoInputIntfControlleeImpl::SetSupportedInputSources(const InputSources& supportedInputSources)
{
    bool diff = false;
    QStatus status = CheckSupportedInputSources(supportedInputSources);

    if (status != ER_OK) {
        return status;
    }

    if (m_supportedInputSources.size() != supportedInputSources.size()) {
        diff = true;
    } else {
        InputSources::const_iterator citer1 = m_supportedInputSources.begin();
        InputSources::const_iterator citer2 = supportedInputSources.begin();

        while (citer1 != m_supportedInputSources.end()) {
            if (citer1->first != citer2->first) {
                diff = true;
                break;
            }

            if ((citer1->second).sourceType != (citer2->second).sourceType
                || (citer1->second).signalPresence != (citer2->second).signalPresence
                || (citer1->second).portNumber != (citer2->second).portNumber
                || (citer1->second).friendlyName != (citer2->second).friendlyName) {
                diff = true;
                break;
            }

            citer1++;
            citer2++;
        }
    }

    if (diff) {
        MsgArg* args = new MsgArg[supportedInputSources.size()];
        MsgArg val;
        InputSources::const_iterator citer;
        int i=0;

        for(citer = supportedInputSources.begin(); citer != supportedInputSources.end(); citer++, i++) {
            args[i].Set("(qqyqs)", citer->first, citer->second.sourceType, citer->second.signalPresence,
                        citer->second.portNumber, citer->second.friendlyName.c_str());
            args[i].Stabilize();
        }

        val.typeId = ALLJOYN_ARRAY;
        val.v_array.SetElements("(qqyqs)", i, args);
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedInputSources.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_supportedInputSources = supportedInputSources;
        delete[] args;
    }

    return ER_OK;
}

QStatus AudioVideoInputIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_InputSourceId.compare(propName))) {
                uint16_t inputSourceId;
                status = m_interfaceListener.OnGetInputSourceId(inputSourceId);
                if (status != ER_OK) {
                    inputSourceId = GetInputSourceId();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetInputSourceId(inputSourceId); // update the value in AudioVideoInputIntfControllee.
                }
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = inputSourceId;
            } else if (!(s_prop_SupportedInputSources.compare(propName))) {
                InputSources supportedInputSources;
                status = m_interfaceListener.OnGetSupportedInputSources(supportedInputSources);
                if (status != ER_OK) {
                    supportedInputSources = GetSupportedInputSources();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetSupportedInputSources(supportedInputSources);
                }

                MsgArg* args = new MsgArg[supportedInputSources.size()];
                InputSources::const_iterator citer;
                int i=0;

                for(citer = supportedInputSources.begin(); citer != supportedInputSources.end(); citer++, i++) {
                     args[i].Set("(qqyqs)", citer->first, citer->second.sourceType, citer->second.signalPresence,
                                citer->second.portNumber, citer->second.friendlyName.c_str());
                     args[i].Stabilize();
                }

                val.Set("a(qqyqs)", i, args);
                val.Stabilize();
                delete[] args;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        } else {
            if (!(s_prop_InputSourceId.compare(propName))) {
                const uint16_t inputSourceId = GetInputSourceId();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = inputSourceId;
            } else if (!(s_prop_SupportedInputSources.compare(propName))) {
                const InputSources& supportedInputSources = GetSupportedInputSources();
                MsgArg* args = new MsgArg[supportedInputSources.size()];
                InputSources::const_iterator citer;
                int i=0;

                for(citer = supportedInputSources.begin(); citer != supportedInputSources.end(); citer++, i++) {
                    args[i].Set("(qqyqs)", citer->first, citer->second.sourceType, citer->second.signalPresence,
                                citer->second.portNumber, citer->second.friendlyName.c_str());
                    args[i].Stabilize();
                }

                val.Set("a(qqyqs)", i, args);
                val.Stabilize();
                delete[] args;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus AudioVideoInputIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_InputSourceId.compare(propName))) {
        if (val.typeId != ALLJOYN_UINT16) {
            status = ER_BUS_NO_SUCH_PROPERTY;
            return status;
        }
        uint16_t inputSourceId = val.v_uint16;
        if (m_supportedInputSources.find(inputSourceId) == m_supportedInputSources.end()) {
            status = ER_INVALID_DATA;
            QCC_LogError(status, ("%s: InputSourceId is not exist in SupportedInputSources.", __func__));
            return status;
        }
        status = m_interfaceListener.OnSetInputSourceId(inputSourceId);
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: failed to set property value", __func__));
            status = ER_BUS_PROPERTY_VALUE_NOT_SET;
        } else {
            SetInputSourceId(inputSourceId); // update the value in AudioVolumeIntfControllee.
        }
    } else {
        status = ER_BUS_NO_SUCH_PROPERTY;
    }

    return status;
}

void AudioVideoInputIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus AudioVideoInputIntfControlleeImpl::CheckSupportedInputSources(const InputSources& supportedInputSources)
{
    InputSources::const_iterator citer;
    int i=0;

    for (citer = supportedInputSources.begin(); citer != supportedInputSources.end(); citer++) {
        if (citer->second.sourceType < MIN_AUDIO_VIDEO_INPUT_SOURCE_TYPE
            || citer->second.sourceType > MAX_AUDIO_VIDEO_INPUT_SOURCE_TYPE) {
            QCC_LogError(ER_FAIL, ("%s: Invaild sourceType", __func__));
            break;
        } else if (citer->second.signalPresence != AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_UNKNOWN
                   && citer->second.signalPresence != AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_PRESENT
                   && citer->second.signalPresence != AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_ABSENT) {
            QCC_LogError(ER_FAIL, ("%s: Invaild signalPresence", __func__));
            break;
        }
    }

    if (citer != supportedInputSources.end()) {
        return ER_FAIL;
    }

    return ER_OK;
}

} //namespace services
} //namespace ajn