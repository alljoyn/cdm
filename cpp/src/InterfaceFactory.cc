/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Debug.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>

#include <alljoyn/hae/LogModule.h>

#include "InterfaceFactory.h"

// Controllee
#include "interfaces/operation/ChannelIntfControlleeImpl.h"
#include "interfaces/operation/AudioVideoInputIntfControlleeImpl.h"
#include "interfaces/operation/AudioVolumeIntfControlleeImpl.h"
#include "interfaces/operation/ClosedStatusIntfControlleeImpl.h"
#include "interfaces/input/HidIntfControlleeImpl.h"
#include "interfaces/operation/OnControlIntfControlleeImpl.h"
#include "interfaces/operation/OffControlIntfControlleeImpl.h"
#include "interfaces/operation/OnOffStatusIntfControlleeImpl.h"
#include "interfaces/operation/ClimateControlModeIntfControlleeImpl.h"
#include "interfaces/operation/ResourceSavingIntfControlleeImpl.h"
#include "interfaces/operation/FanSpeedLevelIntfControlleeImpl.h"
#include "interfaces/operation/BatteryStatusIntfControlleeImpl.h"
#include "interfaces/environment/CurrentTemperatureIntfControlleeImpl.h"
#include "interfaces/environment/TargetTemperatureIntfControlleeImpl.h"
#include "interfaces/environment/WindDirectionIntfControlleeImpl.h"
#include "interfaces/operation/AirRecirculationModeIntfControlleeImpl.h"
#include "interfaces/operation/RepeatModeIntfControlleeImpl.h"
#include "interfaces/operation/RobotCleaningCyclePhaseIntfControlleeImpl.h"
#include "interfaces/operation/CurrentPowerIntfControlleeImpl.h"
#include "interfaces/operation/EnergyUsageIntfControlleeImpl.h"
#include "interfaces/operation/CycleControlIntfControlleeImpl.h"
#include "interfaces/operation/RemoteControllabilityIntfControlleeImpl.h"
#include "interfaces/operation/RapidModeIntfControlleeImpl.h"
#include "interfaces/operation/SoilLevelIntfControlleeImpl.h"
#include "interfaces/operation/SpinSpeedLevelIntfControlleeImpl.h"
#include "interfaces/environment/WaterLevelIntfControlleeImpl.h"
#include "interfaces/operation/HeatingZoneIntfControlleeImpl.h"
#include "interfaces/operation/DishWashingCyclePhaseIntfControlleeImpl.h"
#include "interfaces/operation/LaundryCyclePhaseIntfControlleeImpl.h"
#include "interfaces/operation/OvenCyclePhaseIntfControlleeImpl.h"
#include "interfaces/operation/TimerIntfControlleeImpl.h"
#include "interfaces/operation/AlertsIntfControlleeImpl.h"

// Controller
#include "interfaces/operation/AudioVolumeIntfControllerImpl.h"
#include "interfaces/operation/ChannelIntfControllerImpl.h"
#include "interfaces/operation/AudioVideoInputIntfControllerImpl.h"
#include "interfaces/operation/ClosedStatusIntfControllerImpl.h"
#include "interfaces/input/HidIntfControllerImpl.h"
#include "interfaces/operation/OnControlIntfControllerImpl.h"
#include "interfaces/operation/OffControlIntfControllerImpl.h"
#include "interfaces/operation/OnOffStatusIntfControllerImpl.h"
#include "interfaces/operation/ClimateControlModeIntfControllerImpl.h"
#include "interfaces/operation/ResourceSavingIntfControllerImpl.h"
#include "interfaces/operation/FanSpeedLevelIntfControllerImpl.h"
#include "interfaces/operation/BatteryStatusIntfControllerImpl.h"
#include "interfaces/environment/CurrentTemperatureIntfControllerImpl.h"
#include "interfaces/environment/TargetTemperatureIntfControllerImpl.h"
#include "interfaces/environment/WindDirectionIntfControllerImpl.h"
#include "interfaces/operation/AirRecirculationModeIntfControllerImpl.h"
#include "interfaces/operation/RepeatModeIntfControllerImpl.h"
#include "interfaces/operation/RobotCleaningCyclePhaseIntfControllerImpl.h"
#include "interfaces/operation/CurrentPowerIntfControllerImpl.h"
#include "interfaces/operation/EnergyUsageIntfControllerImpl.h"
#include "interfaces/operation/CycleControlIntfControllerImpl.h"
#include "interfaces/operation/RemoteControllabilityIntfControllerImpl.h"
#include "interfaces/operation/RapidModeIntfControllerImpl.h"
#include "interfaces/operation/SoilLevelIntfControllerImpl.h"
#include "interfaces/operation/SpinSpeedLevelIntfControllerImpl.h"
#include "interfaces/environment/WaterLevelIntfControllerImpl.h"
#include "interfaces/operation/HeatingZoneIntfControllerImpl.h"
#include "interfaces/operation/DishWashingCyclePhaseIntfControllerImpl.h"
#include "interfaces/operation/LaundryCyclePhaseIntfControllerImpl.h"
#include "interfaces/operation/OvenCyclePhaseIntfControllerImpl.h"
#include "interfaces/operation/TimerIntfControllerImpl.h"
#include "interfaces/operation/AlertsIntfControllerImpl.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {

InterfaceFactory* InterfaceFactory::s_instance(0);

InterfaceFactory* InterfaceFactory::GetInstance()
{
    if (!s_instance) {
        s_instance = new InterfaceFactory();
    }
    return s_instance;
}

InterfaceFactory::InterfaceFactory() :
    m_busAttachment(0)
{
    // Controller
    m_controllerCreators[AUDIO_VOLUME_INTERFACE] = static_cast<CreateIntfControllerFptr>(&AudioVolumeIntfControllerImpl::CreateInterface);
    m_controllerCreators[CHANNEL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&ChannelIntfControllerImpl::CreateInterface);
    m_controllerCreators[AUDIO_VIDEO_INPUT_INTERFACE] = static_cast<CreateIntfControllerFptr>(&AudioVideoInputIntfControllerImpl::CreateInterface);
    m_controllerCreators[HID_INTERFACE] = static_cast<CreateIntfControllerFptr>(&HidIntfControllerImpl::CreateInterface);
    m_controllerCreators[ON_CONTROL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&OnControlIntfControllerImpl::CreateInterface);
    m_controllerCreators[OFF_CONTROL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&OffControlIntfControllerImpl::CreateInterface);
    m_controllerCreators[ON_OFF_STATUS_INTERFACE] = static_cast<CreateIntfControllerFptr>(&OnOffStatusIntfControllerImpl::CreateInterface);
    m_controllerCreators[FAN_SPEED_LEVEL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&FanSpeedLevelIntfControllerImpl::CreateInterface);
    m_controllerCreators[CURRENT_TEMPERATURE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&CurrentTemperatureIntfControllerImpl::CreateInterface);
    m_controllerCreators[TARGET_TEMPERATURE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&TargetTemperatureIntfControllerImpl::CreateInterface);
    m_controllerCreators[WIND_DIRECTION_INTERFACE] = static_cast<CreateIntfControllerFptr>(&WindDirectionIntfControllerImpl::CreateInterface);
    m_controllerCreators[RESOURCE_SAVING_INTERFACE] = static_cast<CreateIntfControllerFptr>(&ResourceSavingIntfControllerImpl::CreateInterface);
    m_controllerCreators[CLIMATE_CONTROL_MODE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&ClimateControlModeIntfControllerImpl::CreateInterface);
    m_controllerCreators[BATTERY_STATUS_INTERFACE] = static_cast<CreateIntfControllerFptr>(&BatteryStatusIntfControllerImpl::CreateInterface);
    m_controllerCreators[AIR_RECIRCULATION_MODE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&AirRecirculationModeIntfControllerImpl::CreateInterface);
    m_controllerCreators[REPEAT_MODE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&RepeatModeIntfControllerImpl::CreateInterface);
    m_controllerCreators[CLOSED_STATUS_INTERFACE] = static_cast<CreateIntfControllerFptr>(&ClosedStatusIntfControllerImpl::CreateInterface);
    m_controllerCreators[ROBOT_CLEANING_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&RobotCleaningCyclePhaseIntfControllerImpl::CreateInterface);
    m_controllerCreators[CURRENT_POWER_INTERFACE] = static_cast<CreateIntfControllerFptr>(&CurrentPowerIntfControllerImpl::CreateInterface);
    m_controllerCreators[ENERGY_USAGE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&EnergyUsageIntfControllerImpl::CreateInterface);
    m_controllerCreators[CYCLE_CONTROL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&CycleControlIntfControllerImpl::CreateInterface);
    m_controllerCreators[REMOTE_CONTROLLABILITY_INTERFACE] = static_cast<CreateIntfControllerFptr>(&RemoteControllabilityIntfControllerImpl::CreateInterface);
    m_controllerCreators[RAPID_MODE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&RapidModeIntfControllerImpl::CreateInterface);
    m_controllerCreators[SOIL_LEVEL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&SoilLevelIntfControllerImpl::CreateInterface);
    m_controllerCreators[SPIN_SPEED_LEVEL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&SpinSpeedLevelIntfControllerImpl::CreateInterface);
    m_controllerCreators[WATER_LEVEL_INTERFACE] = static_cast<CreateIntfControllerFptr>(&WaterLevelIntfControllerImpl::CreateInterface);
    m_controllerCreators[HEATING_ZONE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&HeatingZoneIntfControllerImpl::CreateInterface);
    m_controllerCreators[DISH_WASHING_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&DishWashingCyclePhaseIntfControllerImpl::CreateInterface);
    m_controllerCreators[LAUNDRY_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&LaundryCyclePhaseIntfControllerImpl::CreateInterface);
    m_controllerCreators[OVEN_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControllerFptr>(&OvenCyclePhaseIntfControllerImpl::CreateInterface);
    m_controllerCreators[TIMER_INTERFACE] = static_cast<CreateIntfControllerFptr>(&TimerIntfControllerImpl::CreateInterface);
    m_controllerCreators[ALERTS_INTERFACE] = static_cast<CreateIntfControllerFptr>(&AlertsIntfControllerImpl::CreateInterface);

    // Controllee
    m_controlleeCreators[CHANNEL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&ChannelIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[AUDIO_VIDEO_INPUT_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&AudioVideoInputIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[AUDIO_VOLUME_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&AudioVolumeIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[HID_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&HidIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[CURRENT_TEMPERATURE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&CurrentTemperatureIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[TARGET_TEMPERATURE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&TargetTemperatureIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[WIND_DIRECTION_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&WindDirectionIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[RESOURCE_SAVING_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&ResourceSavingIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[CLIMATE_CONTROL_MODE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&ClimateControlModeIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[FAN_SPEED_LEVEL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&FanSpeedLevelIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[ON_CONTROL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&OnControlIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[OFF_CONTROL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&OffControlIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[ON_OFF_STATUS_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&OnOffStatusIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[BATTERY_STATUS_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&BatteryStatusIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[AIR_RECIRCULATION_MODE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&AirRecirculationModeIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[REPEAT_MODE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&RepeatModeIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[CLOSED_STATUS_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&ClosedStatusIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[ROBOT_CLEANING_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&RobotCleaningCyclePhaseIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[CURRENT_POWER_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&CurrentPowerIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[ENERGY_USAGE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&EnergyUsageIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[CYCLE_CONTROL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&CycleControlIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[REMOTE_CONTROLLABILITY_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&RemoteControllabilityIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[RAPID_MODE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&RapidModeIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[SOIL_LEVEL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&SoilLevelIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[SPIN_SPEED_LEVEL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&SpinSpeedLevelIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[WATER_LEVEL_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&WaterLevelIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[HEATING_ZONE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&HeatingZoneIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[DISH_WASHING_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&DishWashingCyclePhaseIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[LAUNDRY_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&LaundryCyclePhaseIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[OVEN_CYCLE_PHASE_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&OvenCyclePhaseIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[TIMER_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&TimerIntfControlleeImpl::CreateInterface);
    m_controlleeCreators[ALERTS_INTERFACE] = static_cast<CreateIntfControlleeFptr>(&AlertsIntfControlleeImpl::CreateInterface);
}

InterfaceFactory::InterfaceFactory(const InterfaceFactory& src)
{
    m_busAttachment = src.m_busAttachment;
}

InterfaceFactory& InterfaceFactory::operator=(const InterfaceFactory& src)
{
    m_busAttachment = src.m_busAttachment;
    return *this;
}

QStatus InterfaceFactory::InitInterfaceFactory(BusAttachment* busAttachment)
{
    if (!busAttachment) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: bus attachment is null.", __func__));
        return ER_BAD_ARG_1;
    }
    m_busAttachment = busAttachment;
    return ER_OK;
}

CreateIntfControlleeFptr InterfaceFactory::GetCreateIntfControlleeFptr(const HaeInterfaceType type)
{
    map<HaeInterfaceType, CreateIntfControlleeFptr>::iterator it;

    it = m_controlleeCreators.find(type);
    if (it == m_controlleeCreators.end()) {
        QCC_LogError(ER_FAIL, ("%s: could not find interface", __func__));
        return NULL;
    }

    return it->second;
}

CreateIntfControllerFptr InterfaceFactory::GetCreateIntfControllerFptr(const HaeInterfaceType type)
{
    map<HaeInterfaceType, CreateIntfControllerFptr>::iterator it;

    it = m_controllerCreators.find(type);
    if (it == m_controllerCreators.end()) {
        QCC_LogError(ER_FAIL, ("%s: could not find interface", __func__));
        return NULL;
    }

    return it->second;
}

HaeInterface* InterfaceFactory::CreateIntfControllee(const HaeInterfaceType type, InterfaceControlleeListener& listener, HaeBusObject& haeBusObject)
{
    HaeInterface* interface = NULL;
    QStatus status = ER_OK;

    if (!m_busAttachment) {
        QCC_LogError(ER_FAIL, ("%s: could not initialize controllee", __func__));
        return NULL;
    }

    CreateIntfControlleeFptr handler = GetCreateIntfControlleeFptr(type);
    if (!handler) {
        QCC_LogError(status, ("%s: could not find interface", __func__));
        return NULL;
    }

    interface = handler(*m_busAttachment, listener, haeBusObject);
    if (!interface) {
        QCC_LogError(status, ("%s: could not create interface", __func__));
        return NULL;
    }

    status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not init interface", __func__));
        delete interface;
        return NULL;
    }

    return interface;
}

HaeInterface* InterfaceFactory::CreateIntfController(const HaeInterfaceType type, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject)
{
    HaeInterface* interface = NULL;
    QStatus status = ER_OK;

    if (!m_busAttachment) {
        QCC_LogError(ER_FAIL, ("%s: could not initialized controllee", __func__));
        return NULL;
    }

    CreateIntfControllerFptr handler = GetCreateIntfControllerFptr(type);
    if (!handler) {
        QCC_LogError(status, ("%s: could not find interface", __func__));
        return NULL;
    }

    interface = handler(*m_busAttachment, listener, haeProxyObject);
    if (!interface) {
        QCC_LogError(status, ("%s: could not create interface", __func__));
        return NULL;
    }

    status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not init interface", __func__));
        delete interface;
        return NULL;
    }

    return interface;
}

void InterfaceFactory::RegisterVendorDefinedIntfControllee(const HaeInterfaceType type, CreateIntfControlleeFptr createIntfControllee)
{
    m_controlleeCreators[type] = createIntfControllee;
}

void InterfaceFactory::RegisterVendorDefinedIntfController(const HaeInterfaceType type, CreateIntfControllerFptr createIntfController)
{
    m_controllerCreators[type] = createIntfController;
}

}
}
