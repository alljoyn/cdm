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

#include "CdmTest.h"
#include <alljoyn/cdm/CdmAboutData.h>
#include <alljoyn/cdm/DeviceTypeDescription.h>
#include <algorithm>

const static std::map<DeviceType, std::vector<std::vector<qcc::String> > > defaultInterfacesForDeviceType = {
    {ROOT                /* 0  */, { } },
    {OTHER               /* 1  */, { } },
    {REFRIGERATOR        /* 2  */, { {"org.alljoyn.SmartSpaces.Operation.ClosedStatus"} } },
    {FREEZER             /* 3  */, { {"org.alljoyn.SmartSpaces.Operation.ClosedStatus"} } },
    {ICE_MAKER           /* 4  */, { } },
    {AIR_CONDITIONER     /* 5  */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.ClimateControlMode"},
                                     {"org.alljoyn.SmartSpaces.Environment.TargetTemperature"},
                                     {"org.alljoyn.SmartSpaces.Environment.CurrentTemperature"} } },
    {THERMOSTAT          /* 6  */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.ClimateControlMode"},
                                     {"org.alljoyn.SmartSpaces.Environment.TargetTemperature"},
                                     {"org.alljoyn.SmartSpaces.Environment.CurrentTemperature"} } },
    {HUMIDIFIER          /* 7  */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"} } },
    {DEHUMIDIFIER        /* 8  */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Environment.TargetHumidity"},
                                     {"org.alljoyn.SmartSpaces.Environment.CurrentHumidity"} } },
    {AIR_PURIFIER        /* 9  */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"} } },
    {ELECTRIC_FAN        /* 10 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"} } },
    {AIR_QUALITY_MONITOR /* 11 */, { {"org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel"} } },
    {CLOTHES_WASHER      /* 12 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.CycleControl"} } },
    {CLOTHES_DRYER       /* 13 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.CycleControl"} } },
    {CLOTHES_WASHER_DRYER/* 14 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.CycleControl"} } },
    {DISH_WASHER         /* 15 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                      {"org.alljoyn.SmartSpaces.Operation.CycleControl"} } },
    {ROBOT_CLEANER       /* 16 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.CycleControl"} } },
    {OVEN                /* 17 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.CycleControl"} } },
    {COOKER_HOOD         /* 18 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.HvacMode"},
                                     {"org.alljoyn.SmartSpaces.Operation.FanSpeedLevel"} } },
    {COOKTOP             /* 19 */, { {"org.alljoyn.SmartSpaces.Operation.HeatingZone"} } },
    {FOOD_PROBE          /* 20 */, { {"org.alljoyn.SmartSpaces.Environment.TargetTemperature"} } },
    {TELEVISION          /* 21 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"},
                                     {"org.alljoyn.SmartSpaces.Operation.Channel"},
                                     {"org.alljoyn.SmartSpaces.Operation.AudioVolume"} } },
    {SET_TOP_BOX         /* 22 */, { {"org.alljoyn.SmartSpaces.Operation.OnOffStatus"} } }
};


void removeInterface(const qcc::String& interface, std::vector<std::vector<qcc::String> >& interfaces) {
    std::vector<std::vector<qcc::String> >::iterator itr = interfaces.begin();
    for (;itr != interfaces.end(); ++itr) {
        if (std::find(itr->begin(), itr->end(), interface) != itr->end()) {
            interfaces.erase(itr);
            return;
        }
    }
}

bool HasDefaultInterfaces(const qcc::String& objPath, const AboutObjectDescription& description, std::vector<std::vector<qcc::String> >& defaultInterfaces)
{
    size_t path_num = description.GetPaths(NULL, 0);
    const char** paths = new const char*[path_num];
    description.GetPaths(paths, path_num);

    for (size_t i = 0; i < path_num; ++i) {
        if (strstr(paths[i], objPath.c_str()) != paths[i]) {
            continue;
        }

        size_t numInterfaces = description.GetInterfaces(paths[i], NULL, 0);
        const char** interfaces = new const char*[numInterfaces];
        description.GetInterfaces(paths[i], interfaces, numInterfaces);
        for (size_t i = 0; i < numInterfaces; ++i) {
            qcc::String intf = interfaces[i];

            removeInterface(intf, defaultInterfaces);
            if (defaultInterfaces.empty()) {
                delete[] interfaces;
                delete[] paths;
                return true;
            }
        }
        delete[] interfaces;
    }
    delete[] paths;
    return false;
}


TEST_F(CDMTest, CDM_v1_CdmAbout)
{
    WaitForControllee();
    CdmAboutData &aboutData = m_interfaces[0].aboutData;
    AboutObjectDescription &aboutDescription = m_interfaces[0].aboutDescription;
    DeviceTypeDescription* deviceTypeDescription = new DeviceTypeDescription();

    TEST_LOG_1("Check Additional About Metadata Fields");
    {
        char* location;
        TEST_LOG_2("Check existence of Mandatory fields");
        TEST_LOG_3("Location field");
        EXPECT_EQ(aboutData.GetLocation(&location), ER_OK);
        TEST_LOG_3("DeviceTypeDescription field");
        ASSERT_EQ(aboutData.GetDeviceTypeDescription(&deviceTypeDescription), ER_OK);
    }

    TEST_LOG_1("Check existence of Minimum required interfaces of DeviceType");
    {
        DeviceTypeDescription::DescriptionsType::const_iterator itr = deviceTypeDescription->GetDescriptions().begin();
        DeviceTypeDescription::DescriptionsType::const_iterator end = deviceTypeDescription->GetDescriptions().end();
        for (;itr != end; ++itr) {
            std::vector<std::vector<qcc::String> > defaultInterfaces = defaultInterfacesForDeviceType.at(itr->first);
            if (!HasDefaultInterfaces(itr->second, aboutDescription, defaultInterfaces)) {
                qcc::String defIntf = "";
                for (size_t i = 0; i < defaultInterfaces.size(); i++) {
                    for (size_t j = 0; j < defaultInterfaces[i].size(); j++)
                    defIntf += "\n  * " + defaultInterfaces[i][j];
                }
                ADD_FAILURE() << "DUT doesn't have default interfaces of DeviceType[" << itr->first << "] as following :" << defIntf.c_str();
            }
        }
    }
    delete deviceTypeDescription;
}