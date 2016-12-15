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

#include "WaterLevelModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<WaterLevelInterface::SupplySource>
{
    Element* put(Element* parent, WaterLevelInterface::SupplySource value)
    {
        Serializer<int32_t> ser;
        return ser.put(parent, value);
    }


    WaterLevelInterface::SupplySource get(Element* element)
    {
        Serializer<int32_t> ser;
        return static_cast<WaterLevelInterface::SupplySource>(ser.get(element));
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


WaterLevelModel::WaterLevelModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus WaterLevelModel::GetSupplySource(WaterLevelInterface::SupplySource& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WaterLevel", "SupplySource", out);
}

QStatus WaterLevelModel::GetCurrentLevel(uint8_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WaterLevel", "CurrentLevel", out);
}

QStatus WaterLevelModel::GetMaxLevel(uint8_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WaterLevel", "MaxLevel", out);
}

} // namespace emulator
} // namespace services
} // namespace ajn