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
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>

#include "HaeProxyBusObject.h"
#include "InterfaceFactory.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

HaeProxyBusObject::HaeProxyBusObject(BusAttachment& busAttachment, std::string const& busName, qcc::String const& objectPath, SessionId sessionId) :
        ProxyBusObject(busAttachment, busName.c_str(), objectPath.c_str(), sessionId),
        m_busAttachment(busAttachment)
{

}

HaeProxyBusObject::~HaeProxyBusObject()
{
    for (map<String, HaeInterface*>::iterator it = m_haeInterfacesMap.begin(); it != m_haeInterfacesMap.end(); ++it) {
        delete it->second;
    }
    m_haeInterfacesMap.clear();
}

HaeInterface* HaeProxyBusObject::CreateInterface(const HaeInterfaceType type, InterfaceControllerListener& listener)
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

} //namespace services
} //namespace ajn
