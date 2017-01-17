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

#include "FanSpeedLevelModel.h"
#include <interfaces/controllee/operation/FanSpeedLevelIntfControllee.h>
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<FanSpeedLevelInterface::AutoMode>
{
    Element* put(Element* parent, FanSpeedLevelInterface::AutoMode value)
    {
        Serializer<uint8_t> ser;
        return ser.put(parent, value);
    }


    FanSpeedLevelInterface::AutoMode get(Element* element)
    {
        Serializer<uint8_t> ser;
        return static_cast<FanSpeedLevelInterface::AutoMode>(ser.get(element));
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


FanSpeedLevelModel::FanSpeedLevelModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus FanSpeedLevelModel::GetFanSpeedLevel(uint8_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", "FanSpeedLevel", out);
}

QStatus FanSpeedLevelModel::SetFanSpeedLevel(const uint8_t value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", "FanSpeedLevel", value);
}

QStatus FanSpeedLevelModel::GetMaxFanSpeedLevel(uint8_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", "MaxFanSpeedLevel", out);
}

QStatus FanSpeedLevelModel::GetAutoMode(FanSpeedLevelInterface::AutoMode& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", "AutoMode", out);
}

QStatus FanSpeedLevelModel::SetAutoMode(const FanSpeedLevelInterface::AutoMode value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", "AutoMode", value);
}



QStatus HandleFanSpeedLevelCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel") {
        if (cmd.property == "FanSpeedLevel") {
            uint8_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<FanSpeedLevelIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel");
                if (iface) {
                    iface->EmitFanSpeedLevelChanged(value);
                }
            }
        }
        if (cmd.property == "AutoMode") {
            FanSpeedLevelInterface::AutoMode value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<FanSpeedLevelIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.FanSpeedLevel");
                if (iface) {
                    iface->EmitAutoModeChanged(value);
                }
            }
        }
    }

    return status;
}


} // namespace emulator
} // namespace services
} // namespace ajn
