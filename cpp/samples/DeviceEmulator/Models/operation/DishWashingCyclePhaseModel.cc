/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "DishWashingCyclePhaseModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>
{
    Element* put(Element* parent, DishWashingCyclePhaseInterface::CyclePhaseDescriptor value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<uint8_t> ser;
            sfield.name = "phase";
            sfield.elem = ser.put(nullptr, value.phase);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "name";
            sfield.elem = ser.put(nullptr, value.name);
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


    DishWashingCyclePhaseInterface::CyclePhaseDescriptor get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        DishWashingCyclePhaseInterface::CyclePhaseDescriptor result;
        auto fields = ser.get(element);
        if (fields.size() != 3) {
            throw SerializerError();
        }
        {
            auto& sfield = fields[0];
            if (sfield.name != "phase")
            {
                throw SerializerError();
            }
            Serializer<uint8_t> ser;
            result.phase = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "name")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.name = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
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

static std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor> s_phases = {
    // phase name description
    {1,   "fill",    "Fill with water"},
    {2,   "wash",    "Wash the dishes"},
    {3,   "dry",     "Dry the dishes"}
};

DishWashingCyclePhaseModel::DishWashingCyclePhaseModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus DishWashingCyclePhaseModel::GetCyclePhase(uint8_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "CyclePhase", out);
}

QStatus DishWashingCyclePhaseModel::GetSupportedCyclePhases(std::vector<uint8_t>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "SupportedCyclePhases", out);
}

QStatus DishWashingCyclePhaseModel::GetVendorPhasesDescription(qcc::String& arg_languageTag, std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& arg_phasesDescription, ErrorCode& error, CdmControllee& controllee)
{
    arg_phasesDescription = s_phases;
    return ER_OK;
}

} // namespace emulator
} // namespace services
} // namespace ajn