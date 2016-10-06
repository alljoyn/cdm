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
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import org.alljoyn.bus.BusObject;
import org.alljoyn.bus.PropertiesChangedListener;
import org.alljoyn.bus.ProxyBusObject;
import org.alljoyn.bus.Status;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.adapter.InterfaceListAdapter;
import org.alljoyn.cdmcontroller.logic.DeviceManager;
import org.alljoyn.cdmcontroller.logic.IntentKeys;
import org.alljoyn.cdmcontroller.logic.MessageType;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentLinkedQueue;

public abstract class InterfaceActivity extends Activity implements BusObject {
    private final static String TAG = "CDM_IntfActivity";

    protected class HandleMsg {
        public static final int PROPERTIES_CHANGED = 0;
        public static final int SIGNAL_EMITTED = 1;
    }

    private BroadcastReceiver receiver = null;
    private IntentFilter filter = new IntentFilter();

    private UUID deviceId = null;
    private String objPath = null;
    private String intfName = null;

    protected Object intf;

    protected ConcurrentLinkedQueue<Map<String, Variant>> changedPropertiesQueue = new ConcurrentLinkedQueue<>();


    private InterfaceListAdapter aboutObjectDescriptionAdapter = null;

    protected Handler m_handler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case HandleMsg.PROPERTIES_CHANGED:
                    while (!changedPropertiesQueue.isEmpty()) {
                        Map<String, Variant> changedProperties = changedPropertiesQueue.poll();
                        for (String name : changedProperties.keySet()) {
                            PropertyView view = InterfaceActivity.this.propertisView.getPropertyView(name);
                            if (view != null) {
                                try {
                                    view.onPropertiesChangedSignal(name, changedProperties.get(name));
                                    Toast.makeText(InterfaceActivity.this, String.format("%s is changed", name), Toast.LENGTH_SHORT).show();
                                } catch (Exception e) {
                                    e.printStackTrace();
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
                    Toast.makeText(InterfaceActivity.this, toastMsg, Toast.LENGTH_SHORT).show();
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

    private PropertiesView propertisView;

    PropertiesChangedListener propertiesChangedListener = new PropertiesChangedListener() {
        @Override
        public synchronized void propertiesChanged(ProxyBusObject pObj, String ifaceName, Map<String, Variant> changed, String[] invalidated) {
            if (!ifaceName.equals(InterfaceActivity.this.intfName))
                return;
            Message msg = m_handler.obtainMessage(HandleMsg.PROPERTIES_CHANGED);
            changedPropertiesQueue.add(changed);
            m_handler.sendMessage(msg);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.page_interface);

        this.deviceId = (UUID) getIntent().getSerializableExtra(IntentKeys.DEVICE_ID);
        this.objPath = (String) getIntent().getSerializableExtra(IntentKeys.OBJECT_PATH);
        this.intfName = (String) getIntent().getSerializableExtra(IntentKeys.INTERFACE_NAME);

        if (deviceId == null) {
            Toast.makeText(this, "UUID is null", Toast.LENGTH_SHORT).show();
            this.finish();
            return;
        }

        intf = DeviceManager.getInstance().getDevice(this.deviceId).getInterface(this.objPath, this.intfName);

        if (intf == null) {
            Toast.makeText(this, this.intfName + " interface not declared in pkg", Toast.LENGTH_SHORT).show();
            this.finish();
        }

        Status status = Status.FAIL;
        status = DeviceManager.getInstance().getDevice(this.deviceId).registerSignal(this);
        status = DeviceManager.getInstance().getDevice(this.deviceId).registerPropertiesChangedSignal(this.propertiesChangedListener);

        LinearLayout propertyView = (LinearLayout) findViewById(R.id.property_body);
        LinearLayout methodView = (LinearLayout) findViewById(R.id.method_body);
        TextView title = (TextView) findViewById(R.id.navtitleback_title_text);
        title.setText(intfName.replaceAll(".*[.]", ""));
        findViewById(R.id.navtitleback_title_arrorw).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                InterfaceActivity.this.finish();
            }
        });

        this.receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(MessageType.ON_DEVICE_REMOVED)) {
                    UUID deviceId = (UUID) intent.getSerializableExtra(IntentKeys.DEVICE_ID);
                    Log.d(TAG, "OnDeviceRemoved : " + deviceId.toString());
                    if (InterfaceActivity.this.deviceId.equals(deviceId)) {
                        Toast.makeText(InterfaceActivity.this, "Exit this Page\nCurrent Device is Removed", Toast.LENGTH_SHORT).show();
                        InterfaceActivity.this.finish();
                    }
                }
            }
        };

        this.propertisView = new PropertiesView(propertyView);
        generatePropertyView(this.propertisView, new CustomView(methodView));

        if (propertyView.getChildCount() == 1)
            propertyView.setVisibility(View.GONE);
        if (methodView.getChildCount() == 1)
            methodView.setVisibility(View.GONE);

        for (PropertyView view : this.propertisView.getAllPropertiesView()) {
            view.initView();
            view.getProperty();
        }

        this.filter.addAction(MessageType.ON_DEVICE_ADDED);
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
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        DeviceManager.getInstance().getDevice(this.deviceId).unregisterSignal(this);
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

    @Override
    public void finish() {
        CdmUtil.hideKeyboard(this);
        super.finish();
    }

    protected abstract void generatePropertyView(CustomView properties, CustomView methods);
}