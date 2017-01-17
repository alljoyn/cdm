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

#include "TargetTemperatureModel.h"
#include <interfaces/controllee/environment/TargetTemperatureIntfControllee.h>
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


TargetTemperatureModel::TargetTemperatureModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus TargetTemperatureModel::GetTargetValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature", "TargetValue", out);
}

QStatus TargetTemperatureModel::SetTargetValue(const double value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature", "TargetValue", value);
}

QStatus TargetTemperatureModel::GetMinValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature", "MinValue", out);
}

QStatus TargetTemperatureModel::GetMaxValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature", "MaxValue", out);
}

QStatus TargetTemperatureModel::GetStepValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature", "StepValue", out);
}



QStatus HandleTargetTemperatureCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Environment.TargetTemperature") {
        if (cmd.property == "TargetValue") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<TargetTemperatureIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature");
                if (iface) {
                    iface->EmitTargetValueChanged(value);
                }
            }
        }
        if (cmd.property == "MinValue") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<TargetTemperatureIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature");
                if (iface) {
                    iface->EmitMinValueChanged(value);
                }
            }
        }
        if (cmd.property == "MaxValue") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<TargetTemperatureIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature");
                if (iface) {
                    iface->EmitMaxValueChanged(value);
                }
            }
        }
        if (cmd.property == "StepValue") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<TargetTemperatureIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Environment.TargetTemperature");
                if (iface) {
                    iface->EmitStepValueChanged(value);
                }
            }
        }
    }

    return status;
}


} // namespace emulator
} // namespace services
} // namespace ajn
