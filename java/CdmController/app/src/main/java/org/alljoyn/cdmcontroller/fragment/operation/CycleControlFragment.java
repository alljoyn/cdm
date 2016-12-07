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

package org.alljoyn.cdmcontroller.fragment.operation;

import android.view.View;

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.cdmcontroller.activity.InterfaceFragment;
//import org.alljoyn.cdmcontroller.view.property.MinMaxPropertyView;
//import org.alljoyn.cdmcontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlySupportedEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteValuePropertyView;
//import org.alljoyn.cdmcontroller.view.property.ReadWriteEnumPropertyView;
//import org.alljoyn.cdmcontroller.view.property.ReadWriteBoolPropertyView;
import org.alljoyn.cdmcontroller.view.method.MethodView;
import org.alljoyn.smartspaces.operation.CycleControl;

// This generated fragment presents the view to the best of its ability.
// It is up to the developer to use different PropertyViews to provide better UX
// and to specify the units of properties (absent on the interface descriptions).
public class CycleControlFragment extends InterfaceFragment {
    private static final String INTERFACE_NAME = "org.alljoyn.SmartSpaces.Operation.CycleControl";

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View operationalStateView = new ReadOnlySupportedEnumPropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "OperationalState", "SupportedOperationalStates", CycleControl.OperationalState.class);
        properties.addView(operationalStateView);

        View executeOperationalCommandView = new MethodView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "ExecuteOperationalCommand", "command");
        methods.addView(executeOperationalCommandView);

    }

    @BusSignalHandler(iface = "org.alljoyn.SmartSpaces.Operation.CycleControl", signal = "EndOfCycle")
    public void endOfCycle() {
        notifyEvent("EndOfCycle");
    }

}