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

#include <interfaces/controllee/operation/OnOffStatusIntfControllee.h>
#include <interfaces/controllee/operation/OnControlIntfControllee.h>
#include <interfaces/controllee/operation/OffControlIntfControllee.h>
#include <interfaces/controllee/operation/BrightnessIntfControllee.h>
#include <interfaces/controllee/operation/ColorIntfControllee.h>

#include "LampControllee.h"

#include "../Utils/Command.h"
#include "../Utils/HAL.h"

using namespace ajn;
using namespace services;

const std::string BusPath = "/Cdm/Lamp";

typedef ajn::services::OnOffStatusIntfControllee OnOffStatus;
typedef ajn::services::OnControlIntfControllee OnControl;
typedef ajn::services::OffControlIntfControllee OffControl;
typedef ajn::services::BrightnessIntfControllee BrightnessControl;
typedef ajn::services::ColorIntfControllee ColorControl;


static QStatus SetFactoryDefaults(CdmControllee& controllee, bool force)
{
    QStatus status = HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn", false, force);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Brightness", "Brightness", 0.75, force);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Color", "Hue", 0.0, force);
    if (status != ER_OK)
        return status;

    status = HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Color", "Saturation", 1.0, force);
    if (status != ER_OK)
        return status;

    if (controllee.EmitChangedSignalOnSetProperty()) {
        auto onOffIface = controllee.GetInterface<OnOffStatusIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus");
        onOffIface->EmitIsOnChanged(false);

        auto brightnessIface = controllee.GetInterface<BrightnessIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Brightness");
        brightnessIface->EmitBrightnessChanged(0.75);

        auto colorIface = controllee.GetInterface<ColorIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Color");
        colorIface->EmitHueChanged(0.0);
        colorIface->EmitSaturationChanged(1.0);
    }

    return ER_OK;
}

static QStatus HandleBrightnessCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Operation.Brightness") {
        if (cmd.property == "Brightness") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<BrightnessIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.Brightness");
                if (iface) {
                    iface->EmitBrightnessChanged(value);
                }
            }
        }
    }

    return status;
}

QStatus HandleColorCommand(const Command& cmd, CdmControllee& controllee)
{
    QStatus status = ER_FAIL;

    if (cmd.name == "changed" && cmd.interface == "org.alljoyn.SmartSpaces.Operation.Color") {
        if (cmd.property == "Hue") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<ColorIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.Color");
                if (iface) {
                    iface->EmitHueChanged(value);
                }
            }
        }
        if (cmd.property == "Saturation") {
            double value;
            status = HAL::ReadProperty(cmd.objPath, cmd.interface, cmd.property, value);
            if (status == ER_OK) {
                auto iface = controllee.GetInterface<ColorIntfControllee>(cmd.objPath, "org.alljoyn.SmartSpaces.Operation.Color");
                if (iface) {
                    iface->EmitSaturationChanged(value);
                }
            }
        }
    }

    return status;
}

static QStatus HandleCommand(const Command& cmd, CdmControllee& controllee)
{
    if (cmd.name == "reset") {
        return SetFactoryDefaults(controllee, true);
    }

    QStatus status = ER_OK;

    if (cmd.name == "changed") {
        if (cmd.interface=="org.alljoyn.SmartSpaces.Operation.Brightness") {
            status = HandleBrightnessCommand(cmd, controllee);
        } else if (cmd.interface=="org.alljoyn.SmartSpaces.Operation.Color") {
            status = HandleColorCommand(cmd, controllee);
        }
    }

    return status;
}

LampControllee::LampControllee(BusAttachment& bus, const std::string& aboutData, const std::string& certPath) :
    m_announcer(bus),
    m_security(bus),
    m_controllee(bus),
    m_switchModel(new SwitchModel(BusPath)),
    m_hsvModel(new HSVColorModel(BusPath))
{
    m_security.LoadFiles(certPath);
    m_announcer.SetAboutData(aboutData);
}

QStatus LampControllee::Run(bool emitOnSet)
{
    QStatus status = SetupDevice(emitOnSet);
    if (status != ER_OK)
        return status;

    StartCommands(HandleCommand, m_controllee);

    return ER_OK;
}

void LampControllee::CreateInterfaces()
{
    m_controllee.CreateInterface<OnOffStatus>(m_switchModel, BusPath);
    m_controllee.CreateInterface<OnControl>(m_switchModel, BusPath);
    m_controllee.CreateInterface<OffControl>(m_switchModel, BusPath);

    m_controllee.CreateInterface<BrightnessControl>(m_hsvModel, BusPath);
    m_controllee.CreateInterface<ColorControl>(m_hsvModel, BusPath);
}

QStatus LampControllee::SetupDevice(bool emitOnSet)
{
    CreateInterfaces();
    QStatus status;

    SetFactoryDefaults(m_controllee, false);

    status = m_security.Enable();
    if (status != ER_OK)
        return status;

    status = m_controllee.Start(emitOnSet);
    if (status != ER_OK)
        return status;

    return m_announcer.Announce();
}


QStatus LampControllee::Shutdown()
{
    m_announcer.Unannounce();

    return m_controllee.Stop();
}