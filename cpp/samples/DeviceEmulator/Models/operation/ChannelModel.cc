/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "ChannelModel.h"
#include "../../../Utils/HAL.h"

#include "Commands.h"
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

// A static list of channels
static std::vector<ChannelInterface::ChannelInfoRecord> s_channels = {
    // channelID channelNumber channelName
    {"a",   "1",    "Hobbit News"},
    {"b",   "2",    "Shire Shopping Network"}
};

static const char* BusPath = "/CDM/Channel";

static bool ChannelCommand(const std::string& key, const StringVec& args, CdmControllee& controllee)
{
    bool ok = false;

    if (args.size() >= 1)
    {
        if (args[0] == "signal")
        {
            if (auto iface = controllee.GetInterface<ChannelIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Channel"))
            {
                iface->EmitChannelListChanged();
                ok = true;
            }
        }
    }

    return ok;
}

static bool s_subscribed = Commands::Instance().Subscribe("channel", ChannelCommand, "channel signal");


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
    if (arg_startingRecord >= s_channels.size())
    {
        error = INVALID_VALUE;
    }
    else
    {
        for (auto i = arg_startingRecord; i < arg_startingRecord + arg_numRecords && i < s_channels.size(); ++i)
        {
            arg_listOfChannelInfoRecords.push_back(s_channels[i]);
        }
    }

    return ER_OK;
}

} // namespace emulator
} // namespace services
} // namespace ajn