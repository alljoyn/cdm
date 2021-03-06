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

package org.alljoyn.cdmcontroller.activity.operation;

import android.view.View;

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.method.MethodSupportedParamEnumView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlySupportedEnumPropertyView;
import org.alljoyn.smartspaces.operation.CycleControl;

public class CycleControlActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View operationalStateView = new ReadOnlySupportedEnumPropertyView(this, this.intf, "OperationalState", "SupportedOperationalStates", CycleControl.OperationalState.class);
        properties.addView(operationalStateView);

        View sendCommandView = new MethodSupportedParamEnumView(this, this.intf, "ExecuteOperationalCommand", new String[]{"SupportedOperationalCommands"}, new Class[]{CycleControl.OperationalCommand.class}, "command");
        methods.addView(sendCommandView);
    }

}
