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

#include <qcc/Util.h>

#include <alljoyn/hae/LogModule.h>
#include <alljoyn/hae/interfaces/operation/OffControlIntfControllerListener.h>
#include <alljoyn/hae/HaeProxyBusObject.h>
#include "OffControlIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

HaeInterface* OffControlIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    return new OffControlIntfControllerImpl(busAttachment, dynamic_cast<OffControlIntfControllerListener&>(listener), haeProxyObject);
}

OffControlIntfControllerImpl::OffControlIntfControllerImpl(BusAttachment& busAttachment, OffControlIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject) :
    InterfaceController(haeProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

OffControlIntfControllerImpl::~OffControlIntfControllerImpl()
{
}

QStatus OffControlIntfControllerImpl::Init()
{
    QStatus status = HaeInterface::Init();
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

QStatus OffControlIntfControllerImpl::SwitchOff(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_SwitchOff.c_str(), this, (MessageReceiver::ReplyHandler)&OffControlIntfControllerImpl::SwitchOffReplyHandler, NULL, 0, context);
    return status;

}

void OffControlIntfControllerImpl::SwitchOffReplyHandler(Message& message, void* context)
{
    qcc::String errorMsg;
    const char* errorName = message->GetErrorName(&errorMsg);
    QStatus status = (message->GetType() == MESSAGE_METHOD_RET) ? ER_OK : ER_FAIL;
    m_interfaceListener.OnResponseSwitchOff(status, m_proxyObject.GetPath(),
            context, errorName, errorMsg.c_str());
}


void OffControlIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    // This interface doesn't have any property.
}

} //namespace services
} //namespace ajn
