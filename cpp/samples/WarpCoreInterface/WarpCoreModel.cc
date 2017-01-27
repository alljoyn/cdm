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

#include "WarpCoreModel.h"
#include "controllee/WarpCoreIntfControllee.h"
#include "../Utils/HAL.h"

using namespace ajn::services;


WarpCoreModel::WarpCoreModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus WarpCoreModel::GetWarpFactor(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "WarpFactor", out);
}

QStatus WarpCoreModel::SetWarpFactor(const double value)
{
    return HAL::WriteProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "WarpFactor", value);
}

QStatus WarpCoreModel::GetCurrentWarpFactor(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "CurrentWarpFactor", out);
}

QStatus WarpCoreModel::GetIsEngaged(bool& out) const
{
    return HAL::ReadProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "IsEngaged", out);
}

QStatus WarpCoreModel::Engage(ErrorCode& error, CdmControllee& controllee)
{
    double warpFactor;
    QStatus status = GetWarpFactor(warpFactor);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "CurrentWarpFactor", warpFactor);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "IsEngaged", true);
    if (status != ER_OK)
        return status;


    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<WarpCoreIntfControllee>(m_busPath, "org.USSEnterprise.Engineering.WarpCore");
        iface->EmitCurrentWarpFactorChanged(warpFactor);
        iface->EmitIsEngagedChanged(true);
    }

    return ER_OK;
}

QStatus WarpCoreModel::Disengage(ErrorCode& error, CdmControllee& controllee)
{
    QStatus status = HAL::WriteProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "CurrentWarpFactor", 0.0);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(m_busPath, "org.USSEnterprise.Engineering.WarpCore", "IsEngaged", false);
    if (status != ER_OK)
        return status;


    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<WarpCoreIntfControllee>(m_busPath, "org.USSEnterprise.Engineering.WarpCore");
        iface->EmitCurrentWarpFactorChanged(0.0);
        iface->EmitIsEngagedChanged(false);
    }

    return ER_OK;
}



QStatus HandleWarpCoreCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.USSEnterprise.Engineering.WarpCore") {
        if (cmd.property == "WarpFactor") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WarpCoreIntfControllee>(cmd.objPath, "org.USSEnterprise.Engineering.WarpCore");
                if (iface) {
                    iface->EmitWarpFactorChanged(value);
                }
            }
        }
        if (cmd.property == "CurrentWarpFactor") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WarpCoreIntfControllee>(cmd.objPath, "org.USSEnterprise.Engineering.WarpCore");
                if (iface) {
                    iface->EmitCurrentWarpFactorChanged(value);
                }
            }
        }
        if (cmd.property == "IsEngaged") {
            bool value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<WarpCoreIntfControllee>(cmd.objPath, "org.USSEnterprise.Engineering.WarpCore");
                if (iface) {
                    iface->EmitIsEngagedChanged(value);
                }
            }
        }
    }

    return status;
}
