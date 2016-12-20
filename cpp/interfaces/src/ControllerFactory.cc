/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <qcc/Debug.h>

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/common/LogModule.h>

#include "interfaces/controller/ControllerFactory.h"

#include "interfaces/controller/operation/AirRecirculationModeIntfController.h"
#include "interfaces/controller/operation/AlertsIntfController.h"
#include "interfaces/controller/operation/AudioVideoInputIntfController.h"
#include "interfaces/controller/operation/AudioVolumeIntfController.h"
#include "interfaces/controller/operation/BatteryStatusIntfController.h"
#include "interfaces/controller/operation/BrightnessIntfController.h"
#include "interfaces/controller/operation/ChannelIntfController.h"
#include "interfaces/controller/operation/ClimateControlModeIntfController.h"
#include "interfaces/controller/operation/ClosedStatusIntfController.h"
#include "interfaces/controller/operation/ColorIntfController.h"
#include "interfaces/controller/operation/ColorTemperatureIntfController.h"
#include "interfaces/controller/operation/CurrentPowerIntfController.h"
#include "interfaces/controller/operation/CycleControlIntfController.h"
#include "interfaces/controller/operation/DishWashingCyclePhaseIntfController.h"
#include "interfaces/controller/operation/EnergyUsageIntfController.h"
#include "interfaces/controller/operation/FanSpeedLevelIntfController.h"
#include "interfaces/controller/operation/FilterStatusIntfController.h"
#include "interfaces/controller/operation/HeatingZoneIntfController.h"
#include "interfaces/controller/operation/HvacFanModeIntfController.h"
#include "interfaces/controller/operation/LaundryCyclePhaseIntfController.h"
#include "interfaces/controller/operation/LockControlIntfController.h"
#include "interfaces/controller/operation/LockedStatusIntfController.h"
#include "interfaces/controller/operation/MoistureOutputLevelIntfController.h"
#include "interfaces/controller/operation/OffControlIntfController.h"
#include "interfaces/controller/operation/OnControlIntfController.h"
#include "interfaces/controller/operation/OnOffStatusIntfController.h"
#include "interfaces/controller/operation/OvenCyclePhaseIntfController.h"
#include "interfaces/controller/operation/PlugInUnitsIntfController.h"
#include "interfaces/controller/operation/RapidModeIntfController.h"
#include "interfaces/controller/operation/RapidModeTimedIntfController.h"
#include "interfaces/controller/operation/RemoteControllabilityIntfController.h"
#include "interfaces/controller/operation/RepeatModeIntfController.h"
#include "interfaces/controller/operation/ResourceSavingIntfController.h"
#include "interfaces/controller/operation/RobotCleaningCyclePhaseIntfController.h"
#include "interfaces/controller/operation/SoilLevelIntfController.h"
#include "interfaces/controller/operation/SpinSpeedLevelIntfController.h"
#include "interfaces/controller/operation/TimerIntfController.h"
#include "interfaces/controller/operation/TriggerSensorIntfController.h"
#include "interfaces/controller/operation/UnlockControlIntfController.h"
#include "interfaces/controller/environment/CurrentAirQualityIntfController.h"
#include "interfaces/controller/environment/CurrentAirQualityLevelIntfController.h"
#include "interfaces/controller/environment/CurrentHumidityIntfController.h"
#include "interfaces/controller/environment/CurrentTemperatureIntfController.h"
#include "interfaces/controller/environment/TargetHumidityIntfController.h"
#include "interfaces/controller/environment/TargetTemperatureIntfController.h"
#include "interfaces/controller/environment/TargetTemperatureLevelIntfController.h"
#include "interfaces/controller/environment/WaterLevelIntfController.h"
#include "interfaces/controller/environment/WindDirectionIntfController.h"

using namespace std;
using namespace qcc;

namespace ajn {
namespace services {
//======================================================================

ControllerFactory& ControllerFactory::Instance()
{
    static ControllerFactory* s_instance = 0;

    if (!s_instance) {
        s_instance = new ControllerFactory();
    }

    return *s_instance;
}



ControllerFactory::ControllerFactory() :
    m_busAttachment(0)
{
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.AirRecirculationMode"] = static_cast<CreateIntfControllerFptr>(&AirRecirculationModeIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.Alerts"] = static_cast<CreateIntfControllerFptr>(&AlertsIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.AudioVideoInput"] = static_cast<CreateIntfControllerFptr>(&AudioVideoInputIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.AudioVolume"] = static_cast<CreateIntfControllerFptr>(&AudioVolumeIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.BatteryStatus"] = static_cast<CreateIntfControllerFptr>(&BatteryStatusIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.Brightness"] = static_cast<CreateIntfControllerFptr>(&BrightnessIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.Channel"] = static_cast<CreateIntfControllerFptr>(&ChannelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.ClimateControlMode"] = static_cast<CreateIntfControllerFptr>(&ClimateControlModeIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.ClosedStatus"] = static_cast<CreateIntfControllerFptr>(&ClosedStatusIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.Color"] = static_cast<CreateIntfControllerFptr>(&ColorIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.ColorTemperature"] = static_cast<CreateIntfControllerFptr>(&ColorTemperatureIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.CurrentPower"] = static_cast<CreateIntfControllerFptr>(&CurrentPowerIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.CycleControl"] = static_cast<CreateIntfControllerFptr>(&CycleControlIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase"] = static_cast<CreateIntfControllerFptr>(&DishWashingCyclePhaseIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.EnergyUsage"] = static_cast<CreateIntfControllerFptr>(&EnergyUsageIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.FanSpeedLevel"] = static_cast<CreateIntfControllerFptr>(&FanSpeedLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.FilterStatus"] = static_cast<CreateIntfControllerFptr>(&FilterStatusIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.HeatingZone"] = static_cast<CreateIntfControllerFptr>(&HeatingZoneIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.HvacFanMode"] = static_cast<CreateIntfControllerFptr>(&HvacFanModeIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase"] = static_cast<CreateIntfControllerFptr>(&LaundryCyclePhaseIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.LockControl"] = static_cast<CreateIntfControllerFptr>(&LockControlIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.LockedStatus"] = static_cast<CreateIntfControllerFptr>(&LockedStatusIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel"] = static_cast<CreateIntfControllerFptr>(&MoistureOutputLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.OffControl"] = static_cast<CreateIntfControllerFptr>(&OffControlIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.OnControl"] = static_cast<CreateIntfControllerFptr>(&OnControlIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.OnOffStatus"] = static_cast<CreateIntfControllerFptr>(&OnOffStatusIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.OvenCyclePhase"] = static_cast<CreateIntfControllerFptr>(&OvenCyclePhaseIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.PlugInUnits"] = static_cast<CreateIntfControllerFptr>(&PlugInUnitsIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.RapidMode"] = static_cast<CreateIntfControllerFptr>(&RapidModeIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.RapidModeTimed"] = static_cast<CreateIntfControllerFptr>(&RapidModeTimedIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.RemoteControllability"] = static_cast<CreateIntfControllerFptr>(&RemoteControllabilityIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.RepeatMode"] = static_cast<CreateIntfControllerFptr>(&RepeatModeIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.ResourceSaving"] = static_cast<CreateIntfControllerFptr>(&ResourceSavingIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase"] = static_cast<CreateIntfControllerFptr>(&RobotCleaningCyclePhaseIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.SoilLevel"] = static_cast<CreateIntfControllerFptr>(&SoilLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel"] = static_cast<CreateIntfControllerFptr>(&SpinSpeedLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.Timer"] = static_cast<CreateIntfControllerFptr>(&TimerIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.TriggerSensor"] = static_cast<CreateIntfControllerFptr>(&TriggerSensorIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Operation.UnlockControl"] = static_cast<CreateIntfControllerFptr>(&UnlockControlIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.CurrentAirQuality"] = static_cast<CreateIntfControllerFptr>(&CurrentAirQualityIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel"] = static_cast<CreateIntfControllerFptr>(&CurrentAirQualityLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.CurrentHumidity"] = static_cast<CreateIntfControllerFptr>(&CurrentHumidityIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.CurrentTemperature"] = static_cast<CreateIntfControllerFptr>(&CurrentTemperatureIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.TargetHumidity"] = static_cast<CreateIntfControllerFptr>(&TargetHumidityIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.TargetTemperature"] = static_cast<CreateIntfControllerFptr>(&TargetTemperatureIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel"] = static_cast<CreateIntfControllerFptr>(&TargetTemperatureLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.WaterLevel"] = static_cast<CreateIntfControllerFptr>(&WaterLevelIntfController::CreateInterface);
    m_controllerCreators["org.alljoyn.SmartSpaces.Environment.WindDirection"] = static_cast<CreateIntfControllerFptr>(&WindDirectionIntfController::CreateInterface);
}



QStatus ControllerFactory::InitControllerFactory(BusAttachment* busAttachment)
{
    if (!busAttachment) {
        QCC_LogError(ER_BAD_ARG_1, ("%s: bus attachment is null.", __func__));
        return ER_BAD_ARG_1;
    }
    m_busAttachment = busAttachment;
    return ER_OK;
}



CreateIntfControllerFptr ControllerFactory::GetCreateIntfControllerFptr(const string& ifaceName)
{
    auto iter = m_controllerCreators.find(ifaceName);

    if (iter == m_controllerCreators.end()) {
        QCC_LogError(ER_FAIL, ("%s: could not find interface", __func__));
        return nullptr;
    }

    return iter->second;
}



Ref<CdmInterface> ControllerFactory::CreateIntfController(const string& ifaceName, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> cdmProxyObject)
{
    QStatus status = ER_OK;

    if (!m_busAttachment) {
        QCC_LogError(ER_FAIL, ("%s: could not initialized controller", __func__));
        return nullptr;
    }

    CreateIntfControllerFptr handler = GetCreateIntfControllerFptr(ifaceName);
    if (!handler) {
        QCC_LogError(status, ("%s: could not find interface", __func__));
        return nullptr;
    }

    auto interface = handler(*m_busAttachment, listener, cdmProxyObject);
    if (!interface) {
        QCC_LogError(status, ("%s: could not create interface", __func__));
        return nullptr;
    }

    status = interface->Init();
    if (status != ER_OK) {
        QCC_LogError(status, ("%s: could not init interface", __func__));
        return nullptr;
    }

    return interface;
}



QStatus ControllerFactory::RegisterIntfController(const std::string& interfaceName, CreateIntfControllerFptr createIntfController)
{
    auto iter = m_controllerCreators.find(interfaceName);

    if (iter != m_controllerCreators.end()) {
        return ER_DUPLICATE_KEY;
    }

    m_controllerCreators[interfaceName] = createIntfController;
    return ER_OK;
}



QStatus ControllerFactory::UnregisterIntfController(const std::string& interfaceName, CreateIntfControllerFptr createIntfController)
{
    auto iter = m_controllerCreators.find(interfaceName);

    if (iter == m_controllerCreators.end()) {
        return ER_FAIL;
    }

    m_controllerCreators.erase(interfaceName);
    return ER_OK;
}

//======================================================================
}
}