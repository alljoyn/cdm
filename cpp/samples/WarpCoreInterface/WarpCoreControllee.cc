/******************************************************************************
 * 
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

#include <alljoyn/cdm/controllee/CdmBusObject.h>

#include "controllee/WarpCoreIntfControllee.h"

#include "WarpCoreControllee.h"

#include "../Utils/Command.h"
#include "../Utils/HAL.h"

using namespace ajn;
using namespace services;

const std::string BusPath = "/Engineering/WarpCore";

typedef ajn::services::WarpCoreIntfControllee WarpCore;

static QStatus InitialiseParamters(CdmControllee& controllee, bool force)
{
    QStatus status = HAL::WriteProperty(BusPath, "org.USSEnterprise.Engineering.WarpCore", "WarpFactor", 6.0, force);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(BusPath, "org.USSEnterprise.Engineering.WarpCore", "CurrentWarpFactor", 0.0, force);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(BusPath, "org.USSEnterprise.Engineering.WarpCore", "IsEngaged", false, force);
    if (status != ER_OK)
        return status;

    return ER_OK;
}

static QStatus HandleCommand(const Command& cmd, CdmControllee& controllee)
{
    if (cmd.name == "reset") {
        return InitialiseParamters(controllee, true);
    }

    QStatus status = ER_OK;

    if (cmd.name == "changed") {
        if (cmd.interface=="org.USSEnterprise.Engineering.WarpCore") {
            status = HandleWarpCoreCommand(cmd, controllee);
        }
    }

    return status;
}

WarpCoreControllee::WarpCoreControllee(BusAttachment& bus, const std::string& aboutData, const std::string& certPath) :
    m_announcer(bus),
    m_security(bus),
    m_controllee(bus),
    m_warpCoreModel(new WarpCoreModel(BusPath))
{
    m_security.LoadFiles(certPath);
    m_announcer.SetAboutData(aboutData);
}

QStatus WarpCoreControllee::Run(bool emitOnSet)
{
    QStatus status = InitialiseWarpCore(emitOnSet);
    if (status != ER_OK)
        return status;

    StartCommands(HandleCommand, m_controllee);

    return ER_OK;
}

void WarpCoreControllee::CreateInterfaces()
{
    m_controllee.CreateInterface<WarpCore>(m_warpCoreModel, BusPath);

}

QStatus WarpCoreControllee::InitialiseWarpCore(bool emitOnSet)
{
    CreateInterfaces();
    QStatus status;

    InitialiseParamters(m_controllee, false);

    status = m_security.Enable();
    if (status != ER_OK)
        return status;

    status = m_controllee.Start(emitOnSet);
    if (status != ER_OK)
        return status;

    return m_announcer.Announce();
}


QStatus WarpCoreControllee::Shutdown()
{
    m_announcer.Unannounce();

    return m_controllee.Stop();
}