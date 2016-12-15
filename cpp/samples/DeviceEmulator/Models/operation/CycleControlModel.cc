/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "CycleControlModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<CycleControlInterface::OperationalState>
{
    Element* put(Element* parent, CycleControlInterface::OperationalState value)
    {
        Serializer<int32_t> ser;
        return ser.put(parent, value);
    }


    CycleControlInterface::OperationalState get(Element* element)
    {
        Serializer<int32_t> ser;
        return static_cast<CycleControlInterface::OperationalState>(ser.get(element));
    }
};

template <>
struct Serializer<CycleControlInterface::OperationalCommands>
{
    Element* put(Element* parent, CycleControlInterface::OperationalCommands value)
    {
        Serializer<int32_t> ser;
        return ser.put(parent, value);
    }


    CycleControlInterface::OperationalCommands get(Element* element)
    {
        Serializer<int32_t> ser;
        return static_cast<CycleControlInterface::OperationalCommands>(ser.get(element));
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


CycleControlModel::CycleControlModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus CycleControlModel::GetOperationalState(CycleControlInterface::OperationalState& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "OperationalState", out);
}

QStatus CycleControlModel::GetSupportedOperationalStates(std::vector<CycleControlInterface::OperationalState>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "SupportedOperationalStates", out);
}

QStatus CycleControlModel::GetSupportedOperationalCommands(std::vector<CycleControlInterface::OperationalCommands>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "SupportedOperationalCommands", out);
}

QStatus CycleControlModel::ExecuteOperationalCommand(CycleControlInterface::OperationalCommands arg_command, ErrorCode& error, CdmControllee& controllee)
{
    // TODO - fix me up manually
    return ER_FAIL;
}

} // namespace emulator
} // namespace services
} // namespace ajn