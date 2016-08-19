/*
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
 */

package org.alljoyn.haecontroller.activity.environment;


import android.view.View;

import org.alljoyn.haecontroller.activity.InterfaceActivity;
import org.alljoyn.haecontroller.util.HaeUtil;
import org.alljoyn.haecontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.haecontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.smartspaces.environment.CurrentAirQuality;

public class CurrentAirQualityActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {

        CurrentAirQuality intf = (CurrentAirQuality)this.intf;

        CurrentAirQuality.ContaminantType type = (CurrentAirQuality.ContaminantType)HaeUtil.findEnum(intf.getContaminantType(), CurrentAirQuality.ContaminantType.class);

        View contaminantTypeView = new ReadOnlyEnumPropertyView(this, this.intf, "ContaminantType", CurrentAirQuality.ContaminantType.class);
        properties.addView(contaminantTypeView);

        View currentValueView = new ReadOnlyValuePropertyView(this, this.intf, "CurrentValue", type.getUnit());
        properties.addView(currentValueView);

        View maxValueView = new ReadOnlyValuePropertyView(this, this.intf, "MaxValue", type.getUnit());
        properties.addView(maxValueView);

        View minValueView = new ReadOnlyValuePropertyView(this, this.intf, "MinValue", type.getUnit());
        properties.addView(minValueView);

        View precisionView = new ReadOnlyValuePropertyView(this, this.intf, "Precision", type.getUnit());
        properties.addView(precisionView);

        View updateMinTimeView = new ReadOnlyValuePropertyView(this, this.intf, "UpdateMinTime", "ms");
        properties.addView(updateMinTimeView);
    }
}
