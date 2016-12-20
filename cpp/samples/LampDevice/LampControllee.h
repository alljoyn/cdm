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

#ifndef ALLJOYN_LAMPCONTROLLEE_H
#define ALLJOYN_LAMPCONTROLLEE_H

#include <memory>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>

#include <alljoyn/cdm/util/CdmAnnouncer.h>
#include <alljoyn/cdm/util/CdmSecurity.h>

#include "SwitchModel.h"
#include "HSVColorModel.h"


class LampControllee {
 public:
    LampControllee(ajn::BusAttachment& bus, const std::string& aboutData, const std::string& certPath);

    QStatus Run();
    QStatus Shutdown();

 private:
    void CreateInterfaces();
    QStatus SetupDevice();

    ajn::services::CdmAnnouncer m_announcer;
    ajn::services::CdmSecurity m_security;
    ajn::services::CdmControllee m_controllee;

    ajn::services::Ref<SwitchModel> m_switchModel;
    ajn::services::Ref<HSVColorModel> m_hsvModel;
};


#endif //ALLJOYN_LAMPCONTROLLEE_H