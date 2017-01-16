/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 * Source Project (AJOSP) Contributors and others.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * All rights reserved. This program and the accompanying materials are
 * made available under the terms of the Apache License, Version 2.0
 * which accompanies this distribution, and is available at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Copyright 2016 Open Connectivity Foundation and Contributors to
 * AllSeen Alliance. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>

#include "ControlleeSample.h"

{% for interface in Device.all_interfaces() %}
#include "{{interface.Name}}Listener.h"
{% endfor %}

{% for interface in Device.all_interfaces() %}
#include <alljoyn/cdm/interfaces/{{interface.Category}}/{{interface.Name}}IntfControllee.h>
{% endfor %}

using namespace std;
using namespace qcc;

class {{Device.Name}}Controllee : public ControlleeSample
{
private:
    {% for interface in Device.all_interfaces() %}
    {{interface.Name}}Listener* m_{{interface.Name}}Listener;
    {% endfor %}

    {% for interface in Device.all_interfaces() %}
    {{interface.Name}}IntfControllee* m_{{interface.Name}}IntfControllee;
    {% endfor %}

public:
    {{Device.Name}}Controllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~{{Device.Name}}Controllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

{{Device.Name}}Controllee::{{Device.Name}}Controllee(BusAttachment* bus, CdmAboutData* aboutData)
        : ControlleeSample(bus, aboutData),
          {% for interface in Device.all_interfaces() %}
          m_{{interface.Name}}Listener(NULL),
          {% endfor %}
          {% for interface in Device.all_interfaces() %}
          m_{{interface.Name}}IntfControllee(NULL){% if not loop.last %},{% endif %}

          {% endfor %}
{
    {% for interface in Device.all_interfaces() %}
    m_{{interface.Name}}Listener = new {{interface.Name}}Listener;
    {% endfor %}
}

{{Device.Name}}Controllee::~{{Device.Name}}Controllee()
{
    {% for interface in Device.all_interfaces() %}
    if (m_{{interface.Name}}Listener) {
        delete m_{{interface.Name}}Listener;
    }
    {% endfor %}
}

void {{Device.Name}}Controllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    {% for interface in Device.all_interfaces() %}
    intf = cdmControllee->CreateInterface({{interface.Name.upper_snake()}}_INTERFACE, "/Cdm/{{Device.Name}}", *m_{{interface.Name}}Listener);
    m_{{interface.Name}}IntfControllee = static_cast<{{interface.Name}}IntfControllee*>(intf);
    {% endfor %}
}

void {{Device.Name}}Controllee::SetInitialProperty()
{
   // Set any defaults for interface properties here
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "{{Device.AboutData.DefaultLanguage}}";
    String device_id = "000102030405060708090A0B0C0D0E0C";
    String app_id = "000102030405060708090A0B0C0D0E0C";
    String app_name = "{{Device.AboutData.AppName}}";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>(defaultLanguage, "{{Device.AboutData.DeviceName}}"));

    if (!app_id.empty()) {
        aboutData->SetAppId(app_id.c_str());
    }

    if (device_id != "") {
        aboutData->SetDeviceId(device_id.c_str());
    }

    vector<String> languages(1);
    languages[0] = defaultLanguage;

    for (size_t i = 0; i < languages.size(); i++) {
        aboutData->SetSupportedLanguage(languages[i].c_str());
    }

    if (defaultLanguage != "") {
        aboutData->SetDefaultLanguage(defaultLanguage.c_str());
    }

    if (app_name != "") {
        aboutData->SetAppName(app_name.c_str(), languages[0].c_str());
    }

    aboutData->SetModelNumber("{{Device.AboutData.ModelNumber}}");
    aboutData->SetDateOfManufacture("{{Device.AboutData.DateOfManufacture}}");
    aboutData->SetSoftwareVersion("{{Device.AboutData.SoftwareVersion}}");
    aboutData->SetHardwareVersion("{{Device.AboutData.HardwareVersion}}");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("{{Device.AboutData.DeviceName}}", defaultLanguage.c_str());
    }

    aboutData->SetDescription("{{Device.AboutData.Description}}", defaultLanguage.c_str());
    aboutData->SetManufacturer("{{Device.AboutData.Manufacturer}}", defaultLanguage.c_str());
    aboutData->SetSupportUrl("{{Device.AboutData.SupportUrl}}");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("{{Device.AboutData.CountryOfProduction}}", defaultLanguage.c_str());
    aboutData->SetCorporateBrand("{{Device.AboutData.CorporateBrand}}", defaultLanguage.c_str());
    aboutData->SetProductBrand("{{Device.AboutData.ProductBrand}}", defaultLanguage.c_str());
    aboutData->SetLocation("{{Device.AboutData.Location}}", defaultLanguage.c_str());

    DeviceTypeDescription description;
    description.AddDeviceType(static_cast<DeviceType>({{Device.AboutData.DeviceTypeDescription.data.device_type}}), "{{Device.AboutData.DeviceTypeDescription.data.object_path}}");
    aboutData->SetDeviceTypeDescription(&description);

    if (!aboutData->IsValid()) {

        return ER_FAIL;
    }

    return ER_OK;
}

int main()
{
    if (AllJoynInit() != ER_OK) {
        printf("FAILED to init alljoyn\n");
        exit(1);
    }
#ifdef ROUTER
    if (AllJoynRouterInit() != ER_OK) {
        AllJoynShutdown();
        printf("FAILED to init router\n");
        exit(1);
    }
#endif
    printf("AllJoyn Library version: %s\n", ajn::GetVersion());
    printf("AllJoyn Library build info: %s\n", ajn::GetBuildInfo());
    QCC_SetLogLevels("CDM_MODULE_LOG_NAME=15;");

    BusAttachment* bus = new BusAttachment("{{Device.Name}}Controllee", true);
    if (!bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    CdmAboutData* aboutData = new CdmAboutData();
    if (!aboutData) {
        printf("AboutData creation failed.\n");
        delete bus;
        exit(1);
    }
    FillAboutData(aboutData);

    QStatus status = bus->Start();
    if (ER_OK != status) {
        printf("BusAttachment::Start failed (%s)\n", QCC_StatusText(status));
        delete bus;
        delete aboutData;
        exit(1);
    }

    status = bus->Connect();
    if (ER_OK != status) {
        printf("BusAttachment::Connect failed (%s)\n", QCC_StatusText(status));
        bus->Stop();
        bus->Join();
        delete bus;
        delete aboutData;
        exit(1);
    }

    {{Device.Name}}Controllee controllee(bus, aboutData);

    controllee.Startup();

    controllee.Shutdown();

    if (bus) {
        bus->Disconnect();
        bus->Stop();
        bus->Join();

        delete bus;
    }

    if (aboutData) {
        delete aboutData;
    }

#ifdef ROUTER
    AllJoynRouterShutdown();
#endif
    AllJoynShutdown();

    return 0;
}
