#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/hae/DeviceTypeDescription.h>

#include "ControlleeSample.h"

#include "OnOffStatusListener.h"
#include "BatteryStatusListener.h"
#include "RepeatModeListener.h"

#include <alljoyn/hae/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/BatteryStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RepeatModeIntfControllee.h>

using namespace std;
using namespace qcc;

class RCControllee : public ControlleeSample
{
  private:
    OnOffStatusListener* m_onOffStatusListener;
    BatteryStatusListener* m_batteryStatusListener;
    RepeatModeListener* m_repeatModeListener;

    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    BatteryStatusIntfControllee* m_batteryStatusIntfControllee;
    RepeatModeIntfControllee* m_repeatModeIntfControllee;

  public:
    RCControllee(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~RCControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

RCControllee::RCControllee(BusAttachment* bus, HaeAboutData* aboutData)
  : ControlleeSample(bus, aboutData),
    m_onOffStatusListener(NULL), m_batteryStatusListener(NULL), m_repeatModeListener(NULL),
    m_onOffStatusIntfControllee(NULL), m_batteryStatusIntfControllee(NULL), m_repeatModeIntfControllee(NULL)
{
    m_onOffStatusListener = new OnOffStatusListener();
    m_batteryStatusListener = new BatteryStatusListener();
    m_repeatModeListener = new RepeatModeListener();
}

RCControllee::~RCControllee()
{
    if (m_onOffStatusListener) {
        delete m_onOffStatusListener;
    }
    if (m_batteryStatusListener) {
        delete m_batteryStatusListener;
    }
    if (m_repeatModeListener) {
        delete m_repeatModeListener;
    }
}

void RCControllee::CreateInterfaces()
{
    HaeInterface* intf = NULL;
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }

    intf = haeControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Hae/RobotCleaner", *m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(BATTERY_STATUS_INTERFACE, "/Hae/RobotCleaner", *m_batteryStatusListener);
    m_batteryStatusIntfControllee = static_cast<BatteryStatusIntfControllee*>(intf);
    intf = haeControllee->CreateInterface(REPEAT_MODE_INTERFACE, "/Hae/RobotCleaner", *m_repeatModeListener);
    m_repeatModeIntfControllee = static_cast<RepeatModeIntfControllee*>(intf);
}

void RCControllee::SetInitialProperty()
{
    if (m_onOffStatusIntfControllee) {
        bool onoff = false;
        m_onOffStatusIntfControllee->SetOnOff(onoff);
    }

    if (m_batteryStatusIntfControllee) {
        uint8_t currentValue = 80;
        m_batteryStatusIntfControllee->SetCurrentValue(80);
    }

    if (m_repeatModeIntfControllee) {
        bool repeatMode = false;
        m_repeatModeIntfControllee->SetRepeatMode(repeatMode);
    }
}

QStatus FillAboutData(HaeAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc03e";
    String app_name = "RCControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "RobotCleaner"));

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

    aboutData->SetModelNumber("Wxfy388i");
    aboutData->SetDateOfManufacture("10/1/2199");
    aboutData->SetSoftwareVersion("12.20.44 build 44454");
    aboutData->SetHardwareVersion("355.499. b");

    map<String, String>::const_iterator iter = deviceNames.find(languages[0]);
    if (iter != deviceNames.end()) {
        aboutData->SetDeviceName(iter->second.c_str(), languages[0].c_str());
    } else {
        aboutData->SetDeviceName("My device name", "en");
    }

    aboutData->SetDescription("This is an RobotCleaner Controllee Application", "en");
    aboutData->SetManufacturer("Manufacturer", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // HAE custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("RobotCleaner Brand", "en");
    aboutData->SetProductBrand("RobotCleaner", "en");
    aboutData->SetLocation("Living Room", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(ROBOT_CLEANER, "/Hae/RobotCleaner");
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

    BusAttachment* bus = new BusAttachment("RCControllee", true);
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

    RCControllee controllee(bus, aboutData);

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
