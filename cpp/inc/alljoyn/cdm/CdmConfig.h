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

    NUMBER_OF_DEVICE_TYPE,
    MAX_DEVICE_TYPE      = NUMBER_OF_DEVICE_TYPE - 1
} DeviceType;

typedef std::vector<DeviceType> InterestDeviceList;

}  // services
}  // ajn

#endif //  CDMCONFIG_H_