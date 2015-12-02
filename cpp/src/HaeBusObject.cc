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

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>
#include <alljoyn/hae/interfaces/InterfaceControllee.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

#include "HaeBusObject.h"
#include "InterfaceFactory.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

HaeBusObject::HaeBusObject(BusAttachment& busAttachment, String const& objectPath) :
        BusObject(objectPath.c_str()),
        m_busAttachment(busAttachment)
{

}

HaeBusObject::~HaeBusObject()
{
    for (map<String, HaeInterface*>::iterator it = m_haeInterfacesMap.begin(); it != m_haeInterfacesMap.end(); ++it) {
        delete it->second;
    }
    m_haeInterfacesMap.clear();
}

QStatus HaeBusObject::Start()
{
    QStatus status = ER_OK;

    return status;
}

QStatus HaeBusObject::Stop()
{
    return ER_OK;
}

HaeInterface* HaeBusObject::CreateInterface(const HaeInterfaceType type, InterfaceControlleeListener& listener)
{
    QStatus status = ER_OK;
    HaeInterface* interface = NULL;

    if (InterfaceTypesMap.find(type) == InterfaceTypesMap.end()) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: Function call argument 1 is invalid.", __func__));
        return NULL;
    }

    map<HaeInterfaceType, String>::const_iterator it = InterfaceTypesMap.find(type);
    if (it != InterfaceTypesMap.end()) {
        const String interfaceName = it->second;
        if (m_haeInterfacesMap[interfaceName] == NULL) {

            interface = InterfaceFactory::GetInstance()->CreateIntfControllee(type, listener, *this);
            if (!interface) {
                QCC_LogError(ER_FAIL, ("%s: could not create interface.", __func__));
                return NULL;
            }

            const InterfaceDescription* description = interface->GetInterfaceDescription();
            status = AddInterface(*description, ANNOUNCED);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: could not add interface", __func__));
                delete interface;
                return NULL;
            }

            // Add handlers
            status = AddInterfaceHandlers(interface);
            if (status != ER_OK) {
                QCC_LogError(status, ("%s: could not add method handlers", __func__));
                delete interface;
                return NULL;
            }
            m_haeInterfacesMap[interfaceName] = interface;

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

QStatus HaeBusObject::Get(const char* ifcName, const char* propName, MsgArg& val)
{
    QStatus status = ER_OK;

    map<String, HaeInterface*>::const_iterator it = m_haeInterfacesMap.find(ifcName);
    if (it != m_haeInterfacesMap.end() && it->second) {
        InterfaceControllee* controllee = dynamic_cast<InterfaceControllee*>(it->second);
        if (controllee) {
            status = controllee->OnGetProperty(propName, val);
        } else {
            QCC_LogError(ER_FAIL, ("%s: interface object could not found.", __func__));
            status = ER_FAIL;
        }
    } else {
        QCC_LogError(ER_FAIL, ("%s: interface object could not found.", __func__));
        status = ER_FAIL;
    }

    return status;
}

QStatus HaeBusObject::Set(const char* ifcName, const char* propName, MsgArg& val)
{
    QStatus status = ER_OK;

    map<String, HaeInterface*>::const_iterator it = m_haeInterfacesMap.find(ifcName);
    if (it != m_haeInterfacesMap.end() && it->second) {
        InterfaceControllee* controllee = dynamic_cast<InterfaceControllee*>(it->second);
        if (controllee) {
            status = controllee->OnSetProperty(propName, val);
        } else {
            QCC_LogError(ER_FAIL, ("%s: interface object could not found.", __func__));
            status = ER_FAIL;
        }
    } else {
        QCC_LogError(ER_FAIL, ("%s: interface object could not found.", __func__));
        status = ER_FAIL;
    }

    return status;
}

void HaeBusObject::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
{

    QStatus status = ER_OK;

    map<String, HaeInterface*>::const_iterator it = m_haeInterfacesMap.find(member->iface->GetName());
    if (it != m_haeInterfacesMap.end() && it->second) {

        InterfaceControllee* controllee = dynamic_cast<InterfaceControllee*>(it->second);
        if (controllee) {
            controllee->OnMethodHandler(member, msg);
        } else {
            status = ER_BUS_METHOD_CALL_ABORTED;
            QCC_LogError(status, ("%s: interface object could not found.", __func__));
            MethodReply(msg, status);
        }
    } else {
        status = ER_BUS_METHOD_CALL_ABORTED;
        QCC_LogError(status, ("%s: could not found method handler.", __func__));
        MethodReply(msg, status);
    }
}


QStatus HaeBusObject::AddInterfaceHandlers(HaeInterface* interface)
{
    QStatus status = ER_OK;

    InterfaceControllee* interfaceCtrll = dynamic_cast<InterfaceControllee*>(interface);

    const InterfaceControllee::MethodHandlers& handlers = interfaceCtrll->GetMethodHanders();

    for (InterfaceControllee::MethodHandlers::const_iterator it = handlers.begin(); it != handlers.end(); ++it) {
        status = AddMethodHandler(it->first, static_cast<MessageReceiver::MethodHandler>(&HaeBusObject::OnMethodHandler));
        if (status != ER_OK) {
            QCC_LogError(status, ("%s: could not add method handler.", __func__));
            return status;
        }
    }

    return status;
}

} //namespace services
} //namespace ajn
