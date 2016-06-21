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
import org.alljoyn.haecontroller.view.property.ReadOnlyValuePropertyView;

public class FilterStatusActivity extends InterfaceActivity {
    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View expectedLifeInDaysView = new ReadOnlyValuePropertyView(this, this.intf, "ExpectedLifeInDays", null);
        properties.addView(expectedLifeInDaysView);

        View isCleanableView = new ReadOnlyValuePropertyView(this, this.intf, "IsCleanable", null);
        properties.addView(isCleanableView);

        View orderPercentageView = new ReadOnlyValuePropertyView(this, this.intf, "OrderPercentage", null);
        properties.addView(orderPercentageView);

        View manufacturerView = new ReadOnlyValuePropertyView(this, this.intf, "Manufacturer", null);
        properties.addView(manufacturerView);

        View partNumberView = new ReadOnlyValuePropertyView(this, this.intf, "PartNumber", null);
        properties.addView(partNumberView);

        View urlView = new ReadOnlyValuePropertyView(this, this.intf, "Url", null);
        properties.addView(urlView);

        View lifeRemainingView = new ReadOnlyValuePropertyView(this, this.intf, "LifeRemaining", null);
        properties.addView(lifeRemainingView);
    }
}
