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

#include "AudioVideoInputModel.h"
#include <interfaces/controllee/operation/AudioVideoInputIntfControllee.h>
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<AudioVideoInputInterface::SourceType>
{
    Element* put(Element* parent, AudioVideoInputInterface::SourceType value)
    {
        Serializer<uint16_t> ser;
        return ser.put(parent, value);
    }


    AudioVideoInputInterface::SourceType get(Element* element)
    {
        Serializer<uint16_t> ser;
        return static_cast<AudioVideoInputInterface::SourceType>(ser.get(element));
    }
};

template <>
struct Serializer<AudioVideoInputInterface::SignalPresence>
{
    Element* put(Element* parent, AudioVideoInputInterface::SignalPresence value)
    {
        Serializer<uint8_t> ser;
        return ser.put(parent, value);
    }


    AudioVideoInputInterface::SignalPresence get(Element* element)
    {
        Serializer<uint8_t> ser;
        return static_cast<AudioVideoInputInterface::SignalPresence>(ser.get(element));
    }
};

template <>
struct Serializer<AudioVideoInputInterface::InputSource>
{
    Element* put(Element* parent, AudioVideoInputInterface::InputSource value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "id";
            sfield.elem = ser.put(nullptr, value.id);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<AudioVideoInputInterface::SourceType> ser;
            sfield.name = "sourceType";
            sfield.elem = ser.put(nullptr, value.sourceType);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<AudioVideoInputInterface::SignalPresence> ser;
            sfield.name = "signalPresence";
            sfield.elem = ser.put(nullptr, value.signalPresence);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "portNumber";
            sfield.elem = ser.put(nullptr, value.portNumber);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "friendlyName";
            sfield.elem = ser.put(nullptr, value.friendlyName);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    AudioVideoInputInterface::InputSource get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        AudioVideoInputInterface::InputSource result;
        auto fields = ser.get(element);
        if (fields.size() != 5) {
            throw SerializerError();
        }
        {
            auto& sfield = fields[0];
            if (sfield.name != "id")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.id = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "sourceType")
            {
                throw SerializerError();
            }
            Serializer<AudioVideoInputInterface::SourceType> ser;
            result.sourceType = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
            if (sfield.name != "signalPresence")
            {
                throw SerializerError();
            }
            Serializer<AudioVideoInputInterface::SignalPresence> ser;
            result.signalPresence = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[3];
            if (sfield.name != "portNumber")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.portNumber = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[4];
            if (sfield.name != "friendlyName")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.friendlyName = ser.get(sfield.elem);
        }
        return result;
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


AudioVideoInputModel::AudioVideoInputModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus AudioVideoInputModel::GetInputSourceId(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", "InputSourceId", out);
}

QStatus AudioVideoInputModel::SetInputSourceId(const uint16_t value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", "InputSourceId", value);
}

QStatus AudioVideoInputModel::GetSupportedInputSources(std::vector<AudioVideoInputInterface::InputSource>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", "SupportedInputSources", out);
}



QStatus HandleAudioVideoInputCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Operation.AudioVideoInput") {
        if (cmd.property == "InputSourceId") {
            uint16_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<AudioVideoInputIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput");
                if (iface) {
                    iface->EmitInputSourceIdChanged(value);
                }
            }
        }
        if (cmd.property == "SupportedInputSources") {
            std::vector<AudioVideoInputInterface::InputSource> value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<AudioVideoInputIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput");
                if (iface) {
                    iface->EmitSupportedInputSourcesChanged(value);
                }
            }
        }
    }

    return status;
}


} // namespace emulator
} // namespace services
} // namespace ajn
