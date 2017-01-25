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
#include <alljoyn/cdm/common/DeviceTypeDescription.h>
#include "ControlleeSample.h"
#include "HeatingZoneModel.h"
#include "OvenCyclePhaseModel.h"
#include "RapidModeModel.h"
#include <interfaces/controllee/operation/HeatingZoneIntfControllee.h>
#include <interfaces/controllee/operation/OvenCyclePhaseIntfControllee.h>
#include <interfaces/controllee/operation/RapidModeIntfControllee.h>

using namespace std;
using namespace qcc;

class CookTopControllee : public ControlleeSample
{
 private:
    Ref<HeatingZoneModel> m_heatingZoneModel;
    Ref<OvenCyclePhaseModel> m_ovenCyclePhaseModel;
    Ref<RapidModeModel> m_rapidModeModel;

 public:
    CookTopControllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~CookTopControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

CookTopControllee::CookTopControllee(BusAttachment* bus, CdmAboutData* aboutData)
    : ControlleeSample(bus, aboutData)
{
    m_heatingZoneModel = mkRef<HeatingZoneModel>();
    m_ovenCyclePhaseModel = mkRef<OvenCyclePhaseModel>();
    m_rapidModeModel = mkRef<RapidModeModel>();
}

CookTopControllee::~CookTopControllee()
{
}

void CookTopControllee::CreateInterfaces()
{
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    cdmControllee->CreateInterface<HeatingZoneIntfControllee>(m_heatingZoneModel, "/Cdm/Cooktop");
    cdmControllee->CreateInterface<OvenCyclePhaseIntfControllee>(m_ovenCyclePhaseModel, "/Cdm/Cooktop");
    cdmControllee->CreateInterface<RapidModeIntfControllee>(m_rapidModeModel, "/Cdm/Cooktop");
}

void CookTopControllee::SetInitialProperty()
{
    uint8_t numZones;
    m_heatingZoneModel->SetNumberOfHeatingZones(4);
    m_heatingZoneModel->GetNumberOfHeatingZones(numZones);
    std::vector<uint8_t> maxHeatingLevels;
    for(uint8_t i = 0; i < numZones; i++)
        maxHeatingLevels.push_back(4);
    m_heatingZoneModel->SetMaxHeatingLevels(maxHeatingLevels);

    std::vector<uint8_t> heatingLevels;
    for(uint8_t i = 0; i < numZones; i++)
        heatingLevels.push_back(i);
    m_heatingZoneModel->SetHeatingLevels(heatingLevels);

    m_ovenCyclePhaseModel->SetCyclePhase(OvenCyclePhaseModel::OVEN_PHASE_PREHEATING);

    std::vector<uint8_t> phases;
    phases.push_back(OvenCyclePhaseModel::OVEN_PHASE_COOKING);
    phases.push_back(OvenCyclePhaseModel::OVEN_PHASE_PREHEATING);
    phases.push_back(OvenCyclePhaseModel::OVEN_PHASE_CLEANING);
    phases.push_back(OvenCyclePhaseModel::OVEN_PHASE_UNAVAILABLE);

    m_ovenCyclePhaseModel->SetSupportedCyclePhases(phases);
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354777-5649-4518-8a48-777c158bc001";
    String app_name = "CookControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "CookTop"));

    if (!app_id.empty()) {
        aboutData->SetAppId(app_id.c_str());
    }

    if (device_id != "") {
        aboutData->SetDeviceId(device_id.c_str());
    }

    vector<String> languages(1);
    languages[0] = "en";

    for (size_t i = 0; i < languages.size(); i++) {
        aboutData->SetSupportedLanguage(languages[i].c_str());
    }

    if (defaultLanguage != "") {
        aboutData->SetDefaultLanguage(defaultLanguage.c_str());
    }

    if (app_name != "") {
        aboutData->SetAppName(app_name.c_str(), languages[0].c_str());
    }

    aboutData->SetModelNumber("md1");
    aboutData->SetDateOfManufacture("22/12/1986");
    aboutData->SetSoftwareVersion("77.77.77 build 777");
    aboutData->SetHardwareVersion("777.777. b");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("Cooking device", "en");
    }

    aboutData->SetDescription("This is an Cooktop Controllee Application", "en");
    aboutData->SetManufacturer("Nik", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("SP", "en");
    aboutData->SetCorporateBrand("CookEr", "en");
    aboutData->SetProductBrand("Model 3", "en");
    aboutData->SetLocation("Kitchen", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(COOKTOP, "/Cdm/Cooktop");
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
    //CookTopControllee
    BusAttachment* bus = new BusAttachment("CookTopControllee", true);
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

    CookTopControllee controllee(bus, aboutData);

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
