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

#include "ClimateControlModeModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<ClimateControlModeInterface::Mode>
{
    Element* put(Element* parent, ClimateControlModeInterface::Mode value)
    {
        Serializer<uint16_t> ser;
        return ser.put(parent, value);
    }


    ClimateControlModeInterface::Mode get(Element* element)
    {
        Serializer<uint16_t> ser;
        return static_cast<ClimateControlModeInterface::Mode>(ser.get(element));
    }
};

template <>
struct Serializer<ClimateControlModeInterface::OperationalState>
{
    Element* put(Element* parent, ClimateControlModeInterface::OperationalState value)
    {
        Serializer<uint16_t> ser;
        return ser.put(parent, value);
    }


    ClimateControlModeInterface::OperationalState get(Element* element)
    {
        Serializer<uint16_t> ser;
        return static_cast<ClimateControlModeInterface::OperationalState>(ser.get(element));
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


ClimateControlModeModel::ClimateControlModeModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus ClimateControlModeModel::GetMode(ClimateControlModeInterface::Mode& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "Mode", out);
}

QStatus ClimateControlModeModel::SetMode(const ClimateControlModeInterface::Mode value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "Mode", value);
}

QStatus ClimateControlModeModel::GetSupportedModes(std::vector<ClimateControlModeInterface::Mode>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "SupportedModes", out);
}

QStatus ClimateControlModeModel::GetOperationalState(ClimateControlModeInterface::OperationalState& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "OperationalState", out);
}

} // namespace emulator
} // namespace services
} // namespace ajn
