/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>

#include <alljoyn/Status.h>
#include <alljoyn/cdm/util/CdmSystem.h>
#include <alljoyn/cdm/util/CdmAnnouncer.h>
#include <alljoyn/cdm/util/CdmSecurity.h>

#include "LampControllee.h"
#include "../Utils/HAL.h"

namespace cdm = ajn::services;

int main() {
#if 0
    const std::string initial_state =
        "/cdm/lamp:Brightness:Brightness=0.900000\n"
            "/cdm/lamp:Color:Hue=180.0\n"
            "/cdm/lamp:Color:Saturation=0.9\n"
            "/cdm/lamp:OnOffStatus:IsOn=0";

    HAL::init("Lamp.state", initial_state);
#endif

    cdm::CdmSystem system("Lamp");

    QStatus status = system.Start();
    if (status != ER_OK) {
        std::cerr << "Failed to start the Lamp " << QCC_StatusText(status) << "\n";
        return 1;
    }

    const std::string aboutData =
        "<AboutData>"
            "  <AppId>4a354637-5649-4518-8a48-323c158bc004</AppId>"
            "  <DefaultLanguage>en</DefaultLanguage>"
            "  <DeviceName>Lamp</DeviceName>"
            "  <DeviceId>deviceID</DeviceId>"
            "  <AppName>SomeLamp</AppName>"
            "  <Manufacturer>Manufacturer</Manufacturer>"
            "  <ModelNumber>Wxfy388i</ModelNumber>"
            "  <Description>This is a Full Featured Lamp Controllee Application</Description>"
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
            "          <device_type>21</device_type>"
            "          <object_path>/cdm/lamp</object_path>"
            "      </TypeDescription>"
            "  </DeviceTypeDescription>"
            "</AboutData>";

    const std::string certPathPrefix = "lamp_certs/security";

    LampControllee lamp(system.GetBusAttachment(), aboutData, certPathPrefix);

    status = lamp.Run();
    if (status != ER_OK) {
        std::cerr << "Failed to start the Lamp: " << QCC_StatusText(status) << "\n";
        return 1;
    }

    status = lamp.Shutdown();
    if (status != ER_OK) {
        std::cerr << "Failed to shutdown the Lamp correctly: " << QCC_StatusText(status) << "\n";
        return 1;
    }

    return 0;
}
