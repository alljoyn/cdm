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
#include <alljoyn/cdm/CdmProxyBusObject.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfControllerListener.h>

#include "LaundryCyclePhaseIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* LaundryCyclePhaseIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new LaundryCyclePhaseIntfControllerImpl(busAttachment, dynamic_cast<LaundryCyclePhaseIntfControllerListener&>(listener), cdmProxyObject);
}

LaundryCyclePhaseIntfControllerImpl::LaundryCyclePhaseIntfControllerImpl(BusAttachment& busAttachment, LaundryCyclePhaseIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

LaundryCyclePhaseIntfControllerImpl::~LaundryCyclePhaseIntfControllerImpl()
{
}

QStatus LaundryCyclePhaseIntfControllerImpl::Init()
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

void LaundryCyclePhaseIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i)
    {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_CyclePhase.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_BYTE)
            {
                LaundryCyclePhaseInterface::LaundryCyclePhase cyclePhase = (LaundryCyclePhaseInterface::LaundryCyclePhase)propValue->v_byte;
                m_interfaceListener.OnCyclePhaseChanged(obj.GetPath(), cyclePhase);
            }
        }
        else if (!s_prop_SupportedCyclePhases.compare(propNameStr))
        {
            if (propValue->typeId == ALLJOYN_BYTE_ARRAY)
            {
                LaundryCyclePhaseInterface::SupportedCyclePhases supportedCyclePhases;
                uint8_t *vals;
                size_t numVals;
                propValue->Get("ay", &numVals, &vals);

                for (size_t i = 0; i < numVals; ++i)
                    supportedCyclePhases.push_back((LaundryCyclePhaseInterface::LaundryCyclePhase)vals[i]);
                m_interfaceListener.OnSupportedCyclePhasesChanged(obj.GetPath(), supportedCyclePhases);
            }
        }
    }
}
QStatus LaundryCyclePhaseIntfControllerImpl::GetCyclePhase(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_CyclePhase.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&LaundryCyclePhaseIntfControllerImpl::GetCyclePhasePropertyCB,context);

    return status;

}

QStatus LaundryCyclePhaseIntfControllerImpl::GetSupportedCyclePhases(void* context )
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(),s_prop_SupportedCyclePhases.c_str(),this,(ProxyBusObject::Listener::GetPropertyCB)&LaundryCyclePhaseIntfControllerImpl::GetSupportedCyclePhasesPropertyCB,context);

    return status;
}

QStatus LaundryCyclePhaseIntfControllerImpl::GetVendorPhasesDescription(const qcc::String& language, void* context)
{
    QStatus status = ER_OK;

    MsgArg args[1];
    args[0].typeId = ALLJOYN_STRING;
    args[0].v_string.str = language.c_str();
    args[0].v_string.len = language.size();

    status = m_proxyObject.MethodCallAsync(GetInterfaceName().c_str(), s_method_GetVendorPhasesDescription.c_str(), this, (MessageReceiver::ReplyHandler)&LaundryCyclePhaseIntfControllerImpl::GetCyclePhasesDescriptionReplyHandler, args, 1, context);

    return status;
}

void LaundryCyclePhaseIntfControllerImpl::GetCyclePhasePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    uint8_t cyclePhase;
    value.Get("y", &cyclePhase);

    m_interfaceListener.OnResponseGetCyclePhase(status, obj->GetPath(), (LaundryCyclePhase)cyclePhase, context);
}
void LaundryCyclePhaseIntfControllerImpl::GetSupportedCyclePhasesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }
    uint8_t *vals;
    size_t numVals;
    value.Get("ay", &numVals, &vals);

    SupportedCyclePhases cyclePhases;
    for (size_t i = 0; i < numVals; ++i)
        cyclePhases.push_back((LaundryCyclePhase)vals[i]);

    m_interfaceListener.OnResponseGetSupportedCyclePhases(status, obj->GetPath(), cyclePhases, context);

}

void LaundryCyclePhaseIntfControllerImpl::GetCyclePhasesDescriptionReplyHandler(Message& message, void* context)
{
    LaundryCyclePhaseInterface::CyclePhaseDescriptions descriptions;
    qcc::String errorMessage;
    const char* errorName = message->GetErrorName(&errorMessage);
    QStatus status = ER_OK;
    if (message->GetType() != MESSAGE_METHOD_RET)
    {
        status = ER_FAIL;
    }
    else
    {
        size_t numArgs;
        const MsgArg* args;
        message->GetArgs(numArgs, args);

        if (!args[0].HasSignature("a(yss)"))
        {
            return;
        }

        MsgArg* entries;
        size_t numEntries;
        LaundryCyclePhaseInterface::CyclePhaseDescriptor desc;

        args[0].Get("a(yss)", &numEntries, &entries);
        for (size_t i = 0; i < numEntries; ++i)
        {
            const char* phaseName, *phaseDesc;
            uint8_t phase;
            entries[i].Get("(yss)", &phase, &phaseName, &phaseDesc);
            desc.phase = (LaundryCyclePhase)phase;
            desc.name = String(phaseName);
            desc.description = String(phaseDesc);
            descriptions.push_back(desc);
        }
    }
    m_interfaceListener.OnResponseGetVendorPhasesDescription(status, m_proxyObject.GetPath(), descriptions, context, errorName, errorMessage.c_str());
}

} //namespace services
} //namespace ajn
