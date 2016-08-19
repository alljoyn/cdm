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

import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.method.MethodView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;

public class TimerActivity extends InterfaceActivity {

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {

        View referenceTimerView = new ReadOnlyValuePropertyView(this, this.intf, "ReferenceTimer", "seconds");
        properties.addView(referenceTimerView);

        View targetTimeToStartView = new ReadOnlyValuePropertyView(this, this.intf, "TargetTimeToStart", "seconds");
        properties.addView(targetTimeToStartView);

        View targetTimeToStopView = new ReadOnlyValuePropertyView(this, this.intf, "TargetTimeToStop", "seconds");
        properties.addView(targetTimeToStopView);

        View estimatedTimeToEndView = new ReadOnlyValuePropertyView(this, this.intf, "EstimatedTimeToEnd", "seconds");
        properties.addView(estimatedTimeToEndView);

        View runningTimeView = new ReadOnlyValuePropertyView(this, this.intf, "RunningTime", "seconds");
        properties.addView(runningTimeView);

        View targetDurationView = new ReadOnlyValuePropertyView(this, this.intf, "TargetDuration", "seconds");
        properties.addView(targetDurationView);

        View setTargetTimeToStartView = new MethodView(this, this.intf, "SetTargetTimeToStart", "targetTimeToStart");
        methods.addView(setTargetTimeToStartView);

        View setTargetTimeToStopView = new MethodView(this, this.intf, "SetTargetTimeToStop", "targetTimeToStop");
        methods.addView(setTargetTimeToStopView);

    }
}
