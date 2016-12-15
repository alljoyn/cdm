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

package org.alljoyn.cdmcontroller.adapter;

import android.content.Context;
import android.graphics.Color;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.logic.Device;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class InterfaceListAdapter extends BaseAdapter {
    public class Item {
        public int level = 0;
        public ArrayList<Integer> icon = new ArrayList<>();
        public String title = "";
        public String detailInfo = "";
        public Item parent = null;
        public List<Item> children = new LinkedList<>();
        public boolean isFolded = false;

        public void setObjectPathInfo(String objectPath, List<Device.DeviceType> deviceTypes) {
            this.parent = null;
            this.level = 0;
            this.title = objectPath;
            this.detailInfo = objectPath;
            for (Device.DeviceType type : deviceTypes) {
                if (type.getIconID() != 0)
                    icon.add(type.getIconID());
            }
        }

        protected void addChild(Item child) {
            this.children.add(child);
        }

        public void setInterfaceInfo(Item parent, String intfName) {
            this.parent = parent;
            this.level = 1;
            this.title = intfName.substring(intfName.lastIndexOf('.') + 1);
            this.detailInfo = intfName;
            this.icon.clear();
            parent.addChild(this);
        }
    }

    private LinkedList<Item> itemList = new LinkedList<Item>();

    private Context context;
    private View rowView = null;
    private LayoutInflater layoutInflater = null;

    public InterfaceListAdapter(Context context) {
        this.context = context;
        this.layoutInflater = LayoutInflater.from(context);
    }

    public void foldItem(int position) {
        Item item = getItem(position);
        if (item.level > 1)
            return;
        if (item.isFolded) {
            this.itemList.addAll(position+1, item.children);
        } else {
            this.itemList.removeAll(item.children);
        }
        item.isFolded = !item.isFolded;
        this.notifyDataSetChanged();
    }

    public boolean add(String objectPath, String[] interfaces, List<Device.DeviceType> deviceTypes) {
        Item objectPathItem = new Item();
        objectPathItem.setObjectPathInfo(objectPath, deviceTypes);
        if (this.itemList.add(objectPathItem)) {
            for (String intf : interfaces) {
                Item intfItem = new Item();
                intfItem.setInterfaceInfo(objectPathItem, intf);
                this.itemList.add(intfItem);
            }
            return true;
        }
        return false;
    }


    @Override
    public int getCount() {
        return itemList.size();
    }

    @Override
    public Item getItem(int position) {
        return itemList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return this.itemList.get(position).hashCode();
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        this.rowView = layoutInflater.inflate(R.layout.level_list_item_info, parent, false);

        TextView titleView = (TextView) this.rowView.findViewById(R.id.title);
        TextView descView = (TextView) this.rowView.findViewById(R.id.description);
        ImageView icon = (ImageView) this.rowView.findViewById(R.id.icon);

        Item item = this.getItem(position);
        if (item.level == 0) {
            this.rowView.setBackgroundColor(this.rowView.getResources().getColor(R.color.item_color2));
            titleView.setText(item.title);
            if (item.icon.size() > 0) {
                for (int iconId : item.icon) {
                    ImageView newIcon = (ImageView)layoutInflater.inflate(R.layout.view_description_icon, parent, false);
                    newIcon.setImageResource(iconId);
                    newIcon.setColorFilter(Color.DKGRAY);
                    ((ViewGroup)this.rowView).addView(newIcon, 0);
                }
                icon.setVisibility(View.GONE);
            }
            if (item.isFolded && item.children.size() > 0) {
                descView.setText("...");
            } else {
                descView.setVisibility(View.GONE);
            }
        } else if (item.level == 1) {
            this.rowView.setBackgroundColor(this.rowView.getResources().getColor(R.color.item_color));
            descView.setText(item.title);
            titleView.setVisibility(View.GONE);
        }
        return rowView;
    }
}