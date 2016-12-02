/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef CDMINTERFACETYPES_H_
#define CDMINTERFACETYPES_H_

#include <map>
#include <qcc/String.h>

namespace ajn {
namespace services {

typedef uint32_t CdmInterfaceType;

/**
 * DeviceType
 */
typedef enum {
    UNDEFINED_INTERFACE             = 0,
    //INPUT
    HID_INTERFACE,

    //Environment
    CURRENT_AIR_QUALITY_INTERFACE,
    CURRENT_AIR_QUALITY_LEVEL_INTERFACE,
    CURRENT_HUMIDITY_INTERFACE,
    CURRENT_TEMPERATURE_INTERFACE,
    TARGET_HUMIDITY_INTERFACE,
    TARGET_TEMPERATURE_INTERFACE,
    TARGET_TEMPERATURE_LEVEL_INTERFACE,
    WATER_LEVEL_INTERFACE,
    WIND_DIRECTION_INTERFACE,

    //Operation
    AIR_RECIRCULATION_MODE_INTERFACE,
    ALERTS_INTERFACE,
    AUDIO_VIDEO_INPUT_INTERFACE,
    AUDIO_VOLUME_INTERFACE,
    BATTERY_STATUS_INTERFACE,
    CHANNEL_INTERFACE,
    CLIMATE_CONTROL_MODE_INTERFACE,
    CLOSED_STATUS_INTERFACE,
    CURRENT_POWER_INTERFACE,
    CYCLE_CONTROL_INTERFACE,
    DISH_WASHING_CYCLE_PHASE_INTERFACE,
    ENERGY_USAGE_INTERFACE,
    FAN_SPEED_LEVEL_INTERFACE,
    FILTER_STATUS_INTERFACE,
    HEATING_ZONE_INTERFACE,
    HVAC_FAN_MODE_INTERFACE,
    LAUNDRY_CYCLE_PHASE_INTERFACE,
    MOISTURE_OUTPUT_LEVEL_INTERFACE,
    ON_OFF_STATUS_INTERFACE,
    OFF_CONTROL_INTERFACE,
    ON_CONTROL_INTERFACE,
    OVEN_CYCLE_PHASE_INTERFACE,
    PLUG_IN_UNITS_INTERFACE,
    RAPID_MODE_INTERFACE,
    RAPID_MODE_TIMED_INTERFACE,
    REMOTE_CONTROLLABILITY_INTERFACE,
    REPEAT_MODE_INTERFACE,
    RESOURCE_SAVING_INTERFACE,
    ROBOT_CLEANING_CYCLE_PHASE_INTERFACE,
    SOIL_LEVEL_INTERFACE,
    SPIN_SPEED_LEVEL_INTERFACE,
    TIMER_INTERFACE,

    //UserInterfaceSettings
    LANGUAGE_DISPLAY_INTERFACE,
    TEMPERATURE_DISPLAY_INTERFACE,
    TIME_DISPLAY_INTERFACE,

    //////////////////////////////
    LAST_BASIC_INTERFACE_TYPE,
    NUMBER_OF_BASIC_INTERFACE_TYPE,
    MAX_BASIC_INTERFACE_TYPE        = NUMBER_OF_BASIC_INTERFACE_TYPE,

    // Vendor Defined Interface
    VENDOR_DEFINED_INTERFACE        = 0x1000,

} CdmInterfaceTypes;

extern std::map<CdmInterfaceType, qcc::String> InterfaceTypesMap;

} //namespace services
} //namespace ajn

#endif /* CDMINTERFACETYPES_H_ */