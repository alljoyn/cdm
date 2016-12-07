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

package org.alljoyn.cdmcontroller.fragment.environment;

import android.view.View;

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.cdmcontroller.activity.InterfaceFragment;
//import org.alljoyn.cdmcontroller.view.property.MinMaxPropertyView;
//import org.alljoyn.cdmcontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteValuePropertyView;
//import org.alljoyn.cdmcontroller.view.property.ReadWriteEnumPropertyView;
//import org.alljoyn.cdmcontroller.view.property.ReadWriteBoolPropertyView;
import org.alljoyn.cdmcontroller.view.method.MethodView;
import org.alljoyn.smartspaces.environment.CurrentAirQuality;

// This generated fragment presents the view to the best of its ability.
// It is up to the developer to use different PropertyViews to provide better UX
// and to specify the units of properties (absent on the interface descriptions).
public class CurrentAirQualityFragment extends InterfaceFragment {
    private static final String INTERFACE_NAME = "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality";

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View contaminantTypeView = new ReadOnlyEnumPropertyView<>(getActivity(), this.device, this.objPath, INTERFACE_NAME, "ContaminantType", CurrentAirQuality.ContaminantType.class);
        properties.addView(contaminantTypeView);

        View currentValueView = new ReadOnlyValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "CurrentValue", null);
        properties.addView(currentValueView);

        View minValueView = new ReadOnlyValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "MinValue", null);
        properties.addView(minValueView);

        View maxValueView = new ReadOnlyValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "MaxValue", null);
        properties.addView(maxValueView);

        View precisionView = new ReadOnlyValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "Precision", null);
        properties.addView(precisionView);

        View updateMinTimeView = new ReadOnlyValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "UpdateMinTime", null);
        properties.addView(updateMinTimeView);

    }

}