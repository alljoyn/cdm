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
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControllerListener.h>

#include "LanguageDisplayIntfControllerImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* LanguageDisplayIntfControllerImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject)
{
    return new LanguageDisplayIntfControllerImpl(busAttachment, dynamic_cast<LanguageDisplayIntfControllerListener&>(listener), cdmProxyObject);
}

LanguageDisplayIntfControllerImpl::LanguageDisplayIntfControllerImpl(BusAttachment& busAttachment, LanguageDisplayIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject) :
    InterfaceController(cdmProxyObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener)
{
}

LanguageDisplayIntfControllerImpl::~LanguageDisplayIntfControllerImpl()
{
}

QStatus LanguageDisplayIntfControllerImpl::Init()
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

void LanguageDisplayIntfControllerImpl::PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context)
{
    MsgArg* entries;
    size_t numEntries;

    changed.Get("a{sv}", &numEntries, &entries);
    for (size_t i = 0; i < numEntries; ++i) {
        const char* propName;
        MsgArg* propValue;
        entries[i].Get("{sv}", &propName, &propValue);
        String propNameStr(propName);

        if (!s_prop_DisplayLanguage.compare(propNameStr)) {
            if (propValue->typeId == ALLJOYN_STRING) {
                String displayLanguage(propValue->v_string.str);
                m_interfaceListener.DisplayLanguagePropertyChanged(obj.GetPath(), displayLanguage);
            }
        } else if(!s_prop_SupportedDisplayLanguages.compare(propNameStr)) {
            qcc::String *vals;
            size_t numVals;
            std::vector<qcc::String> supportedDisplayLanguages;
            propValue->Get("as", &numVals, &vals);

            cout << "supported languages: " << endl;
            for (size_t i = 0; i < numVals; ++i) {
                supportedDisplayLanguages.push_back(String(vals[i]));
            }
            m_interfaceListener.SupportedDisplayLanguagesPropertyChanged(obj.GetPath(), supportedDisplayLanguages);
        }
    }
}


QStatus LanguageDisplayIntfControllerImpl::GetDisplayLanguage(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_DisplayLanguage.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&LanguageDisplayIntfControllerImpl::GetDisplayLanguagePropertyCB,context);

    return status;

}
QStatus LanguageDisplayIntfControllerImpl::SetDisplayLanguage(const qcc::String& displayLanguage, void* context)
{
    QStatus status = ER_OK;

    MsgArg arg;
    arg.Set("s", displayLanguage.c_str());
    arg.Stabilize();
    status = m_proxyObject.SetPropertyAsync(GetInterfaceName().c_str(), s_prop_DisplayLanguage.c_str(), arg, this, (ProxyBusObject::Listener::SetPropertyCB)&LanguageDisplayIntfControllerImpl::SetDisplayLanguagePropertyCB,context);

    return status;
}
QStatus LanguageDisplayIntfControllerImpl::GetSupportedDisplayLanguages(void* context)
{
    QStatus status = ER_OK;

    status = m_proxyObject.GetPropertyAsync(GetInterfaceName().c_str(), s_prop_SupportedDisplayLanguages.c_str(), this, (ProxyBusObject::Listener::GetPropertyCB)&LanguageDisplayIntfControllerImpl::GetSupportedDisplayLanguagesPropertyCB,context);

    return status;
}

void LanguageDisplayIntfControllerImpl::GetDisplayLanguagePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj) {
        return;
    }

    const char* lang;
    value.Get("s", &lang);
    qcc::String displayLanguage(lang);

    m_interfaceListener.GetDisplayLanguagePropertyCallback(status,obj->GetPath(),displayLanguage,context);
}
void LanguageDisplayIntfControllerImpl::SetDisplayLanguagePropertyCB(QStatus status, ProxyBusObject* obj, void* context)
{
    if(!obj){
        return;
    }
    m_interfaceListener.SetDisplayLanguagePropertyCallback(status,obj->GetPath(),context);

}
void LanguageDisplayIntfControllerImpl::GetSupportedDisplayLanguagesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context)
{
    if(!obj){
        return;
    }

    MsgArg* vals;
    size_t numVals;
    std::vector<qcc::String> supportedDisplayLanguages;
    value.Get("as", &numVals, &vals);

    cout << "Supported display languages units: " << endl;
    for (size_t i = 0; i < numVals; ++i) {
        const char* lang;
        vals[i].Get("s", &lang);
        supportedDisplayLanguages.push_back(qcc::String(lang));
    }

    m_interfaceListener.GetSupportedDisplayLanguagesPropertyCallback(status,obj->GetPath(), supportedDisplayLanguages, context);
}

} //namespace services
} //namespace ajn
