/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <iostream>
#include <thread>

#include <alljoyn/cdm/controllee/CdmBusObject.h>

#include <interfaces/controllee/operation/OnOffStatusIntfControllee.h>
#include <interfaces/controllee/operation/OnControlIntfControllee.h>
#include <interfaces/controllee/operation/OffControlIntfControllee.h>
#include <interfaces/controllee/operation/BrightnessIntfControllee.h>
#include <interfaces/controllee/operation/ColorIntfControllee.h>

#include "LampControllee.h"

using namespace ajn;
using namespace services;

const std::string BusPath = "/cdm/lamp";

typedef ajn::services::OnOffStatusIntfControllee OnOffStatus;
typedef ajn::services::OnControlIntfControllee OnControl;
typedef ajn::services::OffControlIntfControllee OffControl;
typedef ajn::services::BrightnessIntfControllee BrightnessControl;
typedef ajn::services::ColorIntfControllee ColorControl;

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

QStatus LampControllee::Run()
{
    QStatus status = SetupDevice();
    if (status != ER_OK)
        return status;

    for(auto i=100; i>0; --i) {
        std::cout<<"Warning: Lamp gonna self destruct in "<<i<<" seconds.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout<<"BOOM!\n";
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

QStatus LampControllee::SetupDevice()
{
    CreateInterfaces();
    QStatus status;

    status = m_security.Enable();
    if (status != ER_OK)
        return status;

    status = m_controllee.Start();
    if (status != ER_OK)
        return status;

    return m_announcer.Announce();
}

QStatus LampControllee::Shutdown()
{
    m_announcer.Unannounce();

    return m_controllee.Stop();
}