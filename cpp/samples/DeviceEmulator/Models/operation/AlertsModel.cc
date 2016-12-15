/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "AlertsModel.h"
#include "../../../Utils/HAL.h"

#include "Commands.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <interfaces/controllee/operation/AlertsIntfControllee.h>

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
        if (fields.size() != 3) {
            throw SerializerError();
        }
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
        if (fields.size() != 2) {
            throw SerializerError();
        }
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

static const char* BusPath = "/CDM/Alerts";

static bool AlertCommand(const std::string& key, const StringVec& args, CdmControllee& controllee)
{
    bool ok = false;

    if (args.size() >= 1 && args[0] == "show")
    {
        std::vector<AlertsInterface::AlertRecord> alerts;
        HAL::ReadProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);
        ok = true;

        for (auto& alert : alerts)
        {
            std::cout << "severity " << alert.severity << ", code " << alert.alertCode << "\n";
        }
    }
    else
    if (args.size() >= 2)
    {
        AlertsInterface::Severity severity = AlertsInterface::SEVERITY_WARNING;
        uint16_t code = 0;

        if (args[0] == "w" || args[0] == "warning")
        {
            severity = AlertsInterface::SEVERITY_WARNING;
        }
        else
        if (args[0] == "a" || args[0] == "alarm")
        {
            severity = AlertsInterface::SEVERITY_ALARM;
        }
        else
        if (args[0] == "f" || args[0] == "fault")
        {
            severity = AlertsInterface::SEVERITY_FAULT;
        }

        {
            std::istringstream strm(args[1]);
            strm >> code;
        }

        ok = true;

        std::vector<AlertsInterface::AlertRecord> alerts;
        HAL::ReadProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

        AlertsInterface::AlertRecord record;

        record.severity = severity;
        record.alertCode = code;
        record.needAcknowledgement = true;

        alerts.push_back(record);
        HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

        if (auto iface = controllee.GetInterface<AlertsIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts"))
        {
            iface->EmitAlertsChanged(alerts);
        }
    }

    return ok;
}

static bool s_subscribed = Commands::Instance().Subscribe("alert", AlertCommand, "alert args");


AlertsModel::AlertsModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus AlertsModel::GetAlerts(std::vector<AlertsInterface::AlertRecord>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", out);
}

QStatus AlertsModel::GetAlertCodesDescription(qcc::String& arg_languageTag, std::vector<AlertsInterface::AlertCodesDescriptor>& arg_description, ErrorCode& error, CdmControllee& controllee)
{
    arg_description = s_descriptions;
    return ER_OK;
}

QStatus AlertsModel::AcknowledgeAlert(uint16_t arg_alertCode, ErrorCode& error, CdmControllee& controllee)
{
    std::vector<AlertsInterface::AlertRecord> alerts;
    HAL::ReadProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);
    alerts.erase(std::remove_if(alerts.begin(), alerts.end(),
            [arg_alertCode](const AlertsInterface::AlertRecord& record){return record.alertCode == arg_alertCode;}),
            alerts.end()
            );
    HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

    auto iface = controllee.GetInterface<AlertsIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts");
    iface->EmitAlertsChanged(alerts);
    return ER_OK;
}

QStatus AlertsModel::AcknowledgeAllAlerts(ErrorCode& error, CdmControllee& controllee)
{
    std::vector<AlertsInterface::AlertRecord> empty;
    HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", empty);

    auto iface = controllee.GetInterface<AlertsIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts");
    iface->EmitAlertsChanged(empty);
    return ER_OK;
}

} // namespace emulator
} // namespace services
} // namespace ajn