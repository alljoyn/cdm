#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>

#include "ControlleeSample.h"

#include "OnOffStatusListener.h"
#include "BatteryStatusListener.h"
#include "RepeatModeListener.h"
#include "RobotCleaningCyclePhaseListener.h"
#include "CurrentPowerListener.h"

#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllee.h>

using namespace std;
using namespace qcc;

class RCControllee : public ControlleeSample
{
  private:
    OnOffStatusListener* m_onOffStatusListener;
    BatteryStatusListener* m_batteryStatusListener;
    RepeatModeListener* m_repeatModeListener;
    RobotCleaningCyclePhaseListener* m_robotCleaningCyclePhaseListener;
    CurrentPowerListener* m_currentPowerListener;

    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    BatteryStatusIntfControllee* m_batteryStatusIntfControllee;
    RepeatModeIntfControllee* m_repeatModeIntfControllee;
    RobotCleaningCyclePhaseIntfControllee* m_robotCleaningCyclePhaseIntfControllee;
    CurrentPowerIntfControllee* m_currentPowerIntfControllee;

  public:
    RCControllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~RCControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

RCControllee::RCControllee(BusAttachment* bus, CdmAboutData* aboutData)
  : ControlleeSample(bus, aboutData),
    m_onOffStatusListener(NULL), m_batteryStatusListener(NULL), m_repeatModeListener(NULL), m_robotCleaningCyclePhaseListener(NULL), m_currentPowerListener(NULL),
    m_onOffStatusIntfControllee(NULL), m_batteryStatusIntfControllee(NULL), m_repeatModeIntfControllee(NULL),
    m_robotCleaningCyclePhaseIntfControllee(NULL), m_currentPowerIntfControllee(NULL)
{
    m_onOffStatusListener = new OnOffStatusListener();
    m_batteryStatusListener = new BatteryStatusListener();
    m_repeatModeListener = new RepeatModeListener();
    m_robotCleaningCyclePhaseListener = new RobotCleaningCyclePhaseListener();
    m_currentPowerListener = new CurrentPowerListener();
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
    if (m_robotCleaningCyclePhaseListener) {
        delete m_robotCleaningCyclePhaseListener;
    }
    if (m_currentPowerListener) {
        delete m_currentPowerListener;
    }
}

void RCControllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    intf = cdmControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Cdm/RobotCleaner", *m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(BATTERY_STATUS_INTERFACE, "/Cdm/RobotCleaner", *m_batteryStatusListener);
    m_batteryStatusIntfControllee = static_cast<BatteryStatusIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(REPEAT_MODE_INTERFACE, "/Cdm/RobotCleaner", *m_repeatModeListener);
    m_repeatModeIntfControllee = static_cast<RepeatModeIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, "/Cdm/RobotCleaner", *m_robotCleaningCyclePhaseListener);
    m_robotCleaningCyclePhaseIntfControllee = static_cast<RobotCleaningCyclePhaseIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(CURRENT_POWER_INTERFACE, "/Cdm/RobotCleaner", *m_currentPowerListener);
    m_currentPowerIntfControllee = static_cast<CurrentPowerIntfControllee*>(intf);
}

void RCControllee::SetInitialProperty()
{
    if (m_onOffStatusIntfControllee) {
        bool onoff = false;
        m_onOffStatusIntfControllee->SetIsOn(onoff);
    }

    if (m_batteryStatusIntfControllee) {
        uint8_t currentValue = 80;
        m_batteryStatusIntfControllee->SetCurrentValue(80);
    }

    if (m_repeatModeIntfControllee) {
        bool repeatMode = false;
        m_repeatModeIntfControllee->SetRepeatMode(repeatMode);
    }

    if (m_robotCleaningCyclePhaseIntfControllee) {
        RobotCleaningCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase
            = { RobotCleaningCyclePhaseInterface::ROBOT_CLEANING_CYCLE_PHASE_CLEANING,
                RobotCleaningCyclePhaseInterface::ROBOT_CLEANING_CYCLE_PHASE_HOMING,
                0x80 };
        uint8_t cyclePhase = RobotCleaningCyclePhaseInterface::ROBOT_CLEANING_CYCLE_PHASE_CLEANING;
        m_robotCleaningCyclePhaseIntfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_robotCleaningCyclePhaseIntfControllee->SetCyclePhase(cyclePhase);
    }

    if (m_currentPowerIntfControllee) {
        double currentPower = 10;
        double precision = 20;
        uint16_t updateMinTime = 1;
        m_currentPowerIntfControllee->SetCurrentPower(currentPower);
        m_currentPowerIntfControllee->SetPrecision(precision);
        m_currentPowerIntfControllee->SetUpdateMinTime(updateMinTime);
    }
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc003";
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

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("RobotCleaner Brand", "en");
    aboutData->SetProductBrand("RobotCleaner", "en");
    aboutData->SetLocation("Living Room", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(ROBOT_CLEANER, "/Cdm/RobotCleaner");
    aboutData->SetDeviceTypeDescription(&description);

    if (!aboutData->IsValid()) {

        return ER_FAIL;
    }

    return ER_OK;
}

int CDECL_CALL main()
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

    BusAttachment* bus = new BusAttachment("RCControllee", true);
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
