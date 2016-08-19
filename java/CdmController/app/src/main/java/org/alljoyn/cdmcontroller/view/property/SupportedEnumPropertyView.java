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

package org.alljoyn.haecontroller.view.property;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.haecontroller.view.PropertyView;
import org.alljoyn.smartspaces.EnumBase;
import org.alljoyn.haecontroller.R;
import org.alljoyn.haecontroller.util.HaeUtil;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class SupportedEnumPropertyView<T extends EnumBase<T>> extends PropertyView {
    private static final String TAG = "HAE_ReadWriteProperty";

    private Method supportedGetter = null;
    private String supportedName;

    private TextView nameView;
    protected Spinner valuesView;

    protected Class<T> clazz;

    protected ArrayAdapter<T> valuesAdapter;
    protected AdapterView.OnItemSelectedListener listener = null;

    public SupportedEnumPropertyView(Context context, Object obj, String propertyName, String supportedEnumPropertyName, Class<T> clazz) {
        super(context, obj, propertyName, null);
        this.supportedName = supportedEnumPropertyName;
        this.clazz = clazz;
        try {
            this.supportedGetter = obj.getClass().getMethod("get" + supportedEnumPropertyName);
        } catch (NoSuchMethodException e) {
            this.supportedGetter = null;
        }
    }

    public String[] getNames() {
        return new String[]{this.name, this.supportedName};
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_supported_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valuesView = (Spinner) view.findViewById(R.id.property_values);
        view.findViewById(R.id.property_unit).setVisibility(View.GONE);
        Log.d(TAG, "1: valueView is " + this.valuesView.toString());


        valuesAdapter = new ArrayAdapter<T>(this.getContext(), android.R.layout.simple_spinner_item);
        this.valuesView.setAdapter(valuesAdapter);

        this.nameView.setText(this.name);
    }

    public void onPropertiesChangedSignal(String name, Variant value) {
        Object obj = null;
        try {
            obj = value.getObject(this.valueGetter.getReturnType());
        } catch (BusException e) {
            e.printStackTrace();
            return;
        }

        if (name.equals(this.supportedName)) {
            setSupportedEnumView(obj);
        } else
            super.onPropertiesChangedSignal(name, value);
    }

    private void setSupportedEnumView(Object enumList) {
        if (enumList != null) {
            SupportedEnumPropertyView.this.valuesAdapter.clear();
            for (Object obj : HaeUtil.toObjectArray(enumList)) {
                T item = (T) HaeUtil.findEnum(obj, SupportedEnumPropertyView.this.clazz);
                SupportedEnumPropertyView.this.valuesAdapter.add(item);
            }
        }
        if (this.currentValue != null) {
            setValueView(this.currentValue);
        }
    }

    @Override
    public void setValueView(Object value) {
        T item = (T)HaeUtil.findEnum(value, this.clazz);
        if (item != null && this.valuesAdapter.getCount() > 0) {
            this.valuesView.setSelection(this.valuesAdapter.getPosition(item));
        }

        if (this.listener == null) {
            this.listener = new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                    SupportedEnumPropertyView.this.setProperty(SupportedEnumPropertyView.this.valuesAdapter.getItem(position).toValue());
                }

                @Override
                public void onNothingSelected(AdapterView<?> parent) {

                }
            };
            this.valuesView.setOnItemSelectedListener(this.listener);
        }
    }

    @Override
    public void getProperty() {
        super.getProperty();

        AsyncTask<Void, Void, Object> execute = new AsyncTask<Void, Void, Object>() {

            @Override
            protected Object doInBackground(Void... voids) {
                Object returnObj = null;
                try {
                    if (SupportedEnumPropertyView.this.supportedGetter != null) {
                        Class<?>[] paramTypes = SupportedEnumPropertyView.this.supportedGetter.getParameterTypes();
                        Object[] params = new Object[paramTypes.length];
                        int idx = 0;
                        returnObj = supportedGetter.invoke(SupportedEnumPropertyView.this.busObject);
                    }
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return returnObj;
            }

            @Override
            protected void onPostExecute(Object o) {
                setSupportedEnumView(o);
            }
        }.execute();
    }
}
