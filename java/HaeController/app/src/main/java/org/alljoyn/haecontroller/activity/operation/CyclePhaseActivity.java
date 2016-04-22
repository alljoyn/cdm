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

package org.alljoyn.haecontroller.activity.operation;

import android.view.View;

import org.alljoyn.haecontroller.activity.InterfaceActivity;
import org.alljoyn.haecontroller.view.method.MethodView;
import org.alljoyn.haecontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.haecontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.smartspaces.operation.DishWashingCyclePhase;

public class CyclePhaseActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(InterfaceActivity.CustomView properties, CustomView methods) {
        View cyclePhaseView = new ReadOnlyValuePropertyView(this, this.intf, "CyclePhase", null);
        properties.addView(cyclePhaseView);

        View supportedCyclePhasesView = new ReadOnlyEnumPropertyView(this, this.intf, "SupportedCyclePhases", DishWashingCyclePhase.CyclePhase.class);
        properties.addView(supportedCyclePhasesView);

        View getVendorPhasesDescriptionView = new MethodView(this, this.intf, "GetVendorPhasesDescription", "languageTag");
        methods.addView(getVendorPhasesDescriptionView);
    }
}
