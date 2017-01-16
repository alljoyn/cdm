/******************************************************************************
 * 
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 * 
 *    SPDX-License-Identifier: Apache-2.0
 * 
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 * 
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 * 
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/


#ifndef CDMCONFIG_H_
#define CDMCONFIG_H_

#include <vector>

namespace ajn {
namespace services {

/**
 * DeviceType
 */
typedef enum {
    ROOT                 = 0,
    OTHER                = 1,
    REFRIGERATOR         = 2,
    FREEZER              = 3,
    ICE_MAKER            = 4,
    AIR_CONDITIONER      = 5,
    THERMOSTAT           = 6,
    HUMIDIFIER           = 7,
    DEHUMIDIFIER         = 8,
    AIR_PURIFIER         = 9,
    ELECTRIC_FAN         = 10,
    AIR_QUALITY_MONITOR  = 11,
    CLOTHES_WASHER       = 12,
    CLOTHES_DRYER        = 13,
    CLOTHES_WASHER_DRYER = 14,
    DISH_WASHER          = 15,
    ROBOT_CLEANER        = 16,
    OVEN                 = 17,
    COOKER_HOOD          = 18,
    COOKTOP              = 19,
    FOOD_PROBE           = 20,
    TELEVISION           = 21,
    SET_TOP_BOX          = 22,
    LAMP                 = 23,
    LOCK                 = 24,
    SWITCH               = 25,
    DOOR_SENSOR          = 26,
    WINDOW_SENSOR        = 27,
    MOTION_SENSOR        = 28,
    POWER_OUTLET         = 29,
    SMOKE_DETECTOR       = 30,
    SPEAKER              = 31,
    WATER_SENSOR         = 32,

    NUMBER_OF_DEVICE_TYPE,
    MAX_DEVICE_TYPE      = NUMBER_OF_DEVICE_TYPE - 1
} DeviceType;

typedef std::vector<DeviceType> InterestDeviceList;

}  // services
}  // ajn

#endif //  CDMCONFIG_H_
