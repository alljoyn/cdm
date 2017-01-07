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

#include "HidModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<HidInterface::InputEvent>
{
    Element* put(Element* parent, HidInterface::InputEvent value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "type";
            sfield.elem = ser.put(nullptr, value.type);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "code";
            sfield.elem = ser.put(nullptr, value.code);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<int32_t> ser;
            sfield.name = "value";
            sfield.elem = ser.put(nullptr, value.value);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    HidInterface::InputEvent get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        HidInterface::InputEvent result;
        auto fields = ser.get(element);
        if (fields.size() != 3) {
            throw SerializerError();
        }
        {
            auto& sfield = fields[0];
            if (sfield.name != "type")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.type = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "code")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.code = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
            if (sfield.name != "value")
            {
                throw SerializerError();
            }
            Serializer<int32_t> ser;
            result.value = ser.get(sfield.elem);
        }
        return result;
    }
};

template <>
struct Serializer<HidInterface::SupportedInputEvent>
{
    Element* put(Element* parent, HidInterface::SupportedInputEvent value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "type";
            sfield.elem = ser.put(nullptr, value.type);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<uint16_t> ser;
            sfield.name = "code";
            sfield.elem = ser.put(nullptr, value.code);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<int32_t> ser;
            sfield.name = "min";
            sfield.elem = ser.put(nullptr, value.min);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<int32_t> ser;
            sfield.name = "max";
            sfield.elem = ser.put(nullptr, value.max);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    HidInterface::SupportedInputEvent get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        HidInterface::SupportedInputEvent result;
        auto fields = ser.get(element);
        if (fields.size() != 4) {
            throw SerializerError();
        }
        {
            auto& sfield = fields[0];
            if (sfield.name != "type")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.type = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "code")
            {
                throw SerializerError();
            }
            Serializer<uint16_t> ser;
            result.code = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
            if (sfield.name != "min")
            {
                throw SerializerError();
            }
            Serializer<int32_t> ser;
            result.min = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[3];
            if (sfield.name != "max")
            {
                throw SerializerError();
            }
            Serializer<int32_t> ser;
            result.max = ser.get(sfield.elem);
        }
        return result;
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


HidModel::HidModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus HidModel::GetSupportedEvents(std::vector<HidInterface::SupportedInputEvent>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.Input.Hid", "SupportedEvents", out);
}

QStatus HidModel::InjectEvents(std::vector<HidInterface::InputEvent>& arg_inputEvents, ErrorCode& error, CdmControllee& controllee)
{
    return ER_OK;
}

} // namespace emulator
} // namespace services
} // namespace ajn
