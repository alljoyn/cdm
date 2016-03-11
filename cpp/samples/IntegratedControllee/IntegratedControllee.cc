#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/hae/DeviceTypeDescription.h>

#include "ControlleeSample.h"
#include "ControlleeCommands.h"

#include "HidListener.h"
#include "CurrentTemperatureListener.h"
#include "TargetTemperatureListener.h"
#include "WindDirectionListener.h"
#include "AirRecirculationModeListener.h"
#include "AudioVideoInputListener.h"
#include "AudioVolumeListener.h"
#include "BatteryStatusListener.h"
#include "ChannelListener.h"
#include "ClimateControlModeListener.h"
#include "ClosedStatusListener.h"
#include "CurrentPowerListener.h"
#include "EnergyUsageListener.h"
#include "FanSpeedLevelListener.h"
#include "OffControlListener.h"
#include "OnControlListener.h"
#include "OnOffStatusListener.h"
#include "RepeatModeListener.h"
#include "ResourceSavingListener.h"
#include "RobotCleaningCyclePhaseListener.h"

#include <alljoyn/hae/interfaces/input/HidIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/CurrentTemperatureIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/WindDirectionIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AirRecirculationModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AudioVideoInputIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AudioVolumeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/BatteryStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ChannelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ClimateControlModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ClosedStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/CurrentPowerIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/EnergyUsageIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/FanSpeedLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OnControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RepeatModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ResourceSavingIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RobotCleaningCyclePhaseIntfControllee.h>

using namespace std;
using namespace qcc;

class IntegratedControllee : public ControlleeSample
{
  private:
    HidListener m_hidListener;
    CurrentTemperatureListener m_currentTemperatureListener;
    TargetTemperatureListener m_targetTemperatureListener;
    WindDirectionListener m_windDirectionListener;
    AirRecirculationModeListener m_airRecirculationModeListener;
    AudioVideoInputListener m_audioVideoInputListener;
    AudioVolumeListener m_audioVolumeListener;
    BatteryStatusListener m_batteryStatusListener;
    ChannelListener m_channelListener;
    ClimateControlModeListener m_climateControlModeListener;
    ClosedStatusListener m_closedStatusListener;
    CurrentPowerListener m_currentPowerListener;
    EnergyUsageListener m_energyUsageListener;
    FanSpeedLevelListener m_fanSpeedLevelListener;
    OffControlListener m_offControlListener;
    OnControlListener m_onControlListener;
    OnOffStatusListener m_onOffStatusListener;
    RepeatModeListener m_repeatModeListener;
    ResourceSavingListener m_resourceSavingListener;
    RobotCleaningCyclePhaseListener m_robotCleaningCyclePhaseListener;

    HidIntfControllee* m_hidIntfControllee;
    CurrentTemperatureIntfControllee* m_currentTemperatureIntfControllee;
    TargetTemperatureIntfControllee* m_targetTemperatureIntfControllee;
    WindDirectionIntfControllee* m_windDirectionIntfControllee;
    AirRecirculationModeIntfControllee* m_airRecirculationModeIntfControllee;
    AudioVideoInputIntfControllee* m_audioVideoInputIntfControllee;
    AudioVolumeIntfControllee* m_audioVolumeIntfControllee;
    BatteryStatusIntfControllee* m_batteryStatusIntfControllee;
    ChannelIntfControllee* m_channelIntfControllee;
    ClimateControlModeIntfControllee* m_climateControlModeIntfControllee;
    ClosedStatusIntfControllee* m_closedStatusIntfControllee;
    CurrentPowerIntfControllee* m_currentPowerIntfControllee;
    EnergyUsageIntfControllee* m_energyUsageIntfControllee;
    FanSpeedLevelIntfControllee* m_fanSpeedLevelIntfControllee;
    OffControlIntfControllee* m_offControlIntfControllee;
    OnControlIntfControllee* m_onControlIntfControllee;
    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    RepeatModeIntfControllee* m_repeatModeIntfControllee;
    ResourceSavingIntfControllee* m_resourceSavingIntfControllee;
    RobotCleaningCyclePhaseIntfControllee* m_robotCleaningCyclePhaseIntfControllee;

  public:
    IntegratedControllee(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~IntegratedControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

IntegratedControllee::IntegratedControllee(BusAttachment* bus, HaeAboutData* aboutData)
  : ControlleeSample(bus, aboutData)
  ,m_hidIntfControllee(NULL)
  ,m_currentTemperatureIntfControllee(NULL)
  ,m_targetTemperatureIntfControllee(NULL)
  ,m_windDirectionIntfControllee(NULL)
  ,m_airRecirculationModeIntfControllee(NULL)
  ,m_audioVideoInputIntfControllee(NULL)
  ,m_audioVolumeIntfControllee(NULL)
  ,m_batteryStatusIntfControllee(NULL)
  ,m_channelIntfControllee(NULL)
  ,m_climateControlModeIntfControllee(NULL)
  ,m_closedStatusIntfControllee(NULL)
  ,m_currentPowerIntfControllee(NULL)
  ,m_energyUsageIntfControllee(NULL)
  ,m_fanSpeedLevelIntfControllee(NULL)
  ,m_offControlIntfControllee(NULL)
  ,m_onControlIntfControllee(NULL)
  ,m_onOffStatusIntfControllee(NULL)
  ,m_repeatModeIntfControllee(NULL)
  ,m_resourceSavingIntfControllee(NULL)
  ,m_robotCleaningCyclePhaseIntfControllee(NULL)
{
}

IntegratedControllee::~IntegratedControllee()
{
}

void IntegratedControllee::CreateInterfaces()
{
    HaeInterface* intf = NULL;
    HaeControllee* haeControllee = GetControllee();
    if (!haeControllee) {
        return;
    }

    intf = haeControllee->CreateInterface(HID_INTERFACE, "/Hae/IntegratedControllee", m_hidListener);
    m_hidIntfControllee = static_cast<HidIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CURRENT_TEMPERATURE_INTERFACE, "/Hae/IntegratedControllee", m_currentTemperatureListener);
    m_currentTemperatureIntfControllee = static_cast<CurrentTemperatureIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(TARGET_TEMPERATURE_INTERFACE, "/Hae/IntegratedControllee", m_targetTemperatureListener);
    m_targetTemperatureIntfControllee = static_cast<TargetTemperatureIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(WIND_DIRECTION_INTERFACE, "/Hae/IntegratedControllee", m_windDirectionListener);
    m_windDirectionIntfControllee = static_cast<WindDirectionIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(AIR_RECIRCULATION_MODE_INTERFACE, "/Hae/IntegratedControllee", m_airRecirculationModeListener);
    m_airRecirculationModeIntfControllee = static_cast<AirRecirculationModeIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(AUDIO_VIDEO_INPUT_INTERFACE, "/Hae/IntegratedControllee", m_audioVideoInputListener);
    m_audioVideoInputIntfControllee = static_cast<AudioVideoInputIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(AUDIO_VOLUME_INTERFACE, "/Hae/IntegratedControllee", m_audioVolumeListener);
    m_audioVolumeIntfControllee = static_cast<AudioVolumeIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(BATTERY_STATUS_INTERFACE, "/Hae/IntegratedControllee", m_batteryStatusListener);
    m_batteryStatusIntfControllee = static_cast<BatteryStatusIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CHANNEL_INTERFACE, "/Hae/IntegratedControllee", m_channelListener);
    m_channelIntfControllee = static_cast<ChannelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CLIMATE_CONTROL_MODE_INTERFACE, "/Hae/IntegratedControllee", m_climateControlModeListener);
    m_climateControlModeIntfControllee = static_cast<ClimateControlModeIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CLOSED_STATUS_INTERFACE, "/Hae/IntegratedControllee", m_closedStatusListener);
    m_closedStatusIntfControllee = static_cast<ClosedStatusIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CURRENT_POWER_INTERFACE, "/Hae/IntegratedControllee", m_currentPowerListener);
    m_currentPowerIntfControllee = static_cast<CurrentPowerIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(ENERGY_USAGE_INTERFACE, "/Hae/IntegratedControllee", m_energyUsageListener);
    m_energyUsageIntfControllee = static_cast<EnergyUsageIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(FAN_SPEED_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_fanSpeedLevelListener);
    m_fanSpeedLevelIntfControllee = static_cast<FanSpeedLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(OFF_CONTROL_INTERFACE, "/Hae/IntegratedControllee", m_offControlListener);
    m_offControlIntfControllee = static_cast<OffControlIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(ON_CONTROL_INTERFACE, "/Hae/IntegratedControllee", m_onControlListener);
    m_onControlIntfControllee = static_cast<OnControlIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Hae/IntegratedControllee", m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(REPEAT_MODE_INTERFACE, "/Hae/IntegratedControllee", m_repeatModeListener);
    m_repeatModeIntfControllee = static_cast<RepeatModeIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(RESOURCE_SAVING_INTERFACE, "/Hae/IntegratedControllee", m_resourceSavingListener);
    m_resourceSavingIntfControllee = static_cast<ResourceSavingIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, "/Hae/IntegratedControllee", m_robotCleaningCyclePhaseListener);
    m_robotCleaningCyclePhaseIntfControllee = static_cast<RobotCleaningCyclePhaseIntfControllee*>(intf);
}

void IntegratedControllee::SetInitialProperty()
{
    if (m_hidIntfControllee) {
        HidInterface::SupportedInputEvents supportedEvents;
        HidInterface::SupportedInputEvent supportedEvent;
        supportedEvent.type = 0x01;
        supportedEvent.code = 0x71;
        supportedEvent.min = 1;
        supportedEvent.max = 1;
        supportedEvents.push_back(supportedEvent);
        m_hidIntfControllee->SetSupportedEvents(supportedEvents);
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

    if (m_airRecirculationModeIntfControllee) {
        m_airRecirculationModeIntfControllee->SetIsRecirculating(false);
    }

    if (m_audioVideoInputIntfControllee) {
        AudioVideoInputInterface::InputSources inputSources;
        AudioVideoInputInterface::InputSource inputSource1, inputSource2;
        uint16_t inputSource1Id = 8080;
        inputSource1.sourceType = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SOURCE_TYPE_HDMI;
        inputSource1.signalPresence = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_ABSENT;
        inputSource1.portNumber = 1;
        inputSource1.friendlyName = "HDMI1";
        inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(inputSource1Id, inputSource1));
        uint16_t inputSource2Id = 8000;
        inputSource2.sourceType = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SOURCE_TYPE_TUNER;
        inputSource2.signalPresence = AudioVideoInputInterface::AUDIO_VIDEO_INPUT_SIGNAL_PRESENCE_PRESENT;
        inputSource2.portNumber = 1;
        inputSource2.friendlyName = "TUNER";
        inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(inputSource2Id, inputSource2));
        uint16_t inputSourceId = inputSource1Id;
        m_audioVideoInputIntfControllee->SetSupportedInputSources(inputSources);
        m_audioVideoInputIntfControllee->SetInputSourceId(inputSourceId);
    }

    if (m_audioVolumeIntfControllee) {
        uint8_t volume = 1;
        uint8_t maxVolume = 100;
        bool mute = false;
        m_audioVolumeIntfControllee->SetVolume(volume);
        m_audioVolumeIntfControllee->SetMaxVolume(maxVolume);
        m_audioVolumeIntfControllee->SetMute(mute);
    }

    if (m_batteryStatusIntfControllee) {
        uint8_t currentValue = 80;
        m_batteryStatusIntfControllee->SetCurrentValue(80);
    }

    if (m_channelIntfControllee) {
        String channelId = "0_1_2_3_4";
        uint16_t totalNumberOfChannels = 50;
        m_channelIntfControllee->SetChannelId(channelId);
        m_channelIntfControllee->SetTotalNumberOfChannels(totalNumberOfChannels);
    }

    if (m_climateControlModeIntfControllee) {
        ClimateControlModeInterface::SupportedModes supportedModes;
        supportedModes.push_back(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_OFF);
        supportedModes.push_back(ClimateControlModeInterface::CLIMATE_CONTROL_MODE_COOL);
        m_climateControlModeIntfControllee->SetSupportedModes(supportedModes);
        uint16_t mode = ClimateControlModeInterface::CLIMATE_CONTROL_MODE_OFF;
        m_climateControlModeIntfControllee->SetMode(mode);
        uint16_t operationalState = ClimateControlModeInterface::CLIMATE_CONTROL_OPERATIONAL_STATE_IDLE;
        m_climateControlModeIntfControllee->SetOperationalState(operationalState);
    }

    if (m_closedStatusIntfControllee) {
        m_closedStatusIntfControllee->SetIsClosed(true);
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

    if (m_fanSpeedLevelIntfControllee) {
        uint8_t automode = 0;
        uint8_t level = 0;
        uint8_t maxlevel = 10;

        m_fanSpeedLevelIntfControllee->SetAutoMode(automode);
        m_fanSpeedLevelIntfControllee->SetFanSpeedLevel(level);
        m_fanSpeedLevelIntfControllee->SetMaxFanSpeedLevel(maxlevel);
    }

    if (m_onOffStatusIntfControllee) {
        bool onoff = false;
        m_onOffStatusIntfControllee->SetOnOff(onoff);
    }

    if (m_repeatModeIntfControllee) {
        bool repeatMode = false;
        m_repeatModeIntfControllee->SetRepeatMode(repeatMode);
    }

    if (m_resourceSavingIntfControllee) {
        bool resourcesavingmode = false;
        m_resourceSavingIntfControllee->SetResourceSavingMode(resourcesavingmode);
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
}

QStatus FillAboutData(HaeAboutData* aboutData)
{
    String const& defaultLanguage = "en";
    String device_id = "deviceID";
    String app_id = "4a354637-5649-4518-8a48-323c158bc02d";
    String app_name = "IntergratedControllee";
    map<String, String> deviceNames;
    deviceNames.insert(pair<String, String>("en", "IntergratedControllee"));

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

    aboutData->SetDescription("This is an Integrated Controllee Application", "en");
    aboutData->SetManufacturer("Manufacturer", "en");
    aboutData->SetSupportUrl("http://www.alljoyn.org");

    // HAE custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("Controllee Brand", "en");
    aboutData->SetProductBrand("IntegratedControllee", "en");
    aboutData->SetLocation("Room1", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(OTHER, "/Hae/IntegratedControllee");
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

    BusAttachment* bus = new BusAttachment("IntegratedControllee", true);
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

    IntegratedControllee controllee(bus, aboutData);

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
