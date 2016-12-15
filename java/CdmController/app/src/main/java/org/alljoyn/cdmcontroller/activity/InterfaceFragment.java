/*
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 */

package org.alljoyn.cdmcontroller.activity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.Toast;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.PropertiesChangedListener;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.adapter.InterfaceListAdapter;
import org.alljoyn.cdmcontroller.dialog.DialogListener;
import org.alljoyn.cdmcontroller.dialog.PresetListDialog;
import org.alljoyn.cdmcontroller.dialog.PresetNameDialog;
import org.alljoyn.cdmcontroller.logic.Device;
import org.alljoyn.cdmcontroller.logic.DeviceManager;
import org.alljoyn.cdmcontroller.logic.IntentKeys;
import org.alljoyn.cdmcontroller.logic.MessageType;
import org.alljoyn.cdmcontroller.logic.Preset;
import org.alljoyn.cdmcontroller.logic.PresetManager;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentLinkedQueue;

public abstract class InterfaceFragment extends Fragment implements BusObject, DialogListener{
    private final static String TAG = "CDM_IntfActivity";
    private boolean isFinishing = false;

    protected class HandleMsg {
        public static final int PROPERTIES_CHANGED = 0;
        public static final int SIGNAL_EMITTED = 1;
    }

    private BroadcastReceiver receiver = null;
    private IntentFilter filter = new IntentFilter();

    private UUID deviceId = null;
    protected String objPath = null;
    private String intfName = null;

    protected Device device;

    protected ConcurrentLinkedQueue<Map<String, Variant>> changedPropertiesQueue = new ConcurrentLinkedQueue<>();


    private InterfaceListAdapter aboutObjectDescriptionAdapter = null;

    protected Handler m_handler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case HandleMsg.PROPERTIES_CHANGED:
                    while (!changedPropertiesQueue.isEmpty()) {
                        Map<String, Variant> changedProperties = changedPropertiesQueue.poll();
                        for (String name : changedProperties.keySet()) {
                            PropertyView view = InterfaceFragment.this.propertiesView.getPropertyView(name);
                            if (view != null) {
                                if(device.canAddChildren()){
                                    Object propertyValue = device.getProperty(objPath, intfName, name);
                                    view.onPropertiesChangedSignal(name, new Variant(propertyValue));
                                    Toast.makeText(getActivity(), String.format("%s is changed", name), Toast.LENGTH_SHORT).show();
                                }
                                else {
                                    try {
                                        view.onPropertiesChangedSignal(name, changedProperties.get(name));
                                        Toast.makeText(getActivity(), String.format("%s is changed", name), Toast.LENGTH_SHORT).show();
                                    } catch (Exception e) {
                                        e.printStackTrace();
                                    }
                                }
                            }
                        }
                    }
                    break;
                case HandleMsg.SIGNAL_EMITTED:
                    Bundle bundle = msg.getData();
                    String eventName = bundle.getString(IntentKeys.SIGNAL_NAME);
                    String eventValue = bundle.getString(IntentKeys.SIGNAL_VALUE);
                    String toastMsg = eventName + " is occured";
                    if (eventValue != null && !eventValue.isEmpty())
                        toastMsg += "\nwith " + eventValue;
                    Toast.makeText(getActivity(), toastMsg, Toast.LENGTH_SHORT).show();
                    break;
            }
        }
    };

    protected class CustomView<T extends View> {
        private ViewGroup view;

        public CustomView(ViewGroup view) {
            this.view = view;
        }

        public void addView(T view) {
            if (this.view.getChildCount() != 1) {
                LayoutInflater inflater = (LayoutInflater) this.view.getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
                this.view.addView(inflater.inflate(R.layout.view_seperator, this.view, false));
            }
            this.view.addView(view);
        }
    }

    private class PropertiesView extends CustomView<PropertyView> {

        private Map<String, PropertyView> propertyViewMap = new HashMap<>();
        private ArrayList<PropertyView> children = new ArrayList<>();

        public PropertiesView(ViewGroup view) {
            super(view);
        }

        @Override
        public void addView(PropertyView view) {
            super.addView(view);
            children.add(view);
            if (view instanceof PropertyView) {
                for (String name : view.getNames())
                    propertyViewMap.put(name, view);
            }
        }

        public PropertyView getPropertyView(String propertyName) {
            return propertyViewMap.get(propertyName);
        }

        public Collection<PropertyView> getAllPropertiesView() {
            return children;
        }
    }

    private PropertiesView propertiesView;

    PropertiesChangedListener propertiesChangedListener = new PropertiesChangedListener() {
        @Override
        public synchronized void propertiesChanged(ProxyBusObject pObj, String ifaceName, Map<String, Variant> changed, String[] invalidated) {
            if (!ifaceName.equals(InterfaceFragment.this.intfName))
                return;
            Message msg = m_handler.obtainMessage(HandleMsg.PROPERTIES_CHANGED);
            changedPropertiesQueue.add(changed);
            m_handler.sendMessage(msg);
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setHasOptionsMenu(true);

        Bundle bundle = getArguments();
        this.deviceId = (UUID) bundle.getSerializable(IntentKeys.DEVICE_ID);
        this.objPath = (String) bundle.getSerializable(IntentKeys.OBJECT_PATH);
        this.intfName = (String) bundle.getSerializable(IntentKeys.INTERFACE_NAME);

        if (deviceId == null) {
            Toast.makeText(getActivity(), "UUID is null", Toast.LENGTH_SHORT).show();
            this.finish();
            return;
        }

        this.device = DeviceManager.getInstance().getDevice(this.deviceId);
        if (this.device == null) {
            Toast.makeText(getActivity(), "Can't find device", Toast.LENGTH_SHORT).show();
            this.finish();
            return;
        }

        Status status = Status.FAIL;
        status = DeviceManager.getInstance().getDevice(this.deviceId).registerSignal(this);
        status = DeviceManager.getInstance().getDevice(this.deviceId).registerPropertiesChangedSignal(this.objPath, this.intfName, this.propertiesChangedListener);

        this.receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(MessageType.ON_DEVICE_REMOVED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceRemoved : " + deviceId.toString());
                    if (InterfaceFragment.this.deviceId.equals(deviceId)) {
                        Toast.makeText(getActivity(), "Exit this Page\nCurrent Device is Removed", Toast.LENGTH_SHORT).show();
                        InterfaceFragment.this.finish();
                    }
                }
            }
        };

        this.filter.addAction(MessageType.ON_DEVICE_REMOVED);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        if(isFinishing) {
            return null;
        }

        View inflatedView =  inflater.inflate(R.layout.page_interface, container, false);

        LinearLayout propertyView = (LinearLayout) inflatedView.findViewById(R.id.property_body);
        LinearLayout methodView = (LinearLayout) inflatedView.findViewById(R.id.method_body);
        ((MainActivity)getActivity()).setActionBarTitle(getFriendlyInterfaceName((String)getArguments().getSerializable(IntentKeys.INTERFACE_NAME)));

        this.propertiesView = new PropertiesView(propertyView);
        generatePropertyView(this.propertiesView, new CustomView(methodView));

        if (propertyView.getChildCount() == 1)
            propertyView.setVisibility(View.GONE);
        if (methodView.getChildCount() == 1)
            methodView.setVisibility(View.GONE);

        for (PropertyView view : this.propertiesView.getAllPropertiesView()) {
            view.initView();
            view.getProperty();
        }

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
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Device device = DeviceManager.getInstance().getDevice(this.deviceId);
        device.unregisterSignal(this);
        device.unregisterPropertiesChangedSignal(this.objPath, this.intfName, this.propertiesChangedListener);
    }

    public void notifyEvent(String eventName) {
        notifyEvent(eventName, null);
    }

    public void notifyEvent(String eventName, String eventValue) {
        Message msg = m_handler.obtainMessage(HandleMsg.SIGNAL_EMITTED);
        Bundle bundle = new Bundle();
        bundle.putString(IntentKeys.SIGNAL_NAME, eventName);
        bundle.putString(IntentKeys.SIGNAL_VALUE, eventValue);
        msg.setData(bundle);
        m_handler.sendMessage(msg);
    }

    public void finish() {
        CdmUtil.hideKeyboard(getActivity());
        getActivity().getSupportFragmentManager().popBackStack();
        this.isFinishing = true;
    }

    protected abstract void generatePropertyView(CustomView properties, CustomView methods);

    private String getFriendlyInterfaceName(String interfaceName) {
        String[] splitName = interfaceName.split("\\.");
        return splitName[splitName.length-1];
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);
        inflater.inflate(R.menu.menu, menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch(item.getItemId()) {
            case R.id.action_preset:
                break;
            case R.id.save_preset:
                PresetNameDialog presetNameDialog = new PresetNameDialog();
                presetNameDialog.setTargetFragment(this, 0);
                presetNameDialog.show(getFragmentManager(), "PresetNameDialog");
                break;
            case R.id.apply_preset:
                if(PresetManager.getInstance().getPresetsForInterface(intfName) != null){
                    PresetListDialog presetListDialog = new PresetListDialog();
                    presetListDialog.setTargetFragment(this, 0);
                    presetListDialog.setInterface(intfName);
                    presetListDialog.show(getFragmentManager(), "PresetListDialog");
                } else {
                    Toast.makeText(getActivity(), "No presets available for this interface", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.delete_preset:
                if(PresetManager.getInstance().getPresetsForInterface(intfName) != null){
                    PresetListDialog presetListDialog = new PresetListDialog();
                    presetListDialog.setTargetFragment(this, 0);
                    presetListDialog.setInterface(intfName);
                    presetListDialog.show(getFragmentManager(), "PresetDeleteDialog");
                } else {
                    Toast.makeText(getActivity(), "No presets available for this interface", Toast.LENGTH_SHORT).show();
                }
                break;
            default:
                break;
        }

        return true;
    }

    public void onDialogPositiveClick(DialogFragment dialogFragment) {
        String tag =  dialogFragment.getTag();
        if(tag.equals("PresetNameDialog")) {
            PresetNameDialog dialog = (PresetNameDialog)dialogFragment;
            Preset preset = new Preset(dialog.getPresetName());
            for (PropertyView view : this.propertiesView.getAllPropertiesView()) {
                preset.addValue(view.getName(), view.getCurrentValue());
            }
            PresetManager presetManager = PresetManager.getInstance();
            presetManager.addPreset(intfName, preset);
            Toast.makeText(getActivity(), "Saved preset: " + preset.getName(), Toast.LENGTH_SHORT).show();
        } else if (tag.equals("PresetListDialog")) {
            PresetListDialog dialog = (PresetListDialog)dialogFragment;
            Preset preset = dialog.getSelectedPreset();
            device.applyPreset(objPath, intfName, preset);
            Toast.makeText(getActivity(), "Applying preset: " + preset.getName(), Toast.LENGTH_SHORT).show();
        } else if (tag.equals("PresetDeleteDialog")) {
            PresetListDialog dialog = (PresetListDialog)dialogFragment;
            Preset preset = dialog.getSelectedPreset();
            PresetManager.getInstance().removePreset(intfName, preset);
            Toast.makeText(getActivity(), "Delete preset: " + preset.getName(), Toast.LENGTH_SHORT).show();
        }
    }

    public void onDialogNegativeClick(DialogFragment dialogFragment) {
        Log.d(TAG, "Dialog cancelled: " + dialogFragment.getTag());
    }
}