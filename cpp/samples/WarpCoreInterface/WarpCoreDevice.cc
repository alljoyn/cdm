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

#include <iostream>

#include <alljoyn/Status.h>
#include <alljoyn/cdm/util/CdmSystem.h>
#include <alljoyn/cdm/util/CdmAnnouncer.h>
#include <alljoyn/cdm/util/CdmSecurity.h>

#include "WarpCoreControllee.h"
#include "../Utils/HAL.h"
#include "../Utils/Utils.h"


namespace cdm = ajn::services;

//======================================================================


int CDECL_CALL main(int argc, char** argv) {

    cdm::CdmSystem system("WarpCore");

    std::string certsDir;
    std::string stateDir;

    cdm::utils::FindArg(argc, argv, "--state-dir", "emulated_device_state", stateDir);
    cdm::utils::FindArg(argc, argv, "--certs-dir", "certificates/security", certsDir);
    cdm::HAL::SetRootDir(stateDir);

    QStatus status = system.Start();
    if (status != ER_OK) {
        std::cerr << "Failed to start the warp core " << QCC_StatusText(status) << "\n";
        return 1;
    }

    const std::string aboutData =
        "<AboutData>"
            "  <AppId></AppId>"
            "  <DefaultLanguage>en</DefaultLanguage>"
            "  <DeviceName>Virtual Warp Core</DeviceName>"
            "  <DeviceId></DeviceId>"
            "  <AppName>AllJoyn CDM Controllee</AppName>"
            "  <Manufacturer>Alljoyn Sample</Manufacturer>"
            "  <ModelNumber>Wxfy388i</ModelNumber>"
            "  <Description>This is a Full Featured Warp Core Application</Description>"
            "  <DateOfManufacture>10/1/2199</DateOfManufacture>"
            "  <SoftwareVersion>12.20.44 build 44454</SoftwareVersion>"
            "  <HardwareVersion>355.499.b</HardwareVersion>"
            "  <SupportUrl>http://www.alljoyn.org</SupportUrl>"
            "  <CountryOfProduction>USA</CountryOfProduction>"
            "  <CorporateBrand>Lamp Corportate Brand</CorporateBrand>"
            "  <ProductBrand>Lamp Product Brand</ProductBrand>"
            "  <Location>Room1</Location>"
            "  <DeviceTypeDescription>"
            "      <TypeDescription>"
            "          <device_type>1</device_type>"
            "          <object_path>/Engineering/WarpCore</object_path>"
            "      </TypeDescription>"
            "  </DeviceTypeDescription>"
            "</AboutData>";

    WarpCoreControllee warpCore(system.GetBusAttachment(), aboutData, certsDir);

    status = warpCore.Run(true);
    if (status != ER_OK) {
        std::cerr << "Failed to start the warp core: " << QCC_StatusText(status) << "\n";
        return 1;
    }

    status = warpCore.Shutdown();
    if (status != ER_OK) {
        std::cerr << "Failed to shutdown the warp core correctly...Core breach imminent: " << QCC_StatusText(status) << "\n";
        return 1;
    }

    return 0;
}

