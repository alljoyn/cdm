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

package org.alljoyn.cdmcontroller.view.property;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import org.alljoyn.bus.BusException;
import org.alljoyn.bus.Variant;
import org.alljoyn.cdmcontroller.R;
import org.alljoyn.cdmcontroller.util.CdmUtil;
import org.alljoyn.cdmcontroller.view.PropertyView;
import org.alljoyn.smartspaces.EnumBase;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ReadOnlySupportedEnumPropertyView<T extends EnumBase<T>> extends SupportedEnumPropertyView {
    private static final String TAG = "CDM_ReadProperty";
    private SpinnerInteractionListener listener = null;

    public class SpinnerInteractionListener implements AdapterView.OnItemSelectedListener, View.OnTouchListener {

        boolean userSelect = false;

        @Override
        public boolean onTouch(View v, MotionEvent event) {
            userSelect = true;
            return false;
        }

        @Override
        public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
            if (userSelect) {
                //ReadOnlySupportedEnumPropertyView.this.setProperty(SupportedValuesPropertyView.this.valuesAdapter.getItem(pos));
                ReadOnlySupportedEnumPropertyView.this.setPosition();
                ReadOnlySupportedEnumPropertyView.this.warning(name +" is read only property.");
                userSelect = false;
            }
        }

        @Override
        public void onNothingSelected(AdapterView<?> parent) {

        }
    }

    public ReadOnlySupportedEnumPropertyView(Context context, Object obj, String propertyName, String supportedEnumPropertyName, Class<T> clazz) {
        super(context, obj, propertyName, supportedEnumPropertyName, clazz);
    }

    int positionC = 0;

    @Override
    public void setValueView(Object value) {
        T item = (T)CdmUtil.findEnum(value, clazz);

        if (item != null && valuesAdapter.getCount() > 0) {
            this.valuesView.setSelection(valuesAdapter.getPosition(item));
            positionC = valuesAdapter.getPosition(item);
        }
        if (this.listener == null) {
            this.listener = new SpinnerInteractionListener();
            this.valuesView.setOnItemSelectedListener(this.listener);
            this.valuesView.setOnTouchListener(this.listener);
        }
    }

    private void setPosition(){
        this.valuesView.setSelection(positionC);
    }

    private void warning(String msg) {
        Toast.makeText(this.getContext(), msg, Toast.LENGTH_SHORT).show();
    }
}