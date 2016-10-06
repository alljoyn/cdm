/*
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 */

package org.alljoyn.cdmcontroller.activity;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.adapter.DeviceInfoAdapter;
import org.alljoyn.cdmcontroller.logic.DeviceManager;
import org.alljoyn.cdmcontroller.logic.IntentKeys;
import org.alljoyn.cdmcontroller.logic.MessageType;

import java.util.Collection;
import java.util.UUID;

public class DeviceListActivity extends Activity {
    private final static String TAG = "CDM_DeviceListActivity";

    private BroadcastReceiver receiver = null;
    private IntentFilter filter = new IntentFilter();

    private DeviceInfoAdapter deviceAdapter = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.page_item_list);

        ListView deviceListView = (ListView) findViewById(R.id.item_list);
        TextView title = (TextView) findViewById(R.id.navtitleback_title_text);
        title.setText("DeviceList");
        findViewById(R.id.navtitleback_title_arrorw).setVisibility(View.GONE);

        deviceAdapter = new DeviceInfoAdapter(this);

        deviceListView.setAdapter(this.deviceAdapter);

        deviceListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                final Intent intent = new Intent(DeviceListActivity.this, InterfaceListActivity.class);
                intent.putExtra(IntentKeys.DEVICE_ID, DeviceListActivity.this.deviceAdapter.getItem(position).getId());
                DeviceListActivity.this.startActivity(intent);
            }
        });

        this.receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(MessageType.ON_DEVICE_ADDED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceAdded : " + deviceId.toString());
                    Toast.makeText(DeviceListActivity.this, "Device is Added : " + deviceId.toString(), Toast.LENGTH_SHORT).show();
                    Device device = DeviceManager.getInstance().getDevice(deviceId);
                    deviceAdapter.add(device);
                } else if (action.equals(MessageType.ON_DEVICE_REMOVED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceRemoved : " + deviceId.toString());
                    Toast.makeText(DeviceListActivity.this, "Device is Removed : " + deviceId.toString(), Toast.LENGTH_SHORT).show();
                    Device device = DeviceManager.getInstance().getDevice(deviceId);
                    deviceAdapter.remove(device);
                }
            }
        };

        loadDeviceInfoList();
        this.filter.addAction(MessageType.ON_DEVICE_ADDED);
        this.filter.addAction(MessageType.ON_DEVICE_REMOVED);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (this.receiver != null) {
            unregisterReceiver(this.receiver);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        loadDeviceInfoList();
        if (this.receiver != null) {
            registerReceiver(this.receiver, this.filter);
        }
    }

    private void loadDeviceInfoList() {
        new AsyncTask<Void, Void, Collection<Device>>() {

            @Override
            protected Collection<Device> doInBackground(Void... params) {
                return DeviceManager.getInstance().getDevices();
            }

            @Override
            protected void onPostExecute(Collection<Device> devices) {
                if (devices != null) {
                    DeviceListActivity.this.deviceAdapter.addAll(devices);
                }
            }
        }.execute();
    }
}