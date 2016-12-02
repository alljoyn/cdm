#include <iostream>
#include <map>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>

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
//--------------------------------------------------
#include "TimeDisplayListener.h"
#include "TemperatureDisplayListener.h"
#include "LanguageDisplayListener.h"
//--------------------------------------------------

#include <alljoyn/cdm/interfaces/input/HidIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/BatteryStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClimateControlModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CurrentPowerIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OffControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OnOffStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RepeatModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/ClosedStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/LaundryCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/OvenCyclePhaseIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RemoteControllabilityIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/SoilLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/TimerIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/PlugInUnitsIntfControllee.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentHumidityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfControllee.h>
#include <alljoyn/cdm/interfaces/environment/CurrentAirQualityLevelIntfControllee.h>

//--------------------------------------------------
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfControllee.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfControllee.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControllee.h>
//--------------------------------------------------

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


//--------------------------------------------------
    TimeDisplayListener m_timeDisplayListener;
    TemperatureDisplayListener m_temperatureDisplayListener;
    LanguageDisplayListener m_languageDisplayListener;
//--------------------------------------------------

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

//--------------------------------------------------
    TimeDisplayIntfControllee* m_timeDisplayIntfControllee;
    TemperatureDisplayIntfControllee* m_temperatureDisplayIntfControllee;
    LanguageDisplayIntfControllee* m_languageDisplayIntfControllee;
//--------------------------------------------------
  public:
    IntegratedControllee(BusAttachment* bus, CdmAboutData* aboutData);
    virtual ~IntegratedControllee();
    void CreateInterfaces();
    void SetInitialProperty();
};

IntegratedControllee::IntegratedControllee(BusAttachment* bus, CdmAboutData* aboutData) :
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
    m_plugInUnitsIntfControllee(NULL), m_rapidModeTimedIntfControllee(NULL), m_timeDisplayIntfControllee(NULL), m_temperatureDisplayIntfControllee(NULL),
    m_languageDisplayIntfControllee(NULL)
{
}

IntegratedControllee::~IntegratedControllee()
{
}

void IntegratedControllee::CreateInterfaces()
{
    CdmInterface* intf = NULL;
    CdmControllee* cdmControllee = GetControllee();
    if (!cdmControllee) {
        return;
    }

    intf = cdmControllee->CreateInterface(HID_INTERFACE, "/Cdm/IntegratedControllee", m_hidListener);
    m_hidIntfControllee = static_cast<HidIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CURRENT_TEMPERATURE_INTERFACE, "/Cdm/IntegratedControllee", m_currentTemperatureListener);
    m_currentTemperatureIntfControllee = static_cast<CurrentTemperatureIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TARGET_TEMPERATURE_INTERFACE, "/Cdm/IntegratedControllee", m_targetTemperatureListener);
    m_targetTemperatureIntfControllee = static_cast<TargetTemperatureIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(WIND_DIRECTION_INTERFACE, "/Cdm/IntegratedControllee", m_windDirectionListener);
    m_windDirectionIntfControllee = static_cast<WindDirectionIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(AIR_RECIRCULATION_MODE_INTERFACE, "/Cdm/IntegratedControllee", m_airRecirculationModeListener);
    m_airRecirculationModeIntfControllee = static_cast<AirRecirculationModeIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(AUDIO_VIDEO_INPUT_INTERFACE, "/Cdm/IntegratedControllee", m_audioVideoInputListener);
    m_audioVideoInputIntfControllee = static_cast<AudioVideoInputIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(AUDIO_VOLUME_INTERFACE, "/Cdm/IntegratedControllee", m_audioVolumeListener);
    m_audioVolumeIntfControllee = static_cast<AudioVolumeIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(BATTERY_STATUS_INTERFACE, "/Cdm/IntegratedControllee", m_batteryStatusListener);
    m_batteryStatusIntfControllee = static_cast<BatteryStatusIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CHANNEL_INTERFACE, "/Cdm/IntegratedControllee", m_channelListener);
    m_channelIntfControllee = static_cast<ChannelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CLIMATE_CONTROL_MODE_INTERFACE, "/Cdm/IntegratedControllee", m_climateControlModeListener);
    m_climateControlModeIntfControllee = static_cast<ClimateControlModeIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CURRENT_POWER_INTERFACE, "/Cdm/IntegratedControllee", m_currentPowerListener);
    m_currentPowerIntfControllee = static_cast<CurrentPowerIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(ENERGY_USAGE_INTERFACE, "/Cdm/IntegratedControllee", m_energyUsageListener);
    m_energyUsageIntfControllee = static_cast<EnergyUsageIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(FAN_SPEED_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_fanSpeedLevelListener);
    m_fanSpeedLevelIntfControllee = static_cast<FanSpeedLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(OFF_CONTROL_INTERFACE, "/Cdm/IntegratedControllee", m_offControlListener);
    m_offControlIntfControllee = static_cast<OffControlIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(ON_CONTROL_INTERFACE, "/Cdm/IntegratedControllee", m_onControlListener);
    m_onControlIntfControllee = static_cast<OnControlIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(ON_OFF_STATUS_INTERFACE, "/Cdm/IntegratedControllee", m_onOffStatusListener);
    m_onOffStatusIntfControllee = static_cast<OnOffStatusIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(REPEAT_MODE_INTERFACE, "/Cdm/IntegratedControllee", m_repeatModeListener);
    m_repeatModeIntfControllee = static_cast<RepeatModeIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(RESOURCE_SAVING_INTERFACE, "/Cdm/IntegratedControllee", m_resourceSavingListener);
    m_resourceSavingIntfControllee = static_cast<ResourceSavingIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(ROBOT_CLEANING_CYCLE_PHASE_INTERFACE, "/Cdm/IntegratedControllee", m_robotCleaningCyclePhaseListener);
    m_robotCleaningCyclePhaseIntfControllee = static_cast<RobotCleaningCyclePhaseIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CLOSED_STATUS_INTERFACE, "/Cdm/IntegratedControllee", m_closedStatusListener);
    m_closedStatusIntfControllee = static_cast<ClosedStatusIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CYCLE_CONTROL_INTERFACE, "/Cdm/IntegratedControllee", m_cycleControlListener);
    m_cycleControlIntfControllee = static_cast<CycleControlIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(DISH_WASHING_CYCLE_PHASE_INTERFACE, "/Cdm/IntegratedControllee", m_dishWashingCycleListener);
    m_dishWashingCyclePhaseIntfControllee = static_cast<DishWashingCyclePhaseIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(HEATING_ZONE_INTERFACE, "/Cdm/IntegratedControllee", m_heatingZoneListener);
    m_heatingZoneIntfControllee = static_cast<HeatingZoneIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(LAUNDRY_CYCLE_PHASE_INTERFACE, "/Cdm/IntegratedControllee", m_laundryCyclePhaseListener);
    m_laundryCyclePhaseIntfControllee = static_cast<LaundryCyclePhaseIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(OVEN_CYCLE_PHASE_INTERFACE, "/Cdm/IntegratedControllee", m_ovenCyclePhaseListener);
    m_ovenCyclePhaseIntfControllee = static_cast<OvenCyclePhaseIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(RAPID_MODE_INTERFACE, "/Cdm/IntegratedControllee", m_rapidModeListener);
    m_rapidModeIntfControllee = static_cast<RapidModeIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(REMOTE_CONTROLLABILITY_INTERFACE, "/Cdm/IntegratedControllee", m_remoteControllabilityListener);
    m_remoteControllabilityIntfControllee = static_cast<RemoteControllabilityIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(SOIL_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_soilLevelListener);
    m_soilLevelIntfControllee = static_cast<SoilLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(SPIN_SPEED_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_spinSpeedLevelListener);
    m_spinSpeedLevelIntfControllee = static_cast<SpinSpeedLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TIMER_INTERFACE, "/Cdm/IntegratedControllee", m_timerListener);
    m_timerIntfControllee = static_cast<TimerIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(WATER_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_waterLevelListener);
    m_waterLevelIntfControllee = static_cast<WaterLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(ALERTS_INTERFACE, "/Cdm/IntegratedControllee", m_alertsListener);
    m_alertsIntfControllee = static_cast<AlertsIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CURRENT_AIR_QUALITY_INTERFACE, "/Cdm/IntegratedControllee", m_currentAirQualityListener);
    m_currentAirQualityIntfControllee = static_cast<CurrentAirQualityIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CURRENT_AIR_QUALITY_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_currentAirQualityLevelListener);
    m_currentAirQualityLevelIntfControllee = static_cast<CurrentAirQualityLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(CURRENT_HUMIDITY_INTERFACE, "/Cdm/IntegratedControllee", m_currentHumidityListener);
    m_currentHumidityIntfControllee = static_cast<CurrentHumidityIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TARGET_HUMIDITY_INTERFACE, "/Cdm/IntegratedControllee", m_targetHumidityListener);
    m_targetHumidityIntfControllee = static_cast<TargetHumidityIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TARGET_TEMPERATURE_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_targetTemperatureLevelListener);
    m_targetTemperatureLevelIntfControllee = static_cast<TargetTemperatureLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(MOISTURE_OUTPUT_LEVEL_INTERFACE, "/Cdm/IntegratedControllee", m_moistureOutputLevelListener);
    m_moistureOutputLevelIntfControllee = static_cast<MoistureOutputLevelIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(FILTER_STATUS_INTERFACE, "/Cdm/IntegratedControllee", m_filterStatusListener);
    m_filterStatusIntfControllee = static_cast<FilterStatusIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(HVAC_FAN_MODE_INTERFACE, "/Cdm/IntegratedControllee", m_hvacFanModeListener);
    m_hvacFanModeIntfControllee = static_cast<HvacFanModeIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(PLUG_IN_UNITS_INTERFACE, "/Cdm/IntegratedControllee", m_plugInUnitsListener);
    m_plugInUnitsIntfControllee = static_cast<PlugInUnitsIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(RAPID_MODE_TIMED_INTERFACE, "/Cdm/IntegratedControllee", m_rapidModeTimedListener);
    m_rapidModeTimedIntfControllee = static_cast<RapidModeTimedIntfControllee*>(intf);

//----------------------------------------------
    intf = cdmControllee->CreateInterface(TIME_DISPLAY_INTERFACE, "/Cdm/IntegratedControllee", m_timeDisplayListener);
    m_timeDisplayIntfControllee = static_cast<TimeDisplayIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(TEMPERATURE_DISPLAY_INTERFACE, "/Cdm/IntegratedControllee", m_temperatureDisplayListener);
    m_temperatureDisplayIntfControllee = static_cast<TemperatureDisplayIntfControllee*>(intf);

    intf = cdmControllee->CreateInterface(LANGUAGE_DISPLAY_INTERFACE, "/Cdm/IntegratedControllee", m_languageDisplayListener);
    m_languageDisplayIntfControllee = static_cast<LanguageDisplayIntfControllee*>(intf);
//----------------------------------------------
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
        inputSource1.sourceType = AudioVideoInputInterface::SOURCE_TYPE_HDMI;
        inputSource1.signalPresence = AudioVideoInputInterface::SIGNAL_PRESENCE_SIGNAL_ABSENT;
        inputSource1.portNumber = 1;
        inputSource1.friendlyName = "HDMI1";
        inputSources.insert(std::pair<uint16_t, AudioVideoInputInterface::InputSource>(inputSource1Id, inputSource1));
        uint16_t inputSource2Id = 8000;
        inputSource2.sourceType = AudioVideoInputInterface::SOURCE_TYPE_TUNER;
        inputSource2.signalPresence = AudioVideoInputInterface::SIGNAL_PRESENCE_SIGNAL_PRESENT;
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
        supportedModes.push_back(ClimateControlModeInterface::MODE_OFF);
        supportedModes.push_back(ClimateControlModeInterface::MODE_COOL);
        m_climateControlModeIntfControllee->SetSupportedModes(supportedModes);
        uint16_t mode = ClimateControlModeInterface::MODE_OFF;
        m_climateControlModeIntfControllee->SetMode(mode);
        uint16_t operationalState = ClimateControlModeInterface::OPERATIONAL_STATE_IDLE;
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
        m_onOffStatusIntfControllee->SetIsOn(onoff);
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
        comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_START);
        comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_STOP);
        comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_PAUSE);
        comm.push_back(CycleControlInterface::OperationalCommands::OPERATIONAL_COMMANDS_RESUME);
        m_cycleControlIntfControllee->SetSupportedCommands(comm);

        CycleControlInterface::SupportedOperationalStates states;
        states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_IDLE);
        states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_WORKING);
        states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_READY_TO_START);
        states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_DELAYED_START);
        states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_PAUSED);
        states.push_back(CycleControlInterface::OperationalState::OPERATIONAL_STATE_END_OF_CYCLE);

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

        WaterLevelInterface::SupplySource supplySource = WaterLevelInterface::SUPPLY_SOURCE_TANK;
        uint8_t maxLvl = 5;
        uint8_t currentLvl = 0;

        m_waterLevelIntfControllee->SetMaxLevel(maxLvl);
        m_waterLevelIntfControllee->SetCurrentLevel(currentLvl);
        m_waterLevelIntfControllee->SetSupplySource(supplySource);
    }
    if (m_alertsIntfControllee) {
        AlertsInterface::Alerts alerts;
        AlertsInterface::AlertRecord aRecord;

        aRecord.severity = AlertsInterface::SEVERITY_WARNING;
        aRecord.alertCode = 0x8000;
        aRecord.needAcknowledgement = false;
        alerts.push_back(aRecord);

        aRecord.severity = AlertsInterface::SEVERITY_ALARM;
        aRecord.alertCode = 0x8001;
        aRecord.needAcknowledgement = false;
        alerts.push_back(aRecord);

        aRecord.severity = AlertsInterface::SEVERITY_FAULT;
        aRecord.alertCode = 0x8002;
        aRecord.needAcknowledgement = true;
        alerts.push_back(aRecord);

        m_alertsIntfControllee->SetAlerts(alerts);
    }
    if (m_currentAirQualityIntfControllee) {
        uint8_t contaminatType = CurrentAirQualityInterface::CONTAMINANT_TYPE_CH2O;
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
        uint8_t contaminatType = CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH2O;
        uint8_t maxLevel = 30;
        uint8_t currentLevel = 15;

        m_currentAirQualityLevelIntfControllee->SetContaminantType(contaminatType);
        m_currentAirQualityLevelIntfControllee->SetMaxLevel(maxLevel);
        m_currentAirQualityLevelIntfControllee->SetCurrentLevel(currentLevel);
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


        TargetTemperatureLevelInterface::TemperatureLevels levels;
        levels.push_back(10);
        levels.push_back(20);
        levels.push_back(50);
        levels.push_back(80);
        m_targetTemperatureLevelIntfControllee->SetMaxLevel(maxlevel);
        m_targetTemperatureLevelIntfControllee->SetTargetLevel(targetlevel);
        m_targetTemperatureLevelIntfControllee->SetSelectableTemperatureLevels(levels);
    }

    if (m_moistureOutputLevelIntfControllee) {
        uint8_t value = 0;
        uint8_t autoMode = MoistureOutputLevelInterface::AUTO_MODE_OFF;

        m_moistureOutputLevelIntfControllee->SetMoistureOutputLevel(value);
        m_moistureOutputLevelIntfControllee->SetAutoMode(autoMode);
    }

    if (m_filterStatusIntfControllee) {
        uint16_t expectedLifeInDays = 30;
        bool isCleanable = true;
        uint8_t orderPercentage = 0;
        qcc::String manufacturer = "CDM";
        uint8_t lifeRemaining = 100;

        m_filterStatusIntfControllee->SetExpectedLifeInDays(expectedLifeInDays);
        m_filterStatusIntfControllee->SetIsCleanable(isCleanable);
        m_filterStatusIntfControllee->SetOrderPercentage(orderPercentage);
        m_filterStatusIntfControllee->SetManufacturer(manufacturer);
        m_filterStatusIntfControllee->SetLifeRemaining(lifeRemaining);
    }

    if (m_hvacFanModeIntfControllee) {
        HvacFanModeInterface::SupportedModes supportedModes;
        supportedModes.push_back(HvacFanModeInterface::MODE_AUTO);
        supportedModes.push_back(HvacFanModeInterface::MODE_CIRCULATION);
        m_hvacFanModeIntfControllee->SetSupportedModes(supportedModes);
        uint16_t mode = HvacFanModeInterface::MODE_AUTO;
        m_hvacFanModeIntfControllee->SetMode(mode);
    }

    if (m_plugInUnitsIntfControllee) {
        PlugInUnitsInterface::PlugInInfo info1, info2;
        info1.objectPath = "/Cdm/IntegratedControllee";
        info1.deviceId = 1;
        info1.pluggedIn = false;

        info2.objectPath = "/Cdm/IntegratedControllee";
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

//----------------------------------------------
    if(m_timeDisplayIntfControllee) {
        uint8_t timeFormat = 0;
        std::vector<uint8_t> supportedTimeFormats;
        supportedTimeFormats.push_back(0);
        supportedTimeFormats.push_back(1);

        m_timeDisplayIntfControllee->SetSupportedDisplayTimeFormats(supportedTimeFormats);
        m_timeDisplayIntfControllee->SetDisplayTimeFormat(timeFormat);
    }

    if(m_temperatureDisplayIntfControllee) {
        uint8_t temperatureUnit = 0;
        std::vector<uint8_t> supportedTemperatureUnits;
        supportedTemperatureUnits.push_back(0);
        supportedTemperatureUnits.push_back(1);
        supportedTemperatureUnits.push_back(2);

        m_temperatureDisplayIntfControllee->SetSupportedDisplayTemperatureUnits(supportedTemperatureUnits);
        m_temperatureDisplayIntfControllee->SetDisplayTemperatureUnit(temperatureUnit);

    }

    if(m_languageDisplayIntfControllee) {
        qcc::String languageDisplay("en");
        std::vector<qcc::String> supportedDisplayLanguages;
        supportedDisplayLanguages.push_back(qcc::String("en"));
        supportedDisplayLanguages.push_back(qcc::String("es"));
        supportedDisplayLanguages.push_back(qcc::String("fr"));

        m_languageDisplayIntfControllee->SetSupportedDisplayLanguages(supportedDisplayLanguages);
        m_languageDisplayIntfControllee->SetDisplayLanguage(languageDisplay);
    }
//----------------------------------------------



}

QStatus FillAboutData(CdmAboutData* aboutData)
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

    // CDM custom metadata fields
    aboutData->SetCountryOfProduction("USA", "en");
    aboutData->SetCorporateBrand("Controllee Brand", "en");
    aboutData->SetProductBrand("IntegratedControllee", "en");
    aboutData->SetLocation("Room1", "en");

    DeviceTypeDescription description;
    description.AddDeviceType(OTHER, "/Cdm/IntegratedControllee");
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

    BusAttachment* bus = new BusAttachment("IntegratedControllee", true);
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
