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

#include <alljoyn/cdm/LogModule.h>
#include <alljoyn/cdm/CdmBusObject.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControlleeListener.h>

#include "FilterStatusIntfControlleeImpl.h"

using namespace qcc;
using namespace std;

namespace ajn {
namespace services {

CdmInterface* FilterStatusIntfControlleeImpl::CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject)
{
    return new FilterStatusIntfControlleeImpl(busAttachment, dynamic_cast<FilterStatusIntfControlleeListener&>(listener), cdmBusObject);
}

FilterStatusIntfControlleeImpl::FilterStatusIntfControlleeImpl(BusAttachment& busAttachment, FilterStatusIntfControlleeListener& listener, CdmBusObject& cdmBusObject) :
    InterfaceControllee(cdmBusObject),
    m_busAttachment(busAttachment),
    m_interfaceListener(listener),
    m_expectedLifeInDays(0),
    m_isCleanable(false),
    m_orderPercentage(0),
    m_lifeRemaining(0),
    m_manufacturerInit(false),
    m_partNumberInit(false),
    m_urlInit(false)
{
}

FilterStatusIntfControlleeImpl::~FilterStatusIntfControlleeImpl()
{
}

QStatus FilterStatusIntfControlleeImpl::Init()
{
    QStatus status = CdmInterface::Init();

    return status;
}

QStatus FilterStatusIntfControlleeImpl::OnGetProperty(const String& propName, MsgArg& val)
{
    QStatus status = ER_OK;

    if (!(s_prop_Version.compare(propName))) {
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = GetInterfaceVersion();
    } else {
        if (s_retrievingActualPropertyValue) {
            if (!(s_prop_ExpectedLifeInDays.compare(propName))) {
                uint16_t value;
                status = m_interfaceListener.OnGetExpectedLifeInDays(value);
                if (status != ER_OK) {
                    value = GetExpectedLifeInDays();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                   SetExpectedLifeInDays(value);
                }

                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_IsCleanable.compare(propName))) {
                bool isCleanable;
                status = m_interfaceListener.OnGetIsCleanable(isCleanable);
                if (status != ER_OK) {
                    isCleanable = GetIsCleanable();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetIsCleanable(isCleanable);
                }

                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = isCleanable;
            } else if (!(s_prop_OrderPercentage.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetLifeRemaining(value);
                if (status != ER_OK) {
                    value = GetLifeRemaining();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetLifeRemaining(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_Manufacturer.compare(propName))) {
                qcc::String manufacturer;
                status = m_interfaceListener.OnGetManufacturer(manufacturer);
                if (status != ER_OK) {
                    manufacturer = GetManufacturer();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetManufacturer(manufacturer);
                }

                status = val.Set("s", manufacturer.c_str());
                if(status != ER_OK){
                    QCC_LogError(status, ("%s: failed to set return value ", __func__));
                }
                val.Stabilize();

            } else if (!(s_prop_PartNumber.compare(propName))) {
                qcc::String partNumber;
                status = m_interfaceListener.OnGetPartNumber(partNumber);
                if (status != ER_OK) {
                    partNumber = GetPartNumber();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetPartNumber(partNumber);
                }

                status = val.Set("s", partNumber.c_str());
                if(status != ER_OK){
                    QCC_LogError(status, ("%s: failed to set return value ", __func__));
                }
                val.Stabilize();
            } else if (!(s_prop_Url.compare(propName))) {
                qcc::String url;
                status = m_interfaceListener.OnGetUrl(url);
                if (status != ER_OK) {
                    url = GetUrl();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetUrl(url);
                }

                status = val.Set("s", url.c_str());
                if(status != ER_OK){
                    QCC_LogError(status, ("%s: failed to set return value ", __func__));
                }
                val.Stabilize();
            } else if (!(s_prop_LifeRemaining.compare(propName))) {
                uint8_t value;
                status = m_interfaceListener.OnGetLifeRemaining(value);
                if (status != ER_OK) {
                    value = GetLifeRemaining();
                    QCC_LogError(status, ("%s: failed to get actual property value from application. use previous value.", __func__));
                    status = ER_OK;
                } else {
                    SetLifeRemaining(value);
                }

                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            }
        } else {
            if (!(s_prop_ExpectedLifeInDays.compare(propName))) {
                const uint16_t value = GetExpectedLifeInDays();
                val.typeId = ALLJOYN_UINT16;
                val.v_uint16 = value;
            } else if (!(s_prop_IsCleanable.compare(propName))) {
                const bool isCleanable = GetIsCleanable();
                val.typeId = ALLJOYN_BOOLEAN;
                val.v_bool = isCleanable;
            } else if (!(s_prop_OrderPercentage.compare(propName))) {
                const uint8_t value = GetOrderPercentage();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else if (!(s_prop_Manufacturer.compare(propName))) {
                const qcc::String manufacturer = GetManufacturer();
                status = val.Set("s", manufacturer.c_str());
                if(status != ER_OK){
                    QCC_LogError(status, ("%s: failed to set return value ", __func__));
                }
                val.Stabilize();
            } else if (!(s_prop_PartNumber.compare(propName))) {
                const qcc::String partNumber = GetPartNumber();
                status = val.Set("s", partNumber.c_str());
                if(status != ER_OK){
                    QCC_LogError(status, ("%s: failed to set return value ", __func__));
                }
                val.Stabilize();
            } else if (!(s_prop_Url.compare(propName))) {
                const qcc::String url = GetUrl();
                status = val.Set("s", url.c_str());
                if(status != ER_OK){
                    QCC_LogError(status, ("%s: failed to set return value ", __func__));
                }
                val.Stabilize();
            } else if (!(s_prop_LifeRemaining.compare(propName))) {
                const uint8_t value = GetLifeRemaining();
                val.typeId = ALLJOYN_BYTE;
                val.v_byte = value;
            } else {
                status = ER_BUS_NO_SUCH_PROPERTY;
            }
       }
    }

    return status;
}

QStatus FilterStatusIntfControlleeImpl::OnSetProperty(const String& propName, MsgArg& val)
{
    return ER_BUS_NO_SUCH_PROPERTY;
}

void FilterStatusIntfControlleeImpl::OnMethodHandler(const InterfaceDescription::Member* member, Message& msg)
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
        QCC_LogError(status, ("%s: could not find method handler.", __func__));
        m_busObject.ReplyMethodCall(msg, status);
    }
}

QStatus FilterStatusIntfControlleeImpl::SetExpectedLifeInDays(const uint16_t value)
{
    if (m_expectedLifeInDays != value) {
        MsgArg val;
        val.typeId = ALLJOYN_UINT16;
        val.v_uint16 = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_ExpectedLifeInDays.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_expectedLifeInDays = value;
    }

    return ER_OK;
}

QStatus FilterStatusIntfControlleeImpl::SetIsCleanable(const bool isCleanable)
{
    if (m_isCleanable != isCleanable) {
        MsgArg val;
        val.typeId = ALLJOYN_BOOLEAN;
        val.v_bool = isCleanable;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_IsCleanable.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_isCleanable = isCleanable;
    }

    return ER_OK;
}

QStatus FilterStatusIntfControlleeImpl::SetOrderPercentage(const uint8_t value)
{
    if (MIN_LIFE_REMAINING > value || (MAX_LIFE_REMAINING < value && value != NOT_APPLICABLE)) {
        QCC_LogError(ER_INVALID_DATA, ("%s: value is invalid.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_orderPercentage != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_OrderPercentage.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_orderPercentage = value;
    }

    return ER_OK;
}

QStatus FilterStatusIntfControlleeImpl::SetManufacturer(const qcc::String& manufacturer)
{
    if (m_manufacturerInit) {
        QCC_LogError(ER_FAIL, ("%s: Manufacturer is constant.", __func__));
        return ER_FAIL;
    }

    m_manufacturer = manufacturer;
    m_manufacturerInit = true;
    return ER_OK;
}

QStatus FilterStatusIntfControlleeImpl::SetPartNumber(const qcc::String& partNumber)
{
    if (m_partNumberInit) {
        QCC_LogError(ER_FAIL, ("%s: PartNumber is constant.", __func__));
        return ER_FAIL;
    }

    m_partNumber = partNumber;
    m_partNumberInit = true;
    return ER_OK;
}

QStatus FilterStatusIntfControlleeImpl::SetUrl(const qcc::String& url)
{
    if (m_urlInit) {
        QCC_LogError(ER_FAIL, ("%s: Url is constant.", __func__));
        return ER_FAIL;
    }

    m_url = url;
    m_urlInit = true;
    return ER_OK;
}

QStatus FilterStatusIntfControlleeImpl::SetLifeRemaining(const uint8_t value)
{
    if (MIN_LIFE_REMAINING > value || MAX_LIFE_REMAINING < value) {
        QCC_LogError(ER_INVALID_DATA, ("%s: value is invalid.", __func__));
        return ER_INVALID_DATA;
    }

    if (m_lifeRemaining != value) {
        MsgArg val;
        val.typeId = ALLJOYN_BYTE;
        val.v_byte = value;
        m_busObject.EmitPropChanged(GetInterfaceName().c_str(), s_prop_LifeRemaining.c_str(), val, SESSION_ID_ALL_HOSTED, ALLJOYN_FLAG_GLOBAL_BROADCAST);
        m_lifeRemaining = value;
    }

    return ER_OK;
}

} //namespace services
} //namespace ajn
