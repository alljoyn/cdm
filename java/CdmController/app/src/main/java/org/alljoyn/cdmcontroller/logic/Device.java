/*
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
 */

package org.alljoyn.cdmcontroller.logic;

import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.PropertiesChangedListener;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.bus.annotation.Signature;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.smartspaces.EnumBase;

import java.util.List;
import java.util.UUID;

public interface Device {
    class DeviceTypeDescription {
        @Position(0)
        @Signature("u")
        public int deviceType;

        @Position(1)
        @Signature("o")
        public String objectPath;
    }
    static enum DeviceType implements EnumBase<Integer> {
        ROOT(0),
        OTHER(1),
        REFRIGERATOR(2, R.drawable.icon_refrigerator),
        FREEZER(3, R.drawable.icon_freezer),
        ICE_MAKER(4),
        AIR_CONDIRIONER(5, R.drawable.icon_air_conditioner),
        THERMOSTAT(6),
        HUMIDIFIER(7),
        DEHUMIDIFIER(8),
        AIR_PURIFIER(9),
        ELECTRIC_FAN(10),
        AIR_QUALITY_MONITOR(11),
        CLOTHES_WASHER(12),
        CLOTHES_DRYER(13),
        CLOTHES_WASHER_DRYER(14),
        DISH_WASHER(15, R.drawable.icon_dish_washer),
        ROBOT_CLEANER(16),
        OVEN(17, R.drawable.icon_oven),
        COOKER_HOOD(18),
        COOKTOP(19, R.drawable.icon_cooktop),
        FOOD_PROBE(20),
        TELEVISION(21, R.drawable.icon_tv),
        SET_TOP_BOX(22, R.drawable.icon_set_top_box);

        private int value;
        private int icon;

        private DeviceType(int value) {
            this.value = value;
            this.icon = 0;
        }

        private DeviceType(int value, int icon) {
            this.value = value;
            this.icon = icon;
        }
        @Override
        public Integer toValue() {
            return this.value;
        }

        public int getIconID() {
            return this.icon;
        }
    };

    static class AboutDataKeys {
        static final String COUNTRY_OF_PRODUCTION   = "CountryOfProduction";
        static final String CORPORATE_BRAND         = "CorporateBrand";
        static final String PRODUCT_BRAND           = "ProductBrand";
        static final String LOCATION                = "Location";
        static final String DEVICE_TYPE_DESCRIPTION = "DeviceTypeDescription";
    }

    public String getName();
    public String getFriendlyName();
    public List<DeviceType> getDeviceType(String objPath);
    public UUID getId();
    public AboutObjectDescription[] getAboutObjectDescriptions();

    public Object getInterface(String objPath, String intfName);

    public Status registerSignal(BusObject obj);
    public Status registerPropertiesChangedSignal(PropertiesChangedListener listener);

    public void unregisterSignal(BusObject obj);
    public void unregisterPropertiesChangedSignal(PropertiesChangedListener listener);
}