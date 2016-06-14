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
#include "CurrentPowerListener.h"
#include "EnergyUsageListener.h"
#include "FanSpeedLevelListener.h"
#include "OffControlListener.h"
#include "OnControlListener.h"
#include "OnOffStatusListener.h"
#include "RepeatModeListener.h"
#include "ResourceSavingListener.h"
#include "RobotCleaningCyclePhaseListener.h"
#include "ClosedStatusListener.h"
#include "CycleControlListener.h"
#include "DishWashingCyclePhaseListener.h"
#include "HeatingZoneListener.h"
#include "LaundryCyclePhaseListener.h"
#include "OvenCyclePhaseListener.h"
#include "RapidModeListener.h"
#include "RemoteControllabilityListener.h"
#include "SoilLevelListener.h"
#include "SpinSpeedLevelListener.h"
#include "TimerListener.h"
#include "WaterLevelListener.h"
#include "AlertsListener.h"
#include "CurrentAirQualityListener.h"
#include "CurrentAirQualityLevelListener.h"
#include "CurrentHumidityListener.h"
#include "TargetHumidityListener.h"
#include "TargetTemperatureLevelListener.h"
#include "MoistureOutputLevelListener.h"
#include "FilterStatusListener.h"
#include "HvacFanModeListener.h"
#include "PlugInUnitsListener.h"
#include "RapidModeTimedListener.h"

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
#include <alljoyn/hae/interfaces/operation/CurrentPowerIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/EnergyUsageIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/FanSpeedLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OnControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RepeatModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ResourceSavingIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RobotCleaningCyclePhaseIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/ClosedStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/CycleControlIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/DishWashingCyclePhaseIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/HeatingZoneIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/LaundryCyclePhaseIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/OvenCyclePhaseIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RapidModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RemoteControllabilityIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/SoilLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/SpinSpeedLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/TimerIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/AlertsIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/MoistureOutputLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/FilterStatusIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/HvacFanModeIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/PlugInUnitsIntfControllee.h>
#include <alljoyn/hae/interfaces/operation/RapidModeTimedIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/WaterLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/CurrentHumidityIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/TargetHumidityIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureLevelIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/CurrentAirQualityIntfControllee.h>
#include <alljoyn/hae/interfaces/environment/CurrentAirQualityLevelIntfControllee.h>

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
    CurrentPowerListener m_currentPowerListener;
    EnergyUsageListener m_energyUsageListener;
    FanSpeedLevelListener m_fanSpeedLevelListener;
    OffControlListener m_offControlListener;
    OnControlListener m_onControlListener;
    OnOffStatusListener m_onOffStatusListener;
    RepeatModeListener m_repeatModeListener;
    ResourceSavingListener m_resourceSavingListener;
    RobotCleaningCyclePhaseListener m_robotCleaningCyclePhaseListener;
    ClosedStatusListener m_closedStatusListener;
    CycleControlListener m_cycleControlListener;
    DishWashingCyclePhaseListener m_dishWashingCycleListener;
    HeatingZoneListener m_heatingZoneListener;
    LaundryCyclePhaseListener m_laundryCyclePhaseListener;
    OvenCyclePhaseListener m_ovenCyclePhaseListener;
    RapidModeListener m_rapidModeListener;
    RemoteControllabilityListener m_remoteControllabilityListener;
    SoilLevelListener m_soilLevelListener;
    SpinSpeedLevelListener m_spinSpeedLevelListener;
    TimerListener m_timerListener;
    WaterLevelListener m_waterLevelListener;
    AlertsListener m_alertsListener;
    CurrentAirQualityListener m_currentAirQualityListener;
    CurrentAirQualityLevelListener m_currentAirQualityLevelListener;
    CurrentHumidityListener m_currentHumidityListener;
    TargetHumidityListener m_targetHumidityListener;
    TargetTemperatureLevelListener m_targetTemperatureLevelListener;
    MoistureOutputLevelListener m_moistureOutputLevelListener;
    FilterStatusListener m_filterStatusListener;
    HvacFanModeListener m_hvacFanModeListener;
    PlugInUnitsListener m_plugInUnitsListener;
    RapidModeTimedListener m_rapidModeTimedListener;

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
    CurrentPowerIntfControllee* m_currentPowerIntfControllee;
    EnergyUsageIntfControllee* m_energyUsageIntfControllee;
    FanSpeedLevelIntfControllee* m_fanSpeedLevelIntfControllee;
    OffControlIntfControllee* m_offControlIntfControllee;
    OnControlIntfControllee* m_onControlIntfControllee;
    OnOffStatusIntfControllee* m_onOffStatusIntfControllee;
    RepeatModeIntfControllee* m_repeatModeIntfControllee;
    ResourceSavingIntfControllee* m_resourceSavingIntfControllee;
    RobotCleaningCyclePhaseIntfControllee* m_robotCleaningCyclePhaseIntfControllee;
    ClosedStatusIntfControllee* m_closedStatusIntfControllee;
    CycleControlIntfControllee* m_cycleControlIntfControllee;
    DishWashingCyclePhaseIntfControllee* m_dishWashingCyclePhaseIntfControllee;
    HeatingZoneIntfControllee* m_heatingZoneIntfControllee;
    LaundryCyclePhaseIntfControllee* m_laundryCyclePhaseIntfControllee;
    OvenCyclePhaseIntfControllee* m_ovenCyclePhaseIntfControllee;
    RapidModeIntfControllee* m_rapidModeIntfControllee;
    RemoteControllabilityIntfControllee* m_remoteControllabilityIntfControllee;
    SoilLevelIntfControllee* m_soilLevelIntfControllee;
    SpinSpeedLevelIntfControllee* m_spinSpeedLevelIntfControllee;
    TimerIntfControllee* m_timerIntfControllee;
    WaterLevelIntfControllee* m_waterLevelIntfControllee;
    AlertsIntfControllee* m_alertsIntfControllee;
    CurrentAirQualityIntfControllee* m_currentAirQualityIntfControllee;
    CurrentAirQualityLevelIntfControllee* m_currentAirQualityLevelIntfControllee;
    CurrentHumidityIntfControllee* m_currentHumidityIntfControllee;
    TargetHumidityIntfControllee* m_targetHumidityIntfControllee;
    TargetTemperatureLevelIntfControllee* m_targetTemperatureLevelIntfControllee;
    MoistureOutputLevelIntfControllee* m_moistureOutputLevelIntfControllee;
    FilterStatusIntfControllee* m_filterStatusIntfControllee;
    HvacFanModeIntfControllee* m_hvacFanModeIntfControllee;
    PlugInUnitsIntfControllee* m_plugInUnitsIntfControllee;
    RapidModeTimedIntfControllee* m_rapidModeTimedIntfControllee;

  public:
    IntegratedControllee(BusAttachment* bus, HaeAboutData* aboutData);
    virtual ~IntegratedControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

IntegratedControllee::IntegratedControllee(BusAttachment* bus, HaeAboutData* aboutData) :
    ControlleeSample(bus, aboutData), m_hidIntfControllee(NULL), m_currentTemperatureIntfControllee(NULL), m_targetTemperatureIntfControllee(NULL),
    m_windDirectionIntfControllee(NULL), m_airRecirculationModeIntfControllee(NULL), m_audioVideoInputIntfControllee(NULL), m_audioVolumeIntfControllee(NULL),
    m_batteryStatusIntfControllee(NULL), m_channelIntfControllee(NULL), m_climateControlModeIntfControllee(NULL), m_currentPowerIntfControllee(NULL),
    m_energyUsageIntfControllee(NULL), m_fanSpeedLevelIntfControllee(NULL), m_offControlIntfControllee(NULL), m_onControlIntfControllee(NULL),
    m_onOffStatusIntfControllee(NULL), m_repeatModeIntfControllee(NULL), m_resourceSavingIntfControllee(NULL), m_robotCleaningCyclePhaseIntfControllee(NULL),
    m_closedStatusIntfControllee(NULL), m_cycleControlIntfControllee(NULL), m_dishWashingCyclePhaseIntfControllee(NULL), m_heatingZoneIntfControllee(NULL),
    m_laundryCyclePhaseIntfControllee(NULL), m_ovenCyclePhaseIntfControllee(NULL), m_rapidModeIntfControllee(NULL), m_remoteControllabilityIntfControllee(NULL),
    m_soilLevelIntfControllee(NULL), m_spinSpeedLevelIntfControllee(NULL), m_timerIntfControllee(NULL), m_waterLevelIntfControllee(NULL), m_alertsIntfControllee(NULL),
    m_currentAirQualityIntfControllee(NULL), m_currentAirQualityLevelIntfControllee(NULL), m_currentHumidityIntfControllee(NULL), m_targetHumidityIntfControllee(NULL),
    m_targetTemperatureLevelIntfControllee(NULL), m_moistureOutputLevelIntfControllee(NULL), m_filterStatusIntfControllee(NULL), m_hvacFanModeIntfControllee(NULL),
    m_plugInUnitsIntfControllee(NULL), m_rapidModeTimedIntfControllee(NULL)
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

    intf = haeControllee->CreateInterface(CLOSED_STATUS_INTERFACE, "/Hae/IntegratedControllee", m_closedStatusListener);
    m_closedStatusIntfControllee = static_cast<ClosedStatusIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CYCLE_CONTROL_INTERFACE, "/Hae/IntegratedControllee", m_cycleControlListener);
    m_cycleControlIntfControllee = static_cast<CycleControlIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(DISH_WASHING_CYCLE_PHASE_INTERFACE, "/Hae/IntegratedControllee", m_dishWashingCycleListener);
    m_dishWashingCyclePhaseIntfControllee = static_cast<DishWashingCyclePhaseIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(HEATING_ZONE_INTERFACE, "/Hae/IntegratedControllee", m_heatingZoneListener);
    m_heatingZoneIntfControllee = static_cast<HeatingZoneIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(LAUNDRY_CYCLE_PHASE_INTERFACE, "/Hae/IntegratedControllee", m_laundryCyclePhaseListener);
    m_laundryCyclePhaseIntfControllee = static_cast<LaundryCyclePhaseIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(OVEN_CYCLE_PHASE_INTERFACE, "/Hae/IntegratedControllee", m_ovenCyclePhaseListener);
    m_ovenCyclePhaseIntfControllee = static_cast<OvenCyclePhaseIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(RAPID_MODE_INTERFACE, "/Hae/IntegratedControllee", m_rapidModeListener);
    m_rapidModeIntfControllee = static_cast<RapidModeIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(REMOTE_CONTROLLABILITY_INTERFACE, "/Hae/IntegratedControllee", m_remoteControllabilityListener);
    m_remoteControllabilityIntfControllee = static_cast<RemoteControllabilityIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(SOIL_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_soilLevelListener);
    m_soilLevelIntfControllee = static_cast<SoilLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(SPIN_SPEED_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_spinSpeedLevelListener);
    m_spinSpeedLevelIntfControllee = static_cast<SpinSpeedLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(TIMER_INTERFACE, "/Hae/IntegratedControllee", m_timerListener);
    m_timerIntfControllee = static_cast<TimerIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(WATER_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_waterLevelListener);
    m_waterLevelIntfControllee = static_cast<WaterLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(ALERTS_INTERFACE, "/Hae/IntegratedControllee", m_alertsListener);
    m_alertsIntfControllee = static_cast<AlertsIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CURRENT_AIR_QUALITY_INTERFACE, "/Hae/IntegratedControllee", m_currentAirQualityListener);
    m_currentAirQualityIntfControllee = static_cast<CurrentAirQualityIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CURRENT_AIR_QUALITY_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_currentAirQualityLevelListener);
    m_currentAirQualityLevelIntfControllee = static_cast<CurrentAirQualityLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(CURRENT_HUMIDITY_INTERFACE, "/Hae/IntegratedControllee", m_currentHumidityListener);
    m_currentHumidityIntfControllee = static_cast<CurrentHumidityIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(TARGET_HUMIDITY_INTERFACE, "/Hae/IntegratedControllee", m_targetHumidityListener);
    m_targetHumidityIntfControllee = static_cast<TargetHumidityIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(TARGET_TEMPERATURE_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_targetTemperatureLevelListener);
    m_targetTemperatureLevelIntfControllee = static_cast<TargetTemperatureLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(MOISTURE_OUTPUT_LEVEL_INTERFACE, "/Hae/IntegratedControllee", m_moistureOutputLevelListener);
    m_moistureOutputLevelIntfControllee = static_cast<MoistureOutputLevelIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(FILTER_STATUS_INTERFACE, "/Hae/IntegratedControllee", m_filterStatusListener);
    m_filterStatusIntfControllee = static_cast<FilterStatusIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(HVAC_FAN_MODE_INTERFACE, "/Hae/IntegratedControllee", m_hvacFanModeListener);
    m_hvacFanModeIntfControllee = static_cast<HvacFanModeIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(PLUG_IN_UNITS_INTERFACE, "/Hae/IntegratedControllee", m_plugInUnitsListener);
    m_plugInUnitsIntfControllee = static_cast<PlugInUnitsIntfControllee*>(intf);

    intf = haeControllee->CreateInterface(RAPID_MODE_TIMED_INTERFACE, "/Hae/IntegratedControllee", m_rapidModeTimedListener);
    m_rapidModeTimedIntfControllee = static_cast<RapidModeTimedIntfControllee*>(intf);
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
        String channelId = CHANNELID_PREFIX + String("0");
        uint16_t totalNumberOfChannels = TOTAL_NUM_OF_CHANNEL;
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
        double cumulativeEnergy = 10.0;
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

    if (m_cycleControlIntfControllee) {
        CycleControlInterface::SupportedOperationalCommands comm;
        comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_START);
        comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_STOP);
        comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_PAUSE);
        comm.push_back(CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_RESUME);
        m_cycleControlIntfControllee->SetSupportedCommands(comm);

        CycleControlInterface::SupportedOperationalStates states;
        states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE);
        states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING);
        states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START);
        states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START);
        states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED);
        states.push_back(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_END_OF_CYCLE);

        m_cycleControlIntfControllee->SetSupportedStates(states);
    }

    if (m_dishWashingCyclePhaseIntfControllee) {
        DishWashingCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase
        = {
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_UNAVAILABLE,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_PRE_WASH,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_WASH,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_RINSE,
            DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_DRY,
            0x80,
            0x81
        };
        uint8_t cyclePhase = DishWashingCyclePhaseInterface::DISH_WASHING_PHASE_PRE_WASH;
        m_dishWashingCyclePhaseIntfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_dishWashingCyclePhaseIntfControllee->SetCyclePhase(cyclePhase);
    }

    if (m_heatingZoneIntfControllee) {
        uint8_t numberOfHeatingZones = 4;
        uint8_t maxLvl = 6;
        uint8_t initialHeatingLevel = 0;
        std::vector<uint8_t> maxHeatingLevels;
        std::vector<uint8_t> heatingLevels;

        for (int i = 0; i < numberOfHeatingZones; i++) {
            maxHeatingLevels.push_back(maxLvl);
            heatingLevels.push_back(initialHeatingLevel);
        }
        m_heatingZoneIntfControllee->SetNumberOfHeatingZones(numberOfHeatingZones);
        m_heatingZoneIntfControllee->SetMaxHeatingLevels(maxHeatingLevels);
        m_heatingZoneIntfControllee->SetHeatingLevels(heatingLevels);
    }

    if (m_laundryCyclePhaseIntfControllee) {
        LaundryCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase
        = {
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_UNAVAILABLE,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_PRE_WASHING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_WASHING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_RINSING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_SPINNING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_STEAM,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_DRYING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_COOLING,
            LaundryCyclePhaseInterface::LAUNDRY_PHASE_ANTICREASING,
            0x80,
            0x81
        };
        uint8_t cyclePhase = LaundryCyclePhaseInterface::LAUNDRY_PHASE_PRE_WASHING;
        m_laundryCyclePhaseIntfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_laundryCyclePhaseIntfControllee->SetCyclePhase(cyclePhase);

    }

    if (m_ovenCyclePhaseIntfControllee) {
        OvenCyclePhaseInterface::SupportedCyclePhases supportedCyclePhase
        = {
            OvenCyclePhaseInterface::OVEN_PHASE_UNAVAILABLE,
            OvenCyclePhaseInterface::OVEN_PHASE_PREHEATING,
            OvenCyclePhaseInterface::OVEN_PHASE_COOKING,
            OvenCyclePhaseInterface::OVEN_PHASE_CLEANING,
            0x80,
            0x81
        };
        uint8_t cyclePhase = OvenCyclePhaseInterface::OVEN_PHASE_PREHEATING;
        m_ovenCyclePhaseIntfControllee->SetSupportedCyclePhases(supportedCyclePhase);
        m_ovenCyclePhaseIntfControllee->SetCyclePhase(cyclePhase);
    }

    if (m_rapidModeIntfControllee) {
        m_rapidModeIntfControllee->SetRapidMode(false);
    }

    if (m_remoteControllabilityIntfControllee) {
        m_remoteControllabilityIntfControllee->SetIsControllable(true);
    }

    if (m_soilLevelIntfControllee) {
        uint8_t initialMaxLvl = 5;
        uint8_t targetLevel = 0;

        std::vector<uint8_t> selectableLevels;
        for (uint8_t i = 0; i <= initialMaxLvl; i++)
            selectableLevels.push_back(i);

        m_soilLevelIntfControllee->SetMaxLevel(initialMaxLvl);
        m_soilLevelIntfControllee->SetSelectableLevels(selectableLevels);
        m_soilLevelIntfControllee->SetTargetLevel(targetLevel);
    }

    if (m_spinSpeedLevelIntfControllee) {
        uint8_t initialMaxLvl = 5;
        uint8_t targetLevel = 0;

        std::vector<uint8_t> selectableLevels;
        for (uint8_t i = 0; i <= initialMaxLvl; i++)
            selectableLevels.push_back(i);

        m_spinSpeedLevelIntfControllee->SetMaxLevel(initialMaxLvl);
        m_spinSpeedLevelIntfControllee->SetSelectableLevels(selectableLevels);
        m_spinSpeedLevelIntfControllee->SetTargetLevel(targetLevel);

    }

    if (m_timerIntfControllee) {
        m_timerIntfControllee->SetReferenceTimer(0);
    }

    if (m_waterLevelIntfControllee) {

        WaterLevelInterface::WaterLevelSupplySource supplySource = WaterLevelInterface::SUPPLY_SOURCE_TANK;
        uint8_t maxLvl = 5;
        uint8_t currentLvl = 0;

        m_waterLevelIntfControllee->SetMaxLevel(maxLvl);
        m_waterLevelIntfControllee->SetCurrentLevel(currentLvl);
        m_waterLevelIntfControllee->SetSupplySource(supplySource);
    }
    if (m_alertsIntfControllee) {
        AlertsInterface::Alerts alerts;
        AlertsInterface::AlertRecord aRecord;

        aRecord.severity = AlertsInterface::ALERT_SEVERITY_WARRNING;
        aRecord.alertCode = 0x8000;
        aRecord.needAcknowledgement = false;
        alerts.push_back(aRecord);

        aRecord.severity = AlertsInterface::ALERT_SEVERITY_ALARM;
        aRecord.alertCode = 0x8001;
        aRecord.needAcknowledgement = false;
        alerts.push_back(aRecord);

        aRecord.severity = AlertsInterface::ALERT_SEVERITY_FAULT;
        aRecord.alertCode = 0x8002;
        aRecord.needAcknowledgement = true;
        alerts.push_back(aRecord);

        m_alertsIntfControllee->SetAlerts(alerts);
    }
    if (m_currentAirQualityIntfControllee) {
        uint8_t contaminatType = CurrentAirQualityInterface::CONTAMINANT_TYPE_CH20;
        double maxValue = 30.0;
        double minValue = 10.0;
        double currentValue = 15.0;
        double precision = 10;
        uint16_t updateMinTime = 1;

        m_currentAirQualityIntfControllee->SetContaminantType(contaminatType);
        m_currentAirQualityIntfControllee->SetMaxValue(maxValue);
        m_currentAirQualityIntfControllee->SetMinValue(minValue);
        m_currentAirQualityIntfControllee->SetCurrentValue(currentValue);
        m_currentAirQualityIntfControllee->SetPrecision(precision);
        m_currentAirQualityIntfControllee->SetUpdateMinTime(updateMinTime);
    }

    if (m_currentAirQualityLevelIntfControllee) {
        uint8_t contaminatType = CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH20;
        uint8_t maxLevel = 30;
        uint8_t currentLevel = 15;

        m_currentAirQualityLevelIntfControllee->SetContaminantType(contaminatType);
        m_currentAirQualityLevelIntfControllee->SetCurrentLevel(currentLevel);
        m_currentAirQualityLevelIntfControllee->SetMaxLevel(maxLevel);
    }

    if (m_currentHumidityIntfControllee) {
        uint8_t currentValue = 0;
        uint8_t maxValue = 100;
        m_currentHumidityIntfControllee->SetCurrentValue(currentValue);
        m_currentHumidityIntfControllee->SetMaxValue(maxValue);
    }

    if (m_targetHumidityIntfControllee) {
        uint8_t maxvalue = 80;
        uint8_t minvalue = 10;
        uint8_t targetvalue = 20;
        uint8_t stepvalue = 5;

        m_targetHumidityIntfControllee->SetMaxValue(maxvalue);
        m_targetHumidityIntfControllee->SetMinValue(minvalue);
        m_targetHumidityIntfControllee->SetTargetValue(targetvalue);
        m_targetHumidityIntfControllee->SetStepValue(stepvalue);
        m_targetHumidityIntfControllee->SetStrategyOfAdjustingTargetValue(TargetHumidityIntfControllee::ROUNDING_TO_NEAREST_VALUE);
    }

    if (m_targetTemperatureLevelIntfControllee) {
        uint8_t maxlevel = 80;
        uint8_t targetlevel = 20;

        m_targetTemperatureLevelIntfControllee->SetMaxLevel(maxlevel);
        m_targetTemperatureLevelIntfControllee->SetTargetLevel(targetlevel);
    }

    if (m_moistureOutputLevelIntfControllee) {
        uint8_t value = 0;
        uint8_t autoMode = MoistureOutputLevelInterface::OFF;

        m_moistureOutputLevelIntfControllee->SetMoistureOutputLevel(value);
        m_moistureOutputLevelIntfControllee->SetAutoMode(autoMode);
    }

    if (m_filterStatusIntfControllee) {
        uint16_t expectedLifeInDays = 30;
        bool isCleanable = true;
        uint8_t orderPercentage = 0;
        qcc::String manufacturer = "HAE";
        uint8_t lifeRemaining = 100;

        m_filterStatusIntfControllee->SetExpectedLifeInDays(expectedLifeInDays);
        m_filterStatusIntfControllee->SetIsCleanable(isCleanable);
        m_filterStatusIntfControllee->SetOrderPercentage(orderPercentage);
        m_filterStatusIntfControllee->SetManufacturer(manufacturer);
        m_filterStatusIntfControllee->SetLifeRemaining(lifeRemaining);
    }

    if (m_hvacFanModeIntfControllee) {
        HvacFanModeInterface::SupportedModes supportedModes;
        supportedModes.push_back(HvacFanModeInterface::HVAC_FAN_MODE_AUTO);
        supportedModes.push_back(HvacFanModeInterface::HVAC_FAN_MODE_CIRCULATION);
        m_hvacFanModeIntfControllee->SetSupportedModes(supportedModes);
        uint16_t mode = HvacFanModeInterface::HVAC_FAN_MODE_AUTO;
        m_hvacFanModeIntfControllee->SetMode(mode);
    }

    if (m_plugInUnitsIntfControllee) {
        PlugInUnitsInterface::PlugInInfo info1, info2;
        info1.objectPath = "/Hae/IntegratedControllee";
        info1.deviceId = 1;
        info1.pluggedIn = false;

        info2.objectPath = "/Hae/IntegratedControllee";
        info2.deviceId = 2;
        info2.pluggedIn = true;

        PlugInUnitsInterface::PlugInUnits units;
        units.push_back(info1);
        units.push_back(info2);

        m_plugInUnitsIntfControllee->SetPlugInUnits(units);
    }

    if (m_rapidModeTimedIntfControllee) {
        uint16_t maxSetMinutes = 30;
        uint16_t rapidModeMinutesRemaining = 15;

        m_rapidModeTimedIntfControllee->SetMaxSetMinutes(maxSetMinutes);
        m_rapidModeTimedIntfControllee->SetRapidModeMinutesRemaining(rapidModeMinutesRemaining);
    }
}

QStatus FillAboutData(HaeAboutData* aboutData)
{
    String const defaultLanguage = "en";
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
