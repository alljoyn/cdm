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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/interfaces/input/HidIntfControllerListener.h>

#include "HidIntfControllerImpl.h"
#include <alljoyn/cdm/CdmProxyBusObject.h>

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* HidIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new HidIntfControllerImpl(busAttachment, static_cast<HidIntfControllerListener&>(listener), cdmProxyObject);
}

HidIntfControllerImpl::HidIntfControllerImpl(BusAttachment& busAttachment, HidIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

HidIntfControllerImpl::~HidIntfControllerImpl()
{
}

QStatus HidIntfControllerImpl::Init()
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

QStatus HidIntfControllerImpl::GetSupportedEvents(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedEvents.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&HidIntfControllerImpl::GetSupportedEventsPropertyCB, context);

    return status;
}

QStatus HidIntfControllerImpl::InjectEvents(const std::vector<InputEvent>& inputEvents, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg[1];
    MsgArg* entries = new MsgArg[inputEvents.size()];
    int i=0;
    for (HidInterface::InputEvents::const_iterator citer = inputEvents.begin(); citer != inputEvents.end(); ++citer, i++) {
        entries[i].Set("(qqi)", citer->type, citer->code, citer->value);
    }
    arg[0].Set("a(qqi)", i, entries);

    status = m_proxyObject.MethodCall(GetInterfaceName().c_str(), s_method_InjectEvents.c_str(), arg, 1);
    delete[] entries;
    return status;
}

void HidIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_SupportedEvents.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_ARRAY) {
                const MsgArg* args = propValue->v_array.GetElements();
                size_t argsNum = propValue->v_array.GetNumElements();
                HidInterface::SupportedInputEvents supportedEvents;
                HidInterface::SupportedInputEvent supportedEvent;

                for(size_t i=0; i<argsNum; i++) {
                    uint16_t type, code;
                    int32_t min, max;
                    args[i].Get("(qqii)", &type, &code, &min, &max);

                    supportedEvent.type = type;
                    supportedEvent.code = code;
                    supportedEvent.min = min;
                    supportedEvent.max = max;
                    supportedEvents.push_back(supportedEvent);
                }
                m_interfaceListener.OnSupportedEventsChanged(obj.GetPath(), supportedEvents);
            }
        }
    }
}

void HidIntfControllerImpl::GetSupportedEventsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    MsgArg* arg = value.v_variant.val;
    if (!arg) {
        return;
    } else if (!arg->HasSignature("a(qqii)")) {
        return;
    }

    MsgArg* entries;
    size_t numEntries;
    HidInterface::SupportedInputEvents supportedEvents;
    HidInterface::SupportedInputEvent supportedEvent;
    arg->Get("a(qqii)", &numEntries, &entries);

    for (size_t i = 0; i < numEntries; ++i) {
        uint16_t type, code;
        int32_t min, max;
        entries[i].Get("(qqii)", &type, &code, &min, &max);

        supportedEvent.type = type;
        supportedEvent.code = code;
        supportedEvent.min = min;
        supportedEvent.max = max;
        supportedEvents.push_back(supportedEvent);
    }
    m_interfaceListener.OnResponseGetSupportedEvents(status, obj->GetPath(), supportedEvents, context);
}

} //namespace services
} //namespace ajn
