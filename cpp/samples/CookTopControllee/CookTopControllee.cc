#include <iostream>
#include <map>

#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/hae/DeviceTypeDescription.h>
#include "ControlleeSample.h"
#include "HeatingZoneListener.h"
#include "OvenCyclePhaseListener.h"
#include "RapidModeListener.h"
#include <alljoyn/hae/interfaces/operation/HeatingZoneIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OvenCyclePhaseIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RapidModeIntfControllee.h>

using namespace std;
using namespace qcc;

class CookTopControllee : public ControlleeSample
{
  private:
    HeatingZoneListener *m_heatingZoneListener;
    OvenCyclePhaseListener *m_ovenCyclePhaseListener;
    RapidModeListener *m_rapidModeListener;

    HeatingZoneIntfControllee* m_heatingZoneIntfControllee;
    OvenCyclePhaseIntfControllee* m_ovenCyclePhaseIntfControllee;
    RapidModeIntfControllee* m_rapidModeIntfControllee;

  public:
    CookTopControllee(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~CookTopControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

CookTopControllee::CookTopControllee(BusAttachment* bus, HaeAboutData* aboutData)
  : ControlleeSample(bus, aboutData), m_heatingZoneIntfControllee(NULL), m_ovenCyclePhaseIntfControllee(NULL), m_rapidModeIntfControllee(NULL)
{
    m_heatingZoneListener = new HeatingZoneListener();
    m_ovenCyclePhaseListener = new OvenCyclePhaseListener();
    m_rapidModeListener = new RapidModeListener();
}

CookTopControllee::~CookTopControllee()
{
    if(m_heatingZoneListener) {
        delete m_heatingZoneListener;
    }
    if(m_ovenCyclePhaseListener) {
        delete m_ovenCyclePhaseListener;
    }
    if(m_rapidModeListener) {
        delete m_rapidModeListener;
    }
}

void CookTopControllee::CreateInterfaces()
{
    HaeInterface* intf = NULL;
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }

    intf = haeControllee->CreateInterface(HEATING_ZONE_INTERFACE, "/Hae/Cooktop", *m_heatingZoneListener);
    m_heatingZoneIntfControllee = static_cast<HeatingZoneIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(OVEN_CYCLE_PHASE_INTERFACE, "/Hae/Cooktop", *m_ovenCyclePhaseListener);
    m_ovenCyclePhaseIntfControllee = static_cast<OvenCyclePhaseIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(RAPID_MODE_INTERFACE, "/Hae/Cooktop", *m_rapidModeListener);
    m_rapidModeIntfControllee = static_cast<RapidModeIntfControllee*>(intf);
}

void CookTopControllee::SetInitialProperty()
{
    m_heatingZoneIntfControllee->SetNumberOfHeatingZones(4);
    uint8_t numZones = m_heatingZoneIntfControllee->GetNumberOfHeatingZones();
    std::vector<uint8_t> maxHeatingLevels;
    for(uint8_t i = 0; i < numZones; i++)
        maxHeatingLevels.push_back(4);
    m_heatingZoneIntfControllee->SetMaxHeatingLevels(maxHeatingLevels);

    std::vector<uint8_t> heatingLevels;
    for(uint8_t i = 0; i < numZones; i++)
        heatingLevels.push_back(i);
    m_heatingZoneIntfControllee->SetHeatingLevels(heatingLevels);

    m_ovenCyclePhaseIntfControllee->SetCyclePhase(OvenCyclePhaseInterface::OvenCyclePhase::OVEN_PHASE_PREHEATING);

    OvenCyclePhaseInterface::SupportedCyclePhases phases;
    phases.push_back(OvenCyclePhaseInterface::OvenCyclePhase::OVEN_PHASE_COOKING);
    phases.push_back(OvenCyclePhaseInterface::OvenCyclePhase::OVEN_PHASE_PREHEATING);
    phases.push_back(OvenCyclePhaseInterface::OvenCyclePhase::OVEN_PHASE_CLEANING);
    phases.push_back(OvenCyclePhaseInterface::OvenCyclePhase::OVEN_PHASE_UNAVAILABLE);

    m_ovenCyclePhaseIntfControllee->SetSupportedCyclePhases(phases);
}

QStatus FillAboutData(HaeAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354777-5649-4518-8a48-777c158bc02d";
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

    // HAE custom metadata fields
    aboutData->SetCountryOfProduction("SP", "en");
    aboutData->SetCorporateBrand("CookEr", "en");
    aboutData->SetProductBrand("Model 3", "en");
    aboutData->SetLocation("Kitchen", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(COOKTOP, "/Hae/Cooktop");
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
    QCC_SetLogLevels("HAE_MODULE_LOG_NAME=15;");
    //CookTopControllee
    BusAttachment* bus = new BusAttachment("CookTopControllee", true);
    if (!bus) {
        printf("BusAttachment creation failed.\n");
        exit(1);
    }

    HaeAboutData* aboutData = new HaeAboutData();
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
