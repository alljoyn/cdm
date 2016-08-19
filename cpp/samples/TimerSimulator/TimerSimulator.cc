#include <iostream>
#include <time.h>
#include <map>
#include <algorithm>
#include <thread>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>
#include "TestControllee.h"
#include <signal.h>
#include <limits>

bool interrupt = false;
QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc02d";
    String app_name = "TestControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "TestControllee"));

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

    aboutData->SetModelNumber("ModelNumber");
    aboutData->SetDateOfManufacture("15/1/2199");
    aboutData->SetSoftwareVersion("55.55.55 build 555");
    aboutData->SetHardwareVersion("555.555. b");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("Test device", "en");
    }

    aboutData->SetDescription("This is an Test Controllee Application", "en");
    aboutData->SetManufacturer("Nik", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("SP", "en");
    aboutData->SetCorporateBrand("TestControllee", "en");
    aboutData->SetProductBrand("Model 1", "en");
    aboutData->SetLocation("Basement", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(OTHER, "/Cdm/TestControllee");
    aboutData->SetDeviceTypeDescription(&description);

    if (!aboutData->IsValid()) {

        return ER_FAIL;
    }

    return ER_OK;
}

void timerThread(TestControllee* controllee)
{
    clock_t t;
    clock_t initT = clock();
    clock_t iter;
    int sec = 0;
    int sec_old = 0;

    cout << "tmrThread start "<< endl;
    while(!interrupt)
    {
        iter = clock() - initT;
        sec = ((float)iter)/CLOCKS_PER_SEC;
        if(sec > sec_old)
        {
            //cout << "seconds: " << sec <<endl;
            //printf ("Scince start %lu clicks (%f seconds).\n",iter,((float)iter)/CLOCKS_PER_SEC);
            sec_old = sec;
            controllee->TimeChangedCallback(sec);
        }
    };
    cout << "tmrThread exit "<< endl;
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

    BusAttachment* bus = new BusAttachment("TimerSimulator", true);
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

    TestControllee controllee(bus, aboutData);
    std::thread tmrThread(timerThread, &controllee);
    controllee.Startup();

    controllee.Shutdown();

    interrupt = true;
    tmrThread.join();

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


