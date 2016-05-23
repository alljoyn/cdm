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
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import org.alljoyn.haecontroller.view.PropertyView;
import org.alljoyn.smartspaces.EnumBase;
import org.alljoyn.haecontroller.R;
import org.alljoyn.haecontroller.util.HaeUtil;

public class ReadWriteEnumPropertyView<T extends EnumBase<?>> extends PropertyView {
    private static final String TAG = "HAE_ReadWriteProperty";

    private TextView nameView;
    private Spinner valuesView;

    private Class<T> clazz;

    private ArrayAdapter<T> valuesAdapter;

    private AdapterView.OnItemSelectedListener listener = null;

    public ReadWriteEnumPropertyView(Context context, Object obj, String propertyName, Class<T> clazz) {
        super(context, obj, propertyName, null);
        this.clazz = clazz;
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

    @Override
    public void setValueView(Object value) {
        T item = (T)HaeUtil.findEnum(value, this.clazz);
        if (item != null) {
            this.valuesView.setSelection(this.valuesAdapter.getPosition(item));
        }

        if (this.listener == null) {
            this.listener = new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                    ReadWriteEnumPropertyView.this.setProperty(ReadWriteEnumPropertyView.this.valuesAdapter.getItem(position).toValue());
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
        for (T item : clazz.getEnumConstants()) {
            ReadWriteEnumPropertyView.this.valuesAdapter.add(item);
        }
        ReadWriteEnumPropertyView.super.getProperty();
    }
}
