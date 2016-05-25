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

package org.alljoyn.haecontroller.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import org.alljoyn.haecontroller.R;
import org.alljoyn.haecontroller.logic.Device;

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
