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

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;
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

public class InterfaceListFragment extends Fragment {
    private final static String TAG = "CDM_IntfListFrag";
    public final static String APP_BAR_SUBTITLE = "Interfaces";

    private BroadcastReceiver receiver = null;
    private IntentFilter filter = new IntentFilter();

    private UUID deviceId = null;

    private InterfaceListAdapter aboutObjectDescriptionAdapter = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        deviceId = (UUID) getArguments().getSerializable(IntentKeys.DEVICE_ID);

        if (deviceId == null) {
            Toast.makeText(getActivity(), "UUID is null", Toast.LENGTH_LONG).show();
            popFromFragmentTransaction();
            return;
        }

        aboutObjectDescriptionAdapter = new InterfaceListAdapter(getActivity());

        this.receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(MessageType.ON_DEVICE_REMOVED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceRemoved : " + deviceId.toString());
                    if (InterfaceListFragment.this.deviceId.equals(deviceId)) {
                        Toast.makeText(getActivity(), "Exit this Page\nCurrent Device is Removed", Toast.LENGTH_SHORT).show();
                        popFromFragmentTransaction();
                    }
                }
            }
        };

        loadInterfaceInfoList();
        this.filter.addAction(MessageType.ON_DEVICE_REMOVED);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View inflatedView = inflater.inflate(R.layout.page_item_list, container, false);

        ListView interfaceListView = (ListView) inflatedView.findViewById(R.id.item_list);

        interfaceListView.setAdapter(this.aboutObjectDescriptionAdapter);

        interfaceListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                InterfaceListAdapter.Item item = aboutObjectDescriptionAdapter.getItem(position);
                if(item.level == 0) {
                    aboutObjectDescriptionAdapter.foldItem(position);
                } else if (item.level == 1) {
                    Class<?> clazz = InterfaceFragmentMap.fragmentMap.get(item.detailInfo);
                    if (clazz == null) {
                        Toast.makeText(getActivity(), item.title + "\n is not implemented!!", Toast.LENGTH_LONG).show();
                        return;
                    }

                    InterfaceFragment interfaceDetailFragment = null;
                    try {
                        interfaceDetailFragment = (InterfaceFragment)clazz.newInstance();
                    } catch (java.lang.InstantiationException e) {
                        e.printStackTrace();
                    } catch (IllegalAccessException e) {
                        e.printStackTrace();
                    }

                    Bundle bundle = new Bundle();
                    bundle.putSerializable(IntentKeys.DEVICE_ID, deviceId);
                    bundle.putSerializable(IntentKeys.OBJECT_PATH, item.parent.detailInfo);
                    bundle.putSerializable(IntentKeys.INTERFACE_NAME, item.detailInfo);

                    interfaceDetailFragment.setArguments(bundle);

                    FragmentManager manager = getFragmentManager();
                    FragmentTransaction transaction = manager.beginTransaction();

                    transaction.replace(R.id.fragmentView, interfaceDetailFragment);
                    transaction.addToBackStack(null);
                    transaction.commit();
                }
            }
        });

        ((MainActivity)getActivity()).setActionBarTitle(InterfaceListFragment.APP_BAR_SUBTITLE);

        return inflatedView;
    }

    @Override
    public void onPause() {
        super.onPause();
        if (this.receiver != null) {
            getActivity().unregisterReceiver(this.receiver);
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        if (this.receiver != null) {
            getActivity().registerReceiver(this.receiver, this.filter);
        }
        if (DeviceManagerImpl.getInstance().getDevice(deviceId) == null)
            popFromFragmentTransaction();
    }

    private void loadInterfaceInfoList() {
        AsyncTask<UUID, Void, Device> execute = new AsyncTask<UUID, Void, Device>() {

            @Override
            protected Device doInBackground(UUID... params) {
                return DeviceManager.getInstance().getDevice(params[0]);
            }

            @Override
            protected void onPostExecute(Device device) {
                if (device != null) {
                    for (AboutObjectDescription desc : device.getAboutObjectDescriptions()) {
                        if (desc.path.toUpperCase().contains("CDM")) {
                            InterfaceListFragment.this.aboutObjectDescriptionAdapter.add(desc.path, desc.interfaces, device.getDeviceType(desc.path));
                            InterfaceListFragment.this.aboutObjectDescriptionAdapter.notifyDataSetChanged();
                        }
                    }
                }
            }
        }.execute(this.deviceId);
    }

    private void popFromFragmentTransaction() {
        FragmentManager manager = getFragmentManager();
        FragmentTransaction transaction = manager.beginTransaction();
        transaction.remove(this);
        transaction.commit();
    }
}