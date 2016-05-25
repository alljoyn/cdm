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

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.haecontroller.activity.InterfaceActivity;
import org.alljoyn.haecontroller.view.method.MethodView;
import org.alljoyn.haecontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.haecontroller.view.property.SupportedValuesPropertyView;

public class ChannelActivity extends InterfaceActivity {

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        View channelIdView = new SupportedValuesPropertyView(this, this.intf, "ChannelId", null, 0, "getChannelList", 0, 100);
        properties.addView(channelIdView);

        View totalNumberOfChannelsView = new ReadOnlyValuePropertyView(this, this.intf, "TotalNumberOfChannels", null);
        properties.addView(totalNumberOfChannelsView);

        View getChannelListView = new MethodView(this, this.intf, "GetChannelList", "startingRecord", "numRecords");
        methods.addView(getChannelListView);
    }

    @BusSignalHandler(iface = "org.alljoyn.smartspaces.operation.Channel", signal = "ChannelListChanged")
    public void channelListChanged() {
        notifyEvent("ChannelListChanged");
    }
}
