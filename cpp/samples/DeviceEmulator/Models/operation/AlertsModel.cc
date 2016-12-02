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

#include "AlertsModel.h"
#include "../../../Utils/HAL.h"

#include "Commands.h"
#include <algorithm>
#include <thread>
#include <sstream>

namespace ajn {
namespace services {

template <>
struct Serializer<AlertsInterface::Severity>
{
    Element* put(Element* parent, AlertsInterface::Severity value)
    {
        Serializer<int32_t> ser;
        return ser.put(parent, value);
    }


    AlertsInterface::Severity get(Element* element)
    {
        Serializer<int32_t> ser;
        return static_cast<AlertsInterface::Severity>(ser.get(element));
    }
};

template <>
struct Serializer<AlertsInterface::AlertRecord>
{
    Element* put(Element* parent, AlertsInterface::AlertRecord value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<AlertsInterface::Severity> ser;
            sfield.name = "severity";
            sfield.elem = ser.put(nullptr, value.severity);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "alertCode";
            sfield.elem = ser.put(nullptr, value.alertCode);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<bool> ser;
            sfield.name = "needAcknowledgement";
            sfield.elem = ser.put(nullptr, value.needAcknowledgement);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    AlertsInterface::AlertRecord get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        AlertsInterface::AlertRecord result;
        auto fields = ser.get(element);
        {
            auto& sfield = fields[0];
            if (sfield.name != "severity")
            {
                throw SerializerError();
            }
            Serializer<AlertsInterface::Severity> ser;
            result.severity = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "alertCode")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.alertCode = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
            if (sfield.name != "needAcknowledgement")
            {
                throw SerializerError();
            }
            Serializer<bool> ser;
            result.needAcknowledgement = ser.get(sfield.elem);
        }
        return result;
    }
};

template <>
struct Serializer<AlertsInterface::AlertCodesDescriptor>
{
    Element* put(Element* parent, AlertsInterface::AlertCodesDescriptor value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "alertCode";
            sfield.elem = ser.put(nullptr, value.alertCode);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "description";
            sfield.elem = ser.put(nullptr, value.description);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    AlertsInterface::AlertCodesDescriptor get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        AlertsInterface::AlertCodesDescriptor result;
        auto fields = ser.get(element);
        {
            auto& sfield = fields[0];
            if (sfield.name != "alertCode")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.alertCode = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "description")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.description = ser.get(sfield.elem);
        }
        return result;
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {

static std::vector<AlertsInterface::AlertCodesDescriptor> s_descriptions = {
    // alertCode description
    {1,   "bad",    },
    {2,   "worse"   },
    {3,   "stuffed" }
};

using MutLock = std::lock_guard<std::mutex>;

static std::vector<uint16_t> s_alerts;
static std::mutex s_alertsMutex;

static bool AlertCommand(const std::string& key, const StringVec& args)
{
    bool ok = false;

    if (args.size() == 2)
    {
        if (args[0] == "alert")
        {
            std::istringstream strm(args[1]);
            uint16_t a;
            strm >> a;
            ok = true;
            MutLock lock(s_alertsMutex);
            s_alerts.push_back(a);
        }
    }

    return ok;
}

static bool s_subscribed = Commands::Instance().Subscribe("alert", AlertCommand, "alert args");


AlertsModel::AlertsModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus AlertsModel::GetAlerts(std::vector<AlertRecord>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", out);
}

QStatus AlertsModel::GetAlertCodesDescription(qcc::String arg_languageTag, std::vector<AlertCodesDescriptor>& arg_description, ErrorCode& error, CdmSideEffects& sideEffects)
{
    arg_description = s_descriptions;
    return ER_OK;
}

QStatus AlertsModel::AcknowledgeAlert(uint16_t arg_alertCode, ErrorCode& error, CdmSideEffects& sideEffects)
{
    MutLock lock(s_alertsMutex);
    s_alerts.erase(std::remove(s_alerts.begin(), s_alerts.end(), arg_alertCode));
    return ER_OK;
}

QStatus AlertsModel::AcknowledgeAllAlerts(ErrorCode& error, CdmSideEffects& sideEffects)
{
    MutLock lock(s_alertsMutex);
    s_alerts.clear();
    return ER_OK;
}

} // namespace emulator
} // namespace services
} // namespace ajn
