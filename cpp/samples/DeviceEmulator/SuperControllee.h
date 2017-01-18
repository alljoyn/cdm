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

#ifndef ALLJOYN_CDM_SUPER_CONTROLLEE_H
#define ALLJOYN_CDM_SUPER_CONTROLLEE_H

#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>

#include <alljoyn/cdm/util/CdmAnnouncer.h>
#include <alljoyn/cdm/util/CdmSecurity.h>

#include "Config.h"
#include "../Utils/Command.h"

namespace ajn {
namespace services {
namespace emulator {
//======================================================================

class SuperControllee {
 public:
    SuperControllee(
        ajn::BusAttachment& bus,
        const Config& config,
        const std::string& certPath
        );

    CdmControllee&  GetControllee() {return m_controllee;}

    QStatus CreateInterfaces();
    QStatus PreloadHAL(bool force = false);
    QStatus Start(bool emitOnSet=false);
    QStatus Stop();

 private:
    QStatus SetupDevice(bool emitOnSet);

    CdmAnnouncer m_announcer;
    CdmSecurity m_security;
    CdmControllee m_controllee;

    const Config& m_config;

    template<typename Interface, typename Model>
    QStatus mkInterface(const std::string& busPath)
    {
        auto model = mkRef<Model>(busPath);
        return m_controllee.CreateInterface<Interface>(model, busPath);
    }

};


QStatus HandleCommand(const Command& cmd, CdmControllee& controllee);

//======================================================================
}}}

#endif //ALLJOYN_CDM_SUPER_CONTROLLEE_H
