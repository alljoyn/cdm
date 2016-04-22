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

#include <algorithm>
#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/HaeBusObject.h>
#include <alljoyn/hae/interfaces/operation/AlertsIntfControlleeListener.h>

#include "AlertsIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* AlertsIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    return new AlertsIntfControlleeImpl(busAttachment, dynamic_cast<AlertsIntfControlleeListener&>(listener), haeBusObject);
}

AlertsIntfControlleeImpl::AlertsIntfControlleeImpl(BusAttachment& busAttachment, AlertsIntfControlleeListener& listener, HaeBusObject& haeBusObject) :
    InterfaceControllee(haeBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

AlertsIntfControlleeImpl::~AlertsIntfControlleeImpl()
{
}

QStatus AlertsIntfControlleeImpl::Init()
{
    QStatus status = HaeInterface::Init();

    const InterfaceDescription::Member* descMember = m_interfaceDescription->GetMember(s_method_GetAlertCodesDescription.c_str());
    MessageReceiver::MethodHandler descMethodHandler = static_cast<MessageReceiver::MethodHandler>(&AlertsIntfControlleeImpl::OnGetAlertCodesDescription);

    m_methodHandlers.push_back(make_pair(descMember, descMethodHandler));

    const InterfaceDescription::Member* ackMember = m_interfaceDescription->GetMember(s_method_AcknowledgeAlert.c_str());
    MessageReceiver::MethodHandler ackMethodHandler = static_cast<MessageReceiver::MethodHandler>(&AlertsIntfControlleeImpl::OnAcknowledgeAlert);

    m_methodHandlers.push_back(make_pair(ackMember, ackMethodHandler));

    const InterfaceDescription::Member* ackAllMember = m_interfaceDescription->GetMember(s_method_AcknowledgeAllAlerts.c_str());
    MessageReceiver::MethodHandler ackAllMethodHandler = static_cast<MessageReceiver::MethodHandler>(&AlertsIntfControlleeImpl::OnAcknowledgeAllAlerts);

    m_methodHandlers.push_back(make_pair(ackAllMember, ackAllMethodHandler));

    return status;
}

QStatus AlertsIntfControlleeImpl::OnGetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName)))
    {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    }
    else
    {
        if (s_retrievingActualPropertyValue)
        {
            if(!s_prop_Alerts.compare(propName))
            {
                AlertsInterface::Alerts alerts;
                status = m_interfaceListener.OnGetAlerts(alerts);
                if(status != ER_OK)
                {
                    alerts = GetAlerts();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                }
                else
                {
                    SetAlerts(alerts); // update the value in ChannelIntfControllee.
                }

                int numAlerts = alerts.size();

                AlertsInterface::Alerts::const_iterator citer;
                MsgArg *args = new MsgArg[numAlerts];
                int i=0;

                for(citer = alerts.begin(); citer != alerts.end(); citer++, i++) {
                    status = args[i].Set("(yqb)", (uint8_t)citer->severity, citer->alertCode, citer->needAcknowledgement);
                    args[i].Stabilize();
                }
                status = val.Set("a(yqb)", i, args);
                val.Stabilize();
                delete [] args;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
        else
        {
            if(!s_prop_Alerts.compare(propName))
            {
                AlertsInterface::Alerts alerts;
                alerts = GetAlerts();

                int numAlerts = alerts.size();

                AlertsInterface::Alerts::const_iterator citer;
                MsgArg *args = new MsgArg[numAlerts];
                int i=0;

                for(citer = alerts.begin(); citer != alerts.end(); citer++, i++) {
                    status = args[i].Set("(yqb)", (uint8_t)citer->severity, citer->alertCode, citer->needAcknowledgement);
                    args[i].Stabilize();
                }
                status = val.Set("a(yqb)", i, args);
                val.Stabilize();
                delete [] args;
            }
            else
            {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
        }
    }

    return status;
}

QStatus AlertsIntfControlleeImpl::OnSetProperty(const String propName, MsgArg& val)
{
    QStatus status = ER_OK;

    return status;
}

void AlertsIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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

QStatus AlertsIntfControlleeImpl::SetAlerts(const Alerts& alerts)
{
    QStatus status = ER_OK;
    bool listChanged = false;

    if(m_alerts.size() != alerts.size())
        listChanged = true;
    else
    {
        for (size_t i = 0; i < alerts.size(); i ++)
        {
            Alerts::iterator it;
            it = std::find(m_alerts.begin(), m_alerts.end(), alerts[i]);
            if(it == m_alerts.end())
            {
                listChanged = true;
                break;
            }
        }
    }

    if(listChanged)
    {
        m_alerts.clear();
        for(size_t i =0; i < alerts.size(); i++)
            m_alerts.push_back(alerts[i]);


        MsgArg val;
        int numAlerts = m_alerts.size();

        AlertsInterface::Alerts::const_iterator citer;
        MsgArg *args = new MsgArg[numAlerts];
        int i=0;

        for(citer = m_alerts.begin(); citer != m_alerts.end(); citer++, i++) {
            status = args[i].Set("(yqb)", (uint8_t)citer->severity, citer->alertCode, citer->needAcknowledgement);
            args[i].Stabilize();
        }
        status = val.Set("a(yqb)", i, args);
        val.Stabilize();
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(),s_prop_Alerts.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        delete [] args;
    }


    return status;
}

void AlertsIntfControlleeImpl::OnGetAlertCodesDescription(const InterfaceDescription::Member* member, Message& msg)
{
    cout << "AlertsIntfControlleeImpl::OnGetAlertCodesDescription" << endl;
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
            AlertsInterface::AlertCodesDescription listOfDescriptions;
            ErrorCode errorCode = NOT_ERROR;
            status = m_interfaceListener.OnGetAlertCodesDescription(lang, listOfDescriptions, errorCode);
            if(status == ER_OK)
            {
                int numReturned = listOfDescriptions.size();
                AlertsInterface::AlertCodesDescription::const_iterator citer;
                MsgArg *args = new MsgArg[numReturned];
                MsgArg retArgs[1];
                int i=0;

                for(citer = listOfDescriptions.begin(); citer != listOfDescriptions.end(); citer++, i++) {
                    status = args[i].Set("(qs)", citer->code, citer->description.c_str());
                    args[i].Stabilize();
                }
                status = retArgs[0].Set("a(qs)", i, args);
                retArgs[0].Stabilize();
                status = m_busObject.ReplyMethodCall(msg, retArgs, ArraySize(retArgs));
                delete [] args;
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

void AlertsIntfControlleeImpl::OnAcknowledgeAlert(const InterfaceDescription::Member* member, Message& msg)
{
    cout << "AlertsIntfControlleeImpl::OnAcknowledgeAlert" << endl;
    QStatus status = ER_OK;
    ErrorCode errorCode;

    const MsgArg* args = NULL;

    size_t numArgs = 0;

    msg->GetArgs(numArgs, args);

    if (numArgs == 1)
    {
        size_t i = 0;
        uint16_t alertCode = args[0].v_uint16;
        for(i = 0; i < m_alerts.size(); ++i)
        {
            if(m_alerts[i].alertCode == alertCode)
            {
                break;
            }
        }

        if(i == m_alerts.size() || !m_alerts[i].needAcknowledgement)
        {
            status = ER_BAD_ARG_1;
            QCC_LogError(status, ("%s: invalid value", __func__));
            m_busObject.ReplyMethodCall(msg, status);
        }
        else
        {
            status = m_interfaceListener.OnAcknowledgeAlert(alertCode, errorCode);
            if(status == ER_OK)
            {
                m_busObject.ReplyMethodCall(msg, status);
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

void AlertsIntfControlleeImpl::OnAcknowledgeAllAlerts(const InterfaceDescription::Member* member, Message& msg)
{
    cout << "AlertsIntfControlleeImpl::OnAcknowledgeAlert" << endl;
    QStatus status = ER_OK;
    ErrorCode errorCode;

    status = m_interfaceListener.OnAcknowledgeAllAlerts(errorCode);
    if(status == ER_OK)
    {
        m_busObject.ReplyMethodCall(msg, status);
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

} //namespace services
} //namespace ajn
