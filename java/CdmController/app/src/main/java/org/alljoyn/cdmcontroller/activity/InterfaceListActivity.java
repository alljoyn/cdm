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

import org.alljoyn.bus.AboutObjectDescription;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.adapter.InterfaceListAdapter;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.logic.DeviceManager;
import org.alljoyn.cdmcontroller.logic.DeviceManagerImpl;
import org.alljoyn.cdmcontroller.logic.IntentKeys;
import org.alljoyn.cdmcontroller.logic.MessageType;

import java.util.UUID;

public class InterfaceListActivity extends Activity {
    private final static String TAG = "CDM_IntfListActivity";

    private BroadcastReceiver receiver = null;
    private IntentFilter filter = new IntentFilter();

    private UUID deviceId = null;

    private InterfaceListAdapter aboutObjectDescriptionAdapter = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.page_item_list);

        deviceId = (UUID) getIntent().getSerializableExtra(IntentKeys.DEVICE_ID);

        if (deviceId == null) {
            Toast.makeText(this, "UUID is null", Toast.LENGTH_LONG).show();
            this.finish();
            return;
        }

        final ListView interfaceListView = (ListView) findViewById(R.id.item_list);
        TextView title = (TextView) findViewById(R.id.navtitleback_title_text);
        title.setText("InterfaceList");
        findViewById(R.id.navtitleback_title_arrorw).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                InterfaceListActivity.this.finish();
            }
        });

        aboutObjectDescriptionAdapter = new InterfaceListAdapter(this);

        interfaceListView.setAdapter(this.aboutObjectDescriptionAdapter);

        interfaceListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                InterfaceListAdapter.Item item = aboutObjectDescriptionAdapter.getItem(position);
                if (item.level == 0) {
                    aboutObjectDescriptionAdapter.foldItem(position);
                } else if (item.level == 1) {
                    Class<?> clazz = InterfaceActivityMap.activityMap.get(item.detailInfo);
                    if (clazz == null) {
                        Toast.makeText(InterfaceListActivity.this, item.title + "\n is not implemented!!", Toast.LENGTH_LONG).show();
                        return;
                    }
                    final Intent intent = new Intent(InterfaceListActivity.this, clazz);
                    intent.putExtra(IntentKeys.DEVICE_ID, InterfaceListActivity.this.deviceId);
                    intent.putExtra(IntentKeys.OBJECT_PATH, item.parent.detailInfo);
                    intent.putExtra(IntentKeys.INTERFACE_NAME, item.detailInfo);
                    InterfaceListActivity.this.startActivity(intent);
                } else {
                    assert (false);
                }
            }
        });

        this.receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(MessageType.ON_DEVICE_REMOVED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceRemoved : " + deviceId.toString());
                    if (InterfaceListActivity.this.deviceId.equals(deviceId)) {
                        Toast.makeText(InterfaceListActivity.this, "Exit this Page\nCurrent Device is Removed", Toast.LENGTH_SHORT).show();
                        InterfaceListActivity.this.finish();
                    }
                }
            }
        };

        loadInterfaceInfoList();
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
        if (this.receiver != null) {
            registerReceiver(this.receiver, this.filter);
        }
        if (DeviceManagerImpl.getInstance().getDevice(deviceId) == null)
            finish();
    }

    private void loadInterfaceInfoList() {
        AsyncTask<UUID, Void, Device> excute = new AsyncTask<UUID, Void, Device>() {

            @Override
            protected Device doInBackground(UUID... params) {
                return DeviceManager.getInstance().getDevice(params[0]);
            }

            @Override
            protected void onPostExecute(Device device) {
                if (device != null) {
                    for (AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                        if (desc.path.toUpperCase().contains("CDM")) {
                            InterfaceListActivity.this.aboutObjectDescriptionAdapter.add(desc.path, desc.interfaces, device.getDeviceType(desc.path));
                        }
                    }
                }
            }
        }.execute(this.deviceId);
    }
}