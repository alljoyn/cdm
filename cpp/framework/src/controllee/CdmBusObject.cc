/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
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

#include <map>

#include <alljoyn/cdm/common/LogModule.h>
#include <alljoyn/cdm/controllee/CdmBusObject.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controllee/InterfaceReceiver.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

CdmBusObject::CdmBusObject(BusAttachment& busAttachment, String const& objectPath) :
        BusObject(objectPath.c_str()),
        m_busAttachment(busAttachment)
{}

CdmBusObject::~CdmBusObject()
{
    m_busAttachment.UnregisterBusObject(*this);
    m_cdmInterfacesMap.clear();
}

//QStatus CdmBusObject::Start()
//{
//    QStatus status = ER_OK;
//
//    return status;
//}
//
//QStatus CdmBusObject::Stop()
//{
//    return ER_OK;
//}

QStatus CdmBusObject::RegisterInterface(CdmInterface* interface)
{
    const InterfaceDescription* description = interface->GetInterfaceDescription();
    QStatus status = BusObject::AddInterface(*description, ANNOUNCED);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not add interface", __func__));
        return status;
    }

    // Add handlers
    status = AddInterfaceHandlers(interface);
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not add method handlers", __func__));
        return status;
    }

    m_cdmInterfacesMap[interface->GetInterfaceName()] = interface;

    return ER_OK;
}

QStatus CdmBusObject::Get(const char* ifcName, const char* propName, MsgArg& val)
{
    QStatus status = ER_OK;

    map<String, CdmInterface*>::const_iterator it = m_cdmInterfacesMap.find(ifcName);
    if (it != m_cdmInterfacesMap.end() && it->second) {
        InterfaceReceiver* controllee = dynamic_cast<InterfaceReceiver*>(it->second);
        if (controllee) {
            status = controllee->OnGetProperty(propName, val);
        } else {
            QCC_LogError(ER_FAIL, ("%s: interface object not found.", __func__));
            status = ER_FAIL;
        }
    } else {
        QCC_LogError(ER_FAIL, ("%s: interface object not found.", __func__));
        status = ER_FAIL;
    }

    return status;
}

QStatus CdmBusObject::Set(const char* ifcName, const char* propName, MsgArg& val)
{
    QStatus status = ER_OK;

    map<String, CdmInterface*>::const_iterator it = m_cdmInterfacesMap.find(ifcName);
    if (it != m_cdmInterfacesMap.end() && it->second) {
        InterfaceReceiver* controllee = dynamic_cast<InterfaceReceiver*>(it->second);
        if (controllee) {
            status = controllee->OnSetProperty(propName, val);
        } else {
            QCC_LogError(ER_FAIL, ("%s: interface object not found.", __func__));
            status = ER_FAIL;
        }
    } else {
        QCC_LogError(ER_FAIL, ("%s: interface object not found.", __func__));
        status = ER_FAIL;
    }

    return status;
}


void CdmBusObject::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{

    QStatus status = ER_OK;

    auto it = m_cdmInterfacesMap.find(member->iface->GetName());
    if (it != m_cdmInterfacesMap.end() && it->second) {

        InterfaceReceiver* controllee = dynamic_cast<InterfaceReceiver*>(it->second);
        if (controllee) {
            controllee->OnMethodHandler(member, msg);
        } else {
            status = ER_BUS_METHOD_CALL_ABORTED;
            QCC_LogError(status, ("%s: interface object not found.", __func__));
            MethodReply(msg, status);
        }
    } else {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: method handler not found.", __func__));
        MethodReply(msg, status);
    }
}


QStatus CdmBusObject::AddInterfaceHandlers(CdmInterface* interface)
{
    QStatus status = ER_OK;

    InterfaceReceiver* interfaceCtrll = dynamic_cast<InterfaceReceiver*>(interface);

    const InterfaceReceiver::MethodHandlers& handlers = interfaceCtrll->GetMethodHanders();

    for (InterfaceReceiver::MethodHandlers::const_iterator it = handlers.begin(); it != handlers.end(); ++it) {
        status = AddMethodHandler(it->first, static_cast<MessageReceiver::MethodHandler>(&CdmBusObject::OnMethodHandler));
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: could not add method handler.", __func__));
            return status;
        }
    }

    return status;
}

} //namespace services
} //namespace ajn
