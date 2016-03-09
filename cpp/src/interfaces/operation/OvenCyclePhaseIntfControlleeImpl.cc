/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Util.h>
#include <vector>
#include <algorithm>
#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeBusObject.h>
#include <alljoyn/hae/interfaces/operation/OvenCyclePhaseIntfControlleeListener.h>

#include "OvenCyclePhaseIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* OvenCyclePhaseIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new OvenCyclePhaseIntfControlleeImpl(busAttachment, dynamic_cast<OvenCyclePhaseIntfControlleeListener&>(listener), haeBusObject);
}

OvenCyclePhaseIntfControlleeImpl::OvenCyclePhaseIntfControlleeImpl(BusAttachment& busAttachment, OvenCyclePhaseIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_cyclePhase(OvenCyclePhaseInterface::OvenCyclePhase::OVEN_PHASE_PREHEATING)
{
}

OvenCyclePhaseIntfControlleeImpl::~OvenCyclePhaseIntfControlleeImpl()
{
}

QStatus OvenCyclePhaseIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();

    const InterfaceDescription::Member* member = m_interfaceDescription->GetMember(s_method_GetVendorPhasesDescription.c_str());
    MessageReceiver::MethodHandler methodHandler = static_cast<MessageReceiver::MethodHandler>(&OvenCyclePhaseIntfControlleeImpl::OnGetCyclePhasesDescription);

    m_methodHandlers.push_back(make_pair(member, methodHandler));

    return status;
}

QStatus OvenCyclePhaseIntfControlleeImpl::OnGetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    }
    else
    {
        if (s_retrievingActualPropertyValue)
        {
            if(!s_prop_CyclePhase.compare(propName))
            {
                uint8_t cyclePhase;
                status = m_interfaceListener.OnGetCyclePhase(cyclePhase);
                if (status != ER_OK) {
                    cyclePhase = GetCyclePhase();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetCyclePhase(cyclePhase); // update the value in ChannelIntfControllee.
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = (uint8_t)cyclePhase;

            }
            else if (!s_prop_SupportedCyclePhases.compare(propName))
            {
                SupportedCyclePhases supportedCyclePhases;
                status = m_interfaceListener.OnGetSupportedCyclePhases(supportedCyclePhases);
                if(status != ER_OK)
                {
                    supportedCyclePhases = GetSupportedCyclePhases();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                }
                else
                {
                    //update internal value
                    SetSupportedCyclePhases(supportedCyclePhases);
                }
                uint8_t vals[supportedCyclePhases.size()];
                size_t i = 0;

                for(i = 0; i < supportedCyclePhases.size(); i++)
                {
                    vals[i] = (uint8_t)supportedCyclePhases[i];
                }
                val.Set("ay", sizeof(vals)/ sizeof(uint8_t), vals);
                val.Stabilize();
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
        else
        {
            if(!s_prop_CyclePhase.compare(propName))
            {
                uint8_t cyclePhase;
                cyclePhase = GetCyclePhase();

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = (uint8_t)cyclePhase;
            }
            else if (!s_prop_SupportedCyclePhases.compare(propName))
            {
                SupportedCyclePhases supportedCyclePhases;
                supportedCyclePhases = GetSupportedCyclePhases();
                uint8_t vals[supportedCyclePhases.size()];
                size_t i = 0;

                for(i = 0; i < supportedCyclePhases.size(); i++)
                {
                    vals[i] = (uint8_t)supportedCyclePhases[i];
                }
                val.Set("ay", sizeof(vals)/ sizeof(uint8_t), vals);
                val.Stabilize();
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus OvenCyclePhaseIntfControlleeImpl::OnSetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void OvenCyclePhaseIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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
QStatus OvenCyclePhaseIntfControlleeImpl::SetCyclePhase(const uint8_t cyclePhase)
{
    StandardCyclePhases::const_iterator stand_it;
    std::vector<uint8_t>::iterator vend_it;

    stand_it = std::find(m_standardCyclePhases.begin(), m_standardCyclePhases.end(), cyclePhase);
    vend_it = std::find(m_vendorDefinedCyclePhases.begin(),m_vendorDefinedCyclePhases.end(),cyclePhase);

    if(vend_it == m_vendorDefinedCyclePhases.end() && stand_it == m_standardCyclePhases.end())
        return ER_FAIL;

    SupportedCyclePhases::iterator supp_it;
    supp_it = std::find(m_supportedCyclePhases.begin(),m_supportedCyclePhases.end(),cyclePhase);
    if(supp_it == m_supportedCyclePhases.end())
        return ER_FAIL;

    if(m_cyclePhase != cyclePhase)
    {
        MsgArg arg;
        arg.typeId = ALLJOYN_BYTE;
        arg.v_byte = cyclePhase;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_CyclePhase.c_str(), arg, 0, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_cyclePhase = cyclePhase;
    }
    return ER_OK;
}

QStatus OvenCyclePhaseIntfControlleeImpl::SetSupportedCyclePhases(const SupportedCyclePhases& supportedPhases)
{
    uint8_t vals[supportedPhases.size()];

    bool listChanged = false;

    if(m_supportedCyclePhases.size() != supportedPhases.size())
        listChanged = true;
    else
    {
        for (size_t i = 0; i < supportedPhases.size(); i++)
        {
            StandardCyclePhases::const_iterator stand_it;
            std::vector<uint8_t>::iterator vend_it;

            stand_it = std::find(m_standardCyclePhases.begin(), m_standardCyclePhases.end(), supportedPhases[i]);
            vend_it = std::find(m_vendorDefinedCyclePhases.begin(),m_vendorDefinedCyclePhases.end(),supportedPhases[i]);

            if(vend_it == m_vendorDefinedCyclePhases.end() && stand_it == m_standardCyclePhases.end())
                return ER_FAIL;

            if(supportedPhases[i] != m_supportedCyclePhases[i])
            {
                listChanged = true;
                break;
            }
        }
    }

    if(listChanged)
    {
        m_supportedCyclePhases.clear();
        for(size_t i = 0 ; i < supportedPhases.size(); i ++)
        {
            m_supportedCyclePhases.push_back(supportedPhases[i]);
            vals[i] = (uint8_t)supportedPhases[i];
        }

        MsgArg arg;
        arg.Set("ay", sizeof(vals)/ sizeof(uint8_t), vals);
        arg.Stabilize();

        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_SupportedCyclePhases.c_str(), arg, 0 , ALLJOYN_FLAG_GLOBAL_BROADCAST);
    }
    return ER_OK;
}

void OvenCyclePhaseIntfControlleeImpl::OnGetCyclePhasesDescription(const InterfaceDescription::Member* member, Message& msg)
{
    cout << "OvenCyclePhaseIntfControlleeImpl::OnGetCyclePhasesDescription" << endl;
    QStatus status = ER_OK;

    const MsgArg* args = NULL;
    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1)
    {
        qcc::String lang(args[0].v_string.str);
        if(lang.compare("en"))
        {
            status = ER_LANGUAGE_NOT_SUPPORTED;
            QCC_LogError(status, ("%s: language not suppoerted", __func__));
            m_busObject.ReplyMethodCall(msg, status);
        }
        else
        {
            CyclePhaseDescriptions listOfDescriptions;
            ErrorCode errorCode = NOT_ERROR;
            status = m_interfaceListener.OnGetCyclePhasesDescriptions(lang, listOfDescriptions, errorCode);
            if(status == ER_OK)
            {
                int numReturned = listOfDescriptions.size();
                OvenCyclePhaseInterface::CyclePhaseDescriptions::const_iterator citer;
                MsgArg args[numReturned];
                MsgArg retArgs[1];
                int i=0;

                for(citer = listOfDescriptions.begin(); citer != listOfDescriptions.end(); citer++, i++) {
                    status = args[i].Set("(yss)", (uint8_t)citer->phase, citer->name.c_str(), citer->description.c_str());
                    args[i].Stabilize();
                }
                status = retArgs[0].Set("a(yss)", i, args);
                retArgs[0].Stabilize();
                status = m_busObject.ReplyMethodCall(msg, retArgs, ArraySize(retArgs));
            }
            else
            {
                if (errorCode == NOT_ERROR)
                {
                    QCC_LogError(status, ("%s: status is not ER_OK, but errorCode was not set.", __func__));
                    m_busObject.ReplyMethodCall(msg, status);
                }
                else
                {
                    m_busObject.ReplyMethodCall(msg, HaeInterface::GetInterfaceErrorName(errorCode).c_str(),HaeInterface::GetInterfaceErrorMessage(errorCode).c_str());
                }
            }
        }
    }
    else
    {
        m_busObject.ReplyMethodCall(msg, ER_INVALID_DATA);
    }
}
QStatus OvenCyclePhaseIntfControlleeImpl::SetVendorDefinedCyclePhases(const std::vector<uint8_t>& vendorPhases)
{
    for(size_t i = 0 ; i < vendorPhases.size(); i++)
    {
        if(vendorPhases[i] < 0x80 )
            return ER_FAIL;
    }
    bool listChanged = false;
    if(m_vendorDefinedCyclePhases.size() != vendorPhases.size())
            listChanged = true;
    else
    {
        for(size_t i = 0 ; i < vendorPhases.size(); i++)
        {
            std::vector<uint8_t>::iterator it;
            it = std::find(m_vendorDefinedCyclePhases.begin(),m_vendorDefinedCyclePhases.end(), vendorPhases[i]);
            if(it == m_vendorDefinedCyclePhases.end())
            {
                listChanged = true;
                break;
            }
        }
    }
    if(listChanged)
    {
        m_vendorDefinedCyclePhases.clear();
        for (size_t i =0;i<vendorPhases.size();i++)
            m_vendorDefinedCyclePhases.push_back(vendorPhases[i]);
    }
    return ER_OK;
}

} //namespace services
} //namespace ajn
