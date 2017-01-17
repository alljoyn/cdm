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

#include "WindDirectionModel.h"
#include <interfaces/controllee/environment/WindDirectionIntfControllee.h>
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<WindDirectionInterface::AutoMode>
{
    Element* put(Element* parent, WindDirectionInterface::AutoMode value)
    {
        Serializer<uint8_t> ser;
        return ser.put(parent, value);
    }


    WindDirectionInterface::AutoMode get(Element* element)
    {
        Serializer<uint8_t> ser;
        return static_cast<WindDirectionInterface::AutoMode>(ser.get(element));
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


WindDirectionModel::WindDirectionModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus WindDirectionModel::GetHorizontalDirection(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalDirection", out);
}

QStatus WindDirectionModel::SetHorizontalDirection(const uint16_t value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalDirection", value);
}

QStatus WindDirectionModel::GetHorizontalMax(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalMax", out);
}

QStatus WindDirectionModel::GetHorizontalAutoMode(WindDirectionInterface::AutoMode& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalAutoMode", out);
}

QStatus WindDirectionModel::SetHorizontalAutoMode(const WindDirectionInterface::AutoMode value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalAutoMode", value);
}

QStatus WindDirectionModel::GetVerticalDirection(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalDirection", out);
}

QStatus WindDirectionModel::SetVerticalDirection(const uint16_t value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalDirection", value);
}

QStatus WindDirectionModel::GetVerticalMax(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalMax", out);
}

QStatus WindDirectionModel::GetVerticalAutoMode(WindDirectionInterface::AutoMode& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalAutoMode", out);
}

QStatus WindDirectionModel::SetVerticalAutoMode(const WindDirectionInterface::AutoMode value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalAutoMode", value);
}



QStatus HandleWindDirectionCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Environment.WindDirection") {
        if (cmd.property == "HorizontalDirection") {
            uint16_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WindDirectionIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection");
                if (iface) {
                    iface->EmitHorizontalDirectionChanged(value);
                }
            }
        }
        if (cmd.property == "HorizontalMax") {
            uint16_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WindDirectionIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection");
                if (iface) {
                    iface->EmitHorizontalMaxChanged(value);
                }
            }
        }
        if (cmd.property == "HorizontalAutoMode") {
            WindDirectionInterface::AutoMode value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WindDirectionIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection");
                if (iface) {
                    iface->EmitHorizontalAutoModeChanged(value);
                }
            }
        }
        if (cmd.property == "VerticalDirection") {
            uint16_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WindDirectionIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection");
                if (iface) {
                    iface->EmitVerticalDirectionChanged(value);
                }
            }
        }
        if (cmd.property == "VerticalMax") {
            uint16_t value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WindDirectionIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection");
                if (iface) {
                    iface->EmitVerticalMaxChanged(value);
                }
            }
        }
        if (cmd.property == "VerticalAutoMode") {
            WindDirectionInterface::AutoMode value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WindDirectionIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection");
                if (iface) {
                    iface->EmitVerticalAutoModeChanged(value);
                }
            }
        }
    }

    return status;
}


} // namespace emulator
} // namespace services
} // namespace ajn
