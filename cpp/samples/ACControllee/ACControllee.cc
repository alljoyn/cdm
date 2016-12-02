#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>

#include "ControlleeSample.h"

#include "OnOffStatusListener.h"
#include "OnControlListener.h"
#include "OffControlListener.h"
#include "ResourceSavingListener.h"
#include "ClimateControlModeListener.h"
#include "FanSpeedLevelListener.h"
#include "CurrentPowerListener.h"
#include "EnergyUsageListener.h"
#include "CurrentTemperatureListener.h"
#include "TargetTemperatureListener.h"
#include "WindDirectionListener.h"

#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControllee.h>

using namespace std;
using namespace qcc;

class ACControllee : public ControlleeSample
{
  private:
    OnOffStatusListener* m_onOffStatusListener;
    OnControlListener* m_onControlListener;
    OffControlListener* m_offControlListener;
    ResourceSavingListener* m_resourceSavingListener;
    ClimateControlModeListener* m_climateControlModeListener;
    FanSpeedLevelListener* m_fanSpeedLevelListener;
    CurrentPowerListener* m_currentPowerListener;
    EnergyUsageListener* m_energyUsageListener;
    CurrentTemperatureListener* m_currentTemperatureListener;
    TargetTemperatureListener* m_targetTemperatureListener;
    WindDirectionListener* m_windDirectionListener;

    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    OnControlIntfControllee* m_onControlIntfControllee;
    OffControlIntfControllee* m_offControlIntfControllee;
    ResourceSavingIntfControllee* m_resourceSavingIntfControllee;
    ClimateControlModeIntfControllee* m_climateControlModeIntfControllee;
    FanSpeedLevelIntfControllee* m_fanSpeedLevelIntfControllee;
    CurrentPowerIntfControllee* m_currentPowerIntfControllee;
    EnergyUsageIntfControllee* m_energyUsageIntfControllee;
    CurrentTemperatureIntfControllee* m_currentTemperatureIntfControllee;
    TargetTemperatureIntfControllee* m_targetTemperatureIntfControllee;
    WindDirectionIntfControllee* m_windDirectionIntfControllee;

  public:
    ACControllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~ACControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

ACControllee::ACControllee(BusAttachment* bus, CdmAboutData* aboutData)
  : ControlleeSample(bus, aboutData),
    m_onOffStatusListener(NULL), m_onControlListener(NULL), m_offControlListener(NULL), m_resourceSavingListener(NULL), m_climateControlModeListener(NULL), m_fanSpeedLevelListener(NULL), m_currentPowerListener(NULL), m_energyUsageListener(NULL), m_currentTemperatureListener(NULL), m_targetTemperatureListener(NULL), m_windDirectionListener(NULL),
    m_onOffStatusIntfControllee(NULL),  m_onControlIntfControllee(NULL), m_offControlIntfControllee(NULL), m_resourceSavingIntfControllee(NULL), m_climateControlModeIntfControllee(NULL),  m_fanSpeedLevelIntfControllee(NULL), m_currentPowerIntfControllee(NULL), m_energyUsageIntfControllee(NULL), m_currentTemperatureIntfControllee(NULL), m_targetTemperatureIntfControllee(NULL), m_windDirectionIntfControllee(NULL)
{
    m_onOffStatusListener = new OnOffStatusListener();
    m_onControlListener = new OnControlListener();
    m_offControlListener = new OffControlListener();
    m_resourceSavingListener = new ResourceSavingListener();
    m_climateControlModeListener = new ClimateControlModeListener();
    m_fanSpeedLevelListener = new FanSpeedLevelListener();
    m_currentPowerListener = new CurrentPowerListener();
    m_energyUsageListener = new EnergyUsageListener();
    m_currentTemperatureListener = new CurrentTemperatureListener();
    m_targetTemperatureListener = new TargetTemperatureListener();
    m_windDirectionListener = new WindDirectionListener();
}

ACControllee::~ACControllee()
{
    if (m_onOffStatusListener) {
        delete m_onOffStatusListener;
    }
    if (m_onControlListener) {
        delete m_onControlListener;
    }
    if (m_offControlListener) {
        delete m_offControlListener;
    }
    if (m_resourceSavingListener) {
        delete m_resourceSavingListener;
    }
    if (m_climateControlModeListener) {
        delete m_climateControlModeListener;
    }
    if (m_fanSpeedLevelListener) {
        delete m_fanSpeedLevelListener;
    }
    if (m_currentPowerListener) {
        delete m_currentPowerListener;
    }
    if (m_energyUsageListener) {
        delete m_energyUsageListener;
    }
    if (m_currentTemperatureListener) {
        delete m_currentTemperatureListener;
    }
    if (m_targetTemperatureListener) {
        delete m_targetTemperatureListener;
    }
    if (m_windDirectionListener) {
        delete m_windDirectionListener;
    }
}

void ACControllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    intf = cdmControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Cdm/AirConditioner", *m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(ON_CONTROL_INTERFACE, "/Cdm/AirConditioner", *m_onControlListener);
    m_onControlIntfControllee = static_cast<OnControlIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(OFF_CONTROL_INTERFACE, "/Cdm/AirConditioner", *m_offControlListener);
    m_offControlIntfControllee = static_cast<OffControlIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(RESOURCE_SAVING_INTERFACE, "/Cdm/AirConditioner", *m_resourceSavingListener);
    m_resourceSavingIntfControllee = static_cast<ResourceSavingIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(CLIMATE_CONTROL_MODE_INTERFACE, "/Cdm/AirConditioner", *m_climateControlModeListener);
    m_climateControlModeIntfControllee = static_cast<ClimateControlModeIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(FAN_SPEED_LEVEL_INTERFACE, "/Cdm/AirConditioner", *m_fanSpeedLevelListener);
    m_fanSpeedLevelIntfControllee = static_cast<FanSpeedLevelIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(CURRENT_POWER_INTERFACE, "/Cdm/AirConditioner", *m_currentPowerListener);
    m_currentPowerIntfControllee = static_cast<CurrentPowerIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(ENERGY_USAGE_INTERFACE, "/Cdm/AirConditioner", *m_energyUsageListener);
    m_energyUsageIntfControllee = static_cast<EnergyUsageIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(CURRENT_TEMPERATURE_INTERFACE, "/Cdm/AirConditioner", *m_currentTemperatureListener);
    m_currentTemperatureIntfControllee = static_cast<CurrentTemperatureIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(TARGET_TEMPERATURE_INTERFACE, "/Cdm/AirConditioner", *m_targetTemperatureListener);
    m_targetTemperatureIntfControllee = static_cast<TargetTemperatureIntfControllee*>(intf);
    intf = cdmControllee->CreateInterface(WIND_DIRECTION_INTERFACE, "/Cdm/AirConditioner", *m_windDirectionListener);
    m_windDirectionIntfControllee = static_cast<WindDirectionIntfControllee*>(intf);
}

void ACControllee::SetInitialProperty()
{
    if (m_onOffStatusIntfControllee) {
        bool onoff = false;
        m_onOffStatusIntfControllee->SetIsOn(onoff);
    }

    if (m_resourceSavingIntfControllee) {
        bool resourcesavingmode = false;
        m_resourceSavingIntfControllee->SetResourceSavingMode(resourcesavingmode);
    }

    if (m_climateControlModeIntfControllee) {
        ClimateControlModeInterface::SupportedModes supportedModes;
        supportedModes.push_back(ClimateControlModeInterface::MODE_OFF);
        supportedModes.push_back(ClimateControlModeInterface::MODE_COOL);
        m_climateControlModeIntfControllee->SetSupportedModes(supportedModes);
        uint16_t mode = ClimateControlModeInterface::MODE_OFF;
        m_climateControlModeIntfControllee->SetMode(mode);
        uint16_t operationalState = ClimateControlModeInterface::OPERATIONAL_STATE_IDLE;
        m_climateControlModeIntfControllee->SetOperationalState(operationalState);
    }

    if (m_fanSpeedLevelIntfControllee) {
        uint8_t automode = 0;
        uint8_t level = 0;
        uint8_t maxlevel = 10;

        m_fanSpeedLevelIntfControllee->SetAutoMode(automode);
        m_fanSpeedLevelIntfControllee->SetFanSpeedLevel(level);
        m_fanSpeedLevelIntfControllee->SetMaxFanSpeedLevel(maxlevel);
    }

    if (m_currentPowerIntfControllee) {
        double currentPower = 20;
        double precision = 10;
        uint16_t updateMinTime = 1;

        m_currentPowerIntfControllee->SetCurrentPower(currentPower);
        m_currentPowerIntfControllee->SetPrecision(precision);
        m_currentPowerIntfControllee->SetUpdateMinTime(updateMinTime);
    }

    if (m_energyUsageIntfControllee) {
        double cumulativeEnergy = 0.0;
        double precision = 0.1;
        uint16_t updateMinTime = 10000;

        m_energyUsageIntfControllee->SetCumulativeEnergy(cumulativeEnergy);
        m_energyUsageIntfControllee->SetPrecision(precision);
        m_energyUsageIntfControllee->SetUpdateMinTime(updateMinTime);
    }

    if (m_currentTemperatureIntfControllee) {
        double currentValue = 0;
        m_currentTemperatureIntfControllee->SetCurrentValue(currentValue);
    }

    if (m_targetTemperatureIntfControllee) {
        double maxvalue = 30;
        double minvalue = -30;
        double targetvalue = 0;
        double stepvalue = 5;

        m_targetTemperatureIntfControllee->SetMaxValue(maxvalue);
        m_targetTemperatureIntfControllee->SetMinValue(minvalue);
        m_targetTemperatureIntfControllee->SetTargetValue(targetvalue);
        m_targetTemperatureIntfControllee->SetStepValue(stepvalue);
        m_targetTemperatureIntfControllee->SetStrategyOfAdjustingTargetValue(TargetTemperatureIntfControllee::ROUNDING_TO_NEAREST_VALUE);
    }

    if (m_windDirectionIntfControllee) {
        uint8_t h_automode = 0;
        uint16_t h_direction = 0;
        uint8_t v_automode = 0;
        uint16_t V_direction = 0;

        m_windDirectionIntfControllee->SetHorizontalAutoMode(h_automode);
        m_windDirectionIntfControllee->SetHorizontalDirection(h_direction);
        m_windDirectionIntfControllee->SetVerticalAutoMode(v_automode);
        m_windDirectionIntfControllee->SetVerticalDirection(V_direction);
    }
}

QStatus FillAboutData(CdmAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc000";
    String app_name = "ACControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "AirConditioner"));

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

    aboutData->SetDescription("This is an AirConditioner Controllee Application", "en");
    aboutData->SetManufacturer("Manufacturer", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("AirConditioner Brand", "en");
    aboutData->SetProductBrand("AirConditioner", "en");
    aboutData->SetLocation("Living Room", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(AIR_CONDITIONER, "/Cdm/AirConditioner");
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

    BusAttachment* bus = new BusAttachment("TVControllee", true);
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

    ACControllee controllee(bus, aboutData);

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
