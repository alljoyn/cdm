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

package org.alljoyn.cdmcontroller.view;

import android.content.Context;
import android.os.AsyncTask;
import android.widget.LinearLayout;
import android.widget.Toast;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.logic.Device;

public abstract class PropertyView extends LinearLayout {
    protected Device device = null;

    protected String objPath = null;
    protected String interfaceName = null;
    protected String name = null;
    protected String unit = null;

    protected Object currentValue = null;
    protected Class<?> propertyType = null;
    protected Class<?>[] propertyParameterTypes = null;

    public PropertyView(Context context, Device obj, String objPath, String interfaceName, String propertyName, String unit) {
        super(context);
        this.device = obj;
        this.objPath = objPath;
        this.interfaceName = interfaceName;
        this.name = propertyName;
        this.unit = unit;
        this.propertyType = this.device.getPropertyType(this.objPath, this.interfaceName, this.name);
        this.propertyParameterTypes = this.device.getPropertyParameterTypes(this.objPath, this.interfaceName, this.name);
    }

    public String[] getNames() { return new String[]{this.name}; }

    public String getName() { return this.name; }

    public Object getCurrentValue() { return this.currentValue; }

    public void onPropertiesChangedSignal(String name, Variant value) {
        if (!name.equals(this.name))
            return;

        try {
            this.currentValue = value.getObject(propertyType);
            this.setValueView(this.currentValue);
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }
        setValueView(this.currentValue);
    }

    public abstract void initView();

    protected abstract void setValueView(Object value);

    public void setProperty(Object value) {
        if (value.equals(this.currentValue))
            return;

        AsyncTask<Object, Void, Boolean> excuteSet = new AsyncTask<Object, Void, Boolean>() {
            @Override
            protected Boolean doInBackground(Object... params) {
                Device device = PropertyView.this.device;
                device.setProperty(PropertyView.this.objPath, PropertyView.this.interfaceName, PropertyView.this.name, params[0]);
                PropertyView.this.currentValue = params[0];
                return true;
            }

            @Override
            protected void onPostExecute(Boolean result) {
                if (!result) {
                    Toast.makeText(PropertyView.this.getContext(), "Set " + PropertyView.this.name + " Property is failed", Toast.LENGTH_SHORT).show();
                    PropertyView.this.setValueView(PropertyView.this.currentValue);
                }
            }

        };
        excuteSet.execute(value);
    }

    public void getProperty() {
        AsyncTask<Void, Void, Object> excuteGet = new AsyncTask<Void, Void, Object>() {
            @Override
            protected Object doInBackground(Void... params) {
                Device device = PropertyView.this.device;
                Object returnObj = device.getProperty(PropertyView.this.objPath, PropertyView.this.interfaceName, PropertyView.this.name);
                PropertyView.this.currentValue = returnObj;
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                if (o != null) {
                    PropertyView.this.setValueView(o);
                } else {
                    Object currentValue = PropertyView.this.currentValue;
                    if (currentValue == null) {
                        currentValue = "Undefined";
                    }
                    PropertyView.this.setValueView(currentValue);
                    Toast.makeText(PropertyView.this.getContext(), "Get " + PropertyView.this.name + " Property is failed", Toast.LENGTH_SHORT).show();
                }

            }
        };
        excuteGet.execute();
    }
}
