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

package org.alljoyn.cdmcontroller.view.method;

import android.content.Context;
import android.os.AsyncTask;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.alljoyn.input.Hid;
import org.alljoyn.cdmcontroller.R;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class InjectEventsMethodView extends LinearLayout {
    private Method method = null;
    protected Object busObject = null;

    private TextView nameView;
    private ViewGroup paramsViewGroup;
    private TextView typeView;
    private TextView codeView;
    private TextView valueView;
    private TextView inputView;
    private TextView outputView;
    private Button addInputBtn;
    private Button invokeMethodBtn;
    private List<Hid.InputEvent> inputList;

    private String name;

    public InjectEventsMethodView(Context context, Object obj, String methodName) {
        super(context);
        this.busObject = obj;
        this.method = null;
        methodName = methodName.toUpperCase();
        for (Method method : obj.getClass().getDeclaredMethods()) {
            if (method.getName().toUpperCase().equals(methodName)) {
                this.method = method;
                break;
            }
        }
        this.name = methodName;
        initView();
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_method_inject_events, this, false);
        this.addView(view);
        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.paramsViewGroup = (ViewGroup) findViewById(R.id.property_body);
        this.typeView = (TextView)view.findViewById(R.id.type_value);
        this.codeView = (TextView)view.findViewById(R.id.code_value);
        this.valueView = (TextView)view.findViewById(R.id.value_value);
        this.inputView = (TextView) view.findViewById(R.id.params);
        this.outputView = (TextView) view.findViewById(R.id.result);
        this.addInputBtn = (Button) view.findViewById(R.id.add);
        this.invokeMethodBtn = (Button) view.findViewById(R.id.invoke);

        inputList = new ArrayList<>();
        this.addInputBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Hid.InputEvent event = new Hid.InputEvent();
                event.type = Short.parseShort(InjectEventsMethodView.this.typeView.getText().toString());
                event.code = Short.parseShort(InjectEventsMethodView.this.codeView.getText().toString());
                event.value = Integer.parseInt(InjectEventsMethodView.this.valueView.getText().toString());
                inputList.add(event);
                InjectEventsMethodView.this.inputView.append(event.toString() + "\n");
            }
        });

        this.invokeMethodBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                Hid.InputEvent[] events = inputList.toArray(new Hid.InputEvent[inputList.size()]);
                asyncMethodCall(events);
            }
        });

        this.nameView.setText(this.name);
    }

    protected void asyncMethodCall(Object[] params) {
        AsyncTask<Object, Void, Object> excuteMethod = new AsyncTask<Object, Void, Object>() {
            @Override
            protected Object doInBackground(Object... params) {
                Object result = null;
                try {
                    result = InjectEventsMethodView.this.method.invoke(InjectEventsMethodView.this.busObject, new Object[]{params});
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return result;
            }

            @Override
            protected void onPostExecute(Object result) {
                InjectEventsMethodView.this.outputView.setText("Succeeded\n");
                for (Hid.InputEvent e : inputList) {
                    InjectEventsMethodView.this.outputView.append(e.toString() + "\n");
                }
                InjectEventsMethodView.this.inputView.setText("");
                inputList.clear();;

            }
        }.execute(params);
    }
}