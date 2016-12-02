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
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllerListener.h>

#include "CycleControlIntfControllerImpl.h"


using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* CycleControlIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& cdmProxyObject)
{
    return new CycleControlIntfControllerImpl(busAttachment, dynamic_cast<CycleControlIntfControllerListener&>(listener), cdmProxyObject);
}

CycleControlIntfControllerImpl::CycleControlIntfControllerImpl(BusAttachment& busAttachment, CycleControlIntfControllerListener& listener, ProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

CycleControlIntfControllerImpl::~CycleControlIntfControllerImpl()
{
}

QStatus CycleControlIntfControllerImpl::Init()
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

QStatus CycleControlIntfControllerImpl::GetOperationalState(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_OperationalState.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CycleControlIntfControllerImpl::GetOperationalStatePropertyCB, context);

    return status;
}

QStatus CycleControlIntfControllerImpl::GetSupportedOperationalStates(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedOperationalStates.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CycleControlIntfControllerImpl::GetSupportedOperationalStatesPropertyCB, context);

    cout << "Get SUpported operational states. Status = " << status<<endl;
    return status;
}

QStatus CycleControlIntfControllerImpl::GetSupportedOperationalCommands(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedOperationalCommands.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&CycleControlIntfControllerImpl::GetSupportedOperationalCommandsPropertyCB, context);

    cout << "Get SUpported operational commands. Status = " << status<<endl;
    return status;
}

QStatus CycleControlIntfControllerImpl::ExecuteOperationalCommand(const OperationalCommands command, void* context)
{
    MsgArg args[1];
    args[0].Set("y", (uint8_t)command);

    QStatus status = ER_OK;
    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_ExecuteOperationalCommand.c_str(), this, (MessageReceiver::ReplyHandler)&CycleControlIntfControllerImpl::ExecuteOperationalCommandReplyHandler, args, 1, context);
    return status;
}

void CycleControlIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_OperationalState.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_BYTE) {
                uint8_t state = propValue->v_byte;
                m_interfaceListener.OnOperationalStateChanged(obj.GetPath(), (OperationalState) state);
            }
        }
        else if(!s_prop_SupportedOperationalCommands.compare(propNameStr)) {
            if(propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                SupportedOperationalCommands commands;
                for (size_t i = 0; i < numVals; ++i)
                    commands.push_back((OperationalCommands)vals[i]);
                m_interfaceListener.OnSupportedOperationalCommandsChanged(obj.GetPath(), commands);
            }
        }
        else if (!s_prop_SupportedOperationalStates.compare(propNameStr)) {
            if(propValue->typeId == ALLJOYN_BYTE_ARRAY) {
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                SupportedOperationalStates states;
                for (size_t i = 0; i < numVals; ++i)
                    states.push_back((OperationalState)vals[i]);
                m_interfaceListener.OnSupportedOperationalStatesChanged(obj.GetPath(), states);
            }
        }
    }
}

void CycleControlIntfControllerImpl::GetOperationalStatePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }

    uint8_t state;
    value.Get("y", &state);

    m_interfaceListener.OnResponseGetOperationalState(status, obj->GetPath(), (OperationalState) state, context);
}

void CycleControlIntfControllerImpl::GetSupportedOperationalStatesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    SupportedOperationalStates states;
    for (size_t i = 0; i < numVals; ++i) {
        states.push_back((OperationalState)vals[i]);
    }
    m_interfaceListener.OnResponseGetSupportedOperationalStates(status, obj->GetPath(), states, context);
}

void CycleControlIntfControllerImpl::GetSupportedOperationalCommandsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if (!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    SupportedOperationalCommands commands;
    for (size_t i = 0; i < numVals; ++i)
        commands.push_back((OperationalCommands)vals[i]);

    m_interfaceListener.OnResponseGetSupportedOperationalCommands(status, obj->GetPath(), commands, context);
}

void CycleControlIntfControllerImpl::ExecuteOperationalCommandReplyHandler(Message& message, void* context)
{
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET) {
        status = ER_FAIL;
    }
    m_interfaceListener.OnResponseExecuteOperationalCommand(status, m_proxyObject.GetPath(), context,
                                                            errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn
