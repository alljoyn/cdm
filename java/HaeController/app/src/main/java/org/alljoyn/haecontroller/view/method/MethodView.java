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

package org.alljoyn.haecontroller.view.method;

import android.content.Context;
import android.os.AsyncTask;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.alljoyn.haecontroller.R;
import org.alljoyn.haecontroller.view.custom.ParamDialog;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class MethodView extends LinearLayout {
    private static final String TAG = "HAE_Method";

    private static final int PARAM_RESULT = 1;

    private Method method = null;

    protected Object busObject = null;

    private TextView nameView;
    private ViewGroup resultLayout;
    private TextView paramView;
    private TextView resultView;
    private Button submitBtn;
    private Object[] params;
    private String[] paramNames = null;
    private int position = -1;

    public MethodView(Context context, Object obj, String methodName, String... paramNames) {
        super(context);
        this.busObject = obj;
        this.method = null;
        this.paramNames = paramNames;
        methodName = methodName.toUpperCase();
        for (Method method : obj.getClass().getDeclaredMethods()) {
            if (method.getName().toUpperCase().equals(methodName)) {
                this.method = method;
                break;
            }
        }
        initView();
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_method, this, false);

        this.addView(view);
        this.resultLayout = (ViewGroup) view.findViewById(R.id.layout_result);
        this.resultLayout.setVisibility(View.GONE);
        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.paramView = (TextView) view.findViewById(R.id.params);
        this.resultView = (TextView) view.findViewById(R.id.result);

        this.submitBtn = (Button) view.findViewById(R.id.submit);

        this.submitBtn.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                invokeMethod();
            }
        });

        this.nameView.setText(this.method.getName());
    }

    protected void asyncMethodCall(Object[] params) {
        AsyncTask<Object, Void, Object> excuteMethod = new AsyncTask<Object, Void, Object>() {
            @Override
            protected Object doInBackground(Object... params) {
                Object result = null;
                try {
                    result = MethodView.this.method.invoke(MethodView.this.busObject, params);
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (InvocationTargetException e) {
                    e.printStackTrace();
                }
                return result;
            }

            @Override
            protected void onPostExecute(Object result) {
                if (result != null) {
                    String strResult = "";
                    if (result instanceof Object[]) {
                        for (Object item : (Object[]) result) {
                            strResult += item.toString() + "\n";
                        }
                    } else
                        strResult = result.toString();
                    MethodView.this.resultView.setText(strResult);
                }
                else {
                    MethodView.this.resultView.setText("No result  ");
                }
            }
        }.execute(params);
    }

    protected void invokeMethod() {
        if (paramNames != null) {
            ParamDialog mDialog = new ParamDialog(getContext(), this.method.getName(), this.method.getParameterTypes(), this.paramNames, new ParamDialog.OnOkClickListener() {
                @Override
                public void onOkClick(Object[] params) {
                    MethodView.this.resultLayout.setVisibility(View.VISIBLE);
                    String strParam = "[ ";
                    for (Object param : params) {
                        strParam += param.toString() + " ";
                    }
                    strParam += "]";
                    MethodView.this.paramView.setText(strParam);
                    asyncMethodCall(params);
                }
            });
            mDialog.show();
        } else {
            asyncMethodCall(null);
        }
    }
}
