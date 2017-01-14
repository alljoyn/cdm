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
#include "commoncontrollerimpl.h"
#include <qcc/Log.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/controller/CdmTranslator.h>

//------------------------------------------------------------
// CommonControllerDevice
//------------------------------------------------------------

CommonControllerDevice::CommonControllerDevice(CommonControllerRoot *root, Ref<ajn::services::DeviceInfo> device_info)
    : root(root),
      device_info(device_info)
{
    const ajn::AboutObjectDescription& description = device_info->GetAboutObjectDescription();
    std::vector<const char*> paths(description.GetPaths(NULL, 0));
    description.GetPaths(paths.data(), paths.size());

    // TODO: We probably want a unified way of getting all the interfaces (translated and real ones) for a path

    const std::map<std::string, Ref<ajn::services::CdmTranslator>>& translators = device_info->GetTranslators();

    for (size_t i = 0; i < paths.size(); i++) {
        std::vector<const char*> interfaces(description.GetInterfaces(paths[i], NULL, 0));
        description.GetInterfaces(paths[i], interfaces.data(), interfaces.size());

        if (translators.count(paths[i])) {
            for (const auto& translatedInterface: translators.at(paths[i])->GetInterfaces()) {
                interfaces.push_back(translatedInterface.c_str());
            }
        }

        children.push_back(new CommonControllerPath(this, paths[i], interfaces));
    }

#if 0
    // Convert the about data into a generic map for easy display,
    std::vector<const char*> fields;
    fields.resize(data.GetFields());
    data.GetFields(fields.data(), fields.size());

    for (size_t i=0; i<fields.size(); i++) {
        ajn::MsgArg *msgarg;
        data.GetField(fields[i], msgarg);

        // XXX: Massive hack, convert msgarg into xml then strip the XML...
        // TODO: Is there a better way to convert a msgarg into a string?
        QString xml(msgarg->ToString().c_str());
        about_fields[fields[i]] = xml.remove(QRegExp("<[^>]*>"));
    }
#endif
}

CommonControllerDevice::~CommonControllerDevice()
{
}

QString CommonControllerDevice::name() const
{
    char *deviceName = NULL;
    device_info->GetAboutData().GetDeviceName(&deviceName);
    return QString("%1 (%2)").arg(device_info->GetBusName().c_str(), deviceName);
}
