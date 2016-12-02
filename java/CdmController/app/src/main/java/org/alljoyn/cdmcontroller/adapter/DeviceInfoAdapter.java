/*
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 */

package org.alljoyn.cdmcontroller.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.logic.Device;

import java.util.Collection;

public class DeviceInfoAdapter extends ArrayAdapter<Device>
{
    private View m_rowView = null;
    private LayoutInflater m_layoutInflater = null;

    public DeviceInfoAdapter(Context context) {
        super(context, 0);
        m_layoutInflater = LayoutInflater.from(context);
    }

    public void setLayoutInflator(LayoutInflater layoutInflater){
        m_layoutInflater = layoutInflater;
    }

    @Override
    public synchronized void add(Device device) {
        if (this.getPosition(device) == -1)
            super.add(device);
    }

    @Override
    public synchronized void addAll(Collection<? extends Device> devices) {
        for (Device device : devices) {
            this.add(device);
        }
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent)
    {
        if (convertView == null) {
            m_rowView = m_layoutInflater.inflate(R.layout.list_item_info, parent, false);
        } else {
            m_rowView = convertView;
        }

        TextView name = (TextView) m_rowView.findViewById(R.id.name);

        Device device = this.getItem(position);
        
        name.setText(device.getName());

        return m_rowView;
    }
}