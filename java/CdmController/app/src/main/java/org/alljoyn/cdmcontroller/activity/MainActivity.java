/*
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.widget.Toast;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.adapter.DeviceInfoAdapter;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.logic.DeviceManager;
import org.alljoyn.cdmcontroller.logic.IntentKeys;
import org.alljoyn.cdmcontroller.logic.MessageType;

import java.util.Collection;
import java.util.UUID;


public class MainActivity extends AppCompatActivity implements TabLayout.OnTabSelectedListener
{
    private final static String TAG = "CDM_MainActivity";
    public final static String ROOT_NAV_NAME = "CDM Controller";
    public final static String APP_BAR_SUBTITLE = "";

    private BroadcastReceiver receiver = null;
    private IntentFilter filter = new IntentFilter();
    private DeviceInfoAdapter deviceAdapter = null;
    private Fragment deviceListFragment = null;
    private Toolbar toolbar = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        toolbar = (Toolbar)findViewById(R.id.toolbar);
        toolbar.setTitle(MainActivity.ROOT_NAV_NAME);
        toolbar.setTitleTextColor(Color.WHITE);
        toolbar.setSubtitleTextColor(Color.WHITE);
        setSupportActionBar(toolbar);

        deviceAdapter = new DeviceInfoAdapter(this);

        TabLayout tabLayout = (TabLayout)findViewById(R.id.tab_layout);
        tabLayout.addTab(tabLayout.newTab().setText("Devices"));
        tabLayout.addTab(tabLayout.newTab().setText("Groups"));
        tabLayout.setTabGravity(TabLayout.GRAVITY_FILL);
        tabLayout.setOnTabSelectedListener(this);
        tabLayout.getTabAt(0).select();

        this.receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(MessageType.ON_DEVICE_ADDED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceAdded : " + deviceId.toString());
                    Toast.makeText(MainActivity.this, "Device is Added : " + deviceId.toString(), Toast.LENGTH_SHORT).show();
                    Device device = DeviceManager.getInstance().getDevice(deviceId);
                    deviceAdapter.add(device);
                    deviceAdapter.notifyDataSetChanged();
                } else if (action.equals(MessageType.ON_DEVICE_REMOVED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceRemoved : " + deviceId.toString());
                    Toast.makeText(MainActivity.this, "Device is Removed : " + deviceId.toString(), Toast.LENGTH_SHORT).show();
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

    @Override
    public void onTabSelected(TabLayout.Tab tab) {
        Log.d(TAG, "Selecting tab");
        handleFragmentSwitch(tab);
    }

    @Override
    public void onTabReselected(TabLayout.Tab tab) {
        Log.d(TAG, "Reselected tab");
        if(deviceListFragment == null) {
            handleFragmentSwitch(tab);
        }
    }

    @Override
    public void onTabUnselected(TabLayout.Tab tab) {
        Log.d(TAG, "Unselected tab");

        if(deviceListFragment != null){
            FragmentManager manager = getSupportFragmentManager();
            manager.popBackStack(null, FragmentManager.POP_BACK_STACK_INCLUSIVE);
            FragmentTransaction fragmentTransaction = manager.beginTransaction();
            fragmentTransaction.remove(deviceListFragment);
            fragmentTransaction.commit();
            deviceListFragment = null;
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
                    MainActivity.this.deviceAdapter.addAll(devices);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            MainActivity.this.deviceAdapter.notifyDataSetChanged();
                        }
                    });
                }
            }
        }.execute();
    }

    private void handleFragmentSwitch(TabLayout.Tab tab) {
        FragmentManager manager = getSupportFragmentManager();
        FragmentTransaction fragmentTransaction = manager.beginTransaction();

        if (tab.getText().equals("Devices")) {
            Log.d(TAG, "Devices tab selected");

            deviceListFragment = new DeviceListFragment();
            ((DeviceListFragment)deviceListFragment).setDeviceAdapter(deviceAdapter);
        } else {
            Log.d(TAG, "Groups tab selected");

            deviceListFragment = new DeviceGroupListFragment();
        }

        fragmentTransaction.replace(R.id.fragmentView, deviceListFragment);
        fragmentTransaction.commit();
    }

    public void setActionBarTitle(String title) {
        this.toolbar.setSubtitle(title);
    }
}