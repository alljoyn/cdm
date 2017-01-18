/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include "ChannelModel.h"
#include <interfaces/controllee/operation/ChannelIntfControllee.h>
#include "../../../Utils/HAL.h"

#include <interfaces/controllee/operation/ChannelIntfControllee.h>

namespace ajn {
namespace services {

template <>
struct Serializer<ChannelInterface::ChannelInfoRecord>
{
    Element* put(Element* parent, ChannelInterface::ChannelInfoRecord value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "channelID";
            sfield.elem = ser.put(nullptr, value.channelID);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "channelNumber";
            sfield.elem = ser.put(nullptr, value.channelNumber);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "channelName";
            sfield.elem = ser.put(nullptr, value.channelName);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    ChannelInterface::ChannelInfoRecord get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        ChannelInterface::ChannelInfoRecord result;
        auto fields = ser.get(element);
        if (fields.size() != 3) {
            throw SerializerError();
        }
        {
            auto& sfield = fields[0];
            if (sfield.name != "channelID")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.channelID = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "channelNumber")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.channelNumber = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
            if (sfield.name != "channelName")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.channelName = ser.get(sfield.elem);
        }
        return result;
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


ChannelModel::ChannelModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus ChannelModel::GetChannelId(qcc::String& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Channel", "ChannelId", out);
}

QStatus ChannelModel::SetChannelId(const qcc::String& value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Channel", "ChannelId", value);
}

QStatus ChannelModel::GetTotalNumberOfChannels(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Channel", "TotalNumberOfChannels", out);
}

QStatus ChannelModel::GetChannelList(uint16_t arg_startingRecord, uint16_t arg_numRecords, std::vector<ChannelInterface::ChannelInfoRecord>& arg_listOfChannelInfoRecords, ErrorCode& error, CdmControllee& controllee)
{
    std::vector<ChannelInterface::ChannelInfoRecord> channels;

    auto status = HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Channel", "__ChannelList", channels);

    if (status != ER_OK) {
        error = FEATURE_NOT_AVAILABLE;
        return status;
    }

    if (arg_startingRecord >= channels.size()) {
        error = INVALID_VALUE;
    } else {
        for (auto i = arg_startingRecord; i < arg_startingRecord + arg_numRecords && i < channels.size(); ++i) {
            arg_listOfChannelInfoRecords.push_back(channels[i]);
        }
    }

    return ER_OK;
}



QStatus HandleChannelCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Operation.Channel") {
        if (cmd.property == "ChannelId") {
            qcc::String value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<ChannelIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.Channel");
                if (iface) {
                    iface->EmitChannelIdChanged(value);
                }
            }
        }
        if (cmd.property == "TotalNumberOfChannels") {
            uint16_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<ChannelIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.Channel");
                if (iface) {
                    iface->EmitTotalNumberOfChannelsChanged(value);
                }
            }
        }
    }

    return status;
}


} // namespace emulator
} // namespace services
} // namespace ajn
