/*
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.adapter.DeviceInfoAdapter;
import org.alljoyn.cdmcontroller.dialog.DeviceListDialogFragment;
import org.alljoyn.cdmcontroller.dialog.DialogListener;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.logic.DeviceGroupImpl;
import org.alljoyn.cdmcontroller.logic.DeviceManager;
import org.alljoyn.cdmcontroller.logic.IntentKeys;

import java.util.ArrayList;


public class DeviceGroupListFragment extends Fragment implements DialogListener{
    private final static String TAG = "CDM_DeviceGroupListFrag";
    private ListView deviceListView;
    private DeviceInfoAdapter deviceGroupAdapter = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG, "DeviceGroupList created");
        deviceGroupAdapter = new DeviceInfoAdapter(getActivity());
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View inflatedView = inflater.inflate(R.layout.page_item_list, container, false);

        deviceListView = (ListView) inflatedView.findViewById(R.id.item_list);
        deviceListView.setAdapter(deviceGroupAdapter);

        deviceListView.setOnItemClickListener(new AdapterView.OnItemClickListener(){
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Device device = (Device)parent.getItemAtPosition(position);
                Log.d(TAG, "Group '" + device.getName() + "' clicked");

                Bundle bundle = new Bundle();
                bundle.putSerializable(IntentKeys.DEVICE_ID, device.getId());

                InterfaceListFragment interfaceListFragment = new InterfaceListFragment();
                interfaceListFragment.setArguments(bundle);

                FragmentManager manager = getFragmentManager();
                FragmentTransaction transaction = manager.beginTransaction();
                transaction.replace(R.id.fragmentView, interfaceListFragment);
                transaction.addToBackStack(null);
                transaction.commit();
            }
        });

        FloatingActionButton fab = (FloatingActionButton) inflatedView.findViewById(R.id.add_btn);
        fab.setVisibility(View.VISIBLE);

        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DeviceListDialogFragment deviceListDialogFragment = new DeviceListDialogFragment();
                deviceListDialogFragment.setSelectableDevices(DeviceManager.getInstance().getDevices());
                deviceListDialogFragment.setTargetFragment(DeviceGroupListFragment.this, 0);
                deviceListDialogFragment.show(getFragmentManager(), "DeviceListDialogFragment");
            }
        });

        ((MainActivity)getActivity()).setActionBarTitle(MainActivity.APP_BAR_SUBTITLE);

        return inflatedView;
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public void onDialogPositiveClick(DialogFragment dialogFragment) {
        DeviceListDialogFragment fragment = (DeviceListDialogFragment)dialogFragment;
        ArrayList<Device> devices = fragment.getSelectedDevices();
        String groupName = fragment.getGroupName();
        if(devices.size() > 0 && groupName.length() > 0) {
            DeviceGroupImpl deviceGroup = new DeviceGroupImpl(groupName, devices);
            DeviceManager.getInstance().addDevice(deviceGroup);
            deviceGroupAdapter.add(deviceGroup);
            Log.d(TAG, "Successfully created new group");
            deviceGroupAdapter.notifyDataSetChanged();
        } else {
            Toast.makeText(getActivity(), "Failed to create group", Toast.LENGTH_LONG).show();
        }
    }

    @Override
    public void onDialogNegativeClick(DialogFragment dialogFragment) {
        Log.d(TAG, "User cancelled group creation");
    }
}