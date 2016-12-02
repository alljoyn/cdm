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
import android.view.View;

import org.alljoyn.cdmcontroller.view.custom.ParamSupportedEnumDialog;
import org.alljoyn.smartspaces.EnumBase;

public class MethodSupportedParamEnumView<T extends EnumBase<T>> extends MethodView {

    private String[] supportedParamNames;
    private Class<T>[] clazzes;

    public MethodSupportedParamEnumView(Context context, Object obj, String methodName, String[] supportedParamNames, Class<T>[] clazzes,
                                        String... paramNames) {
        super(context, obj, methodName, paramNames);

        this.supportedParamNames = supportedParamNames;
        this.clazzes = clazzes;
    }

    protected void invokeMethod() {
        if (paramNames != null) {
            ParamSupportedEnumDialog mDialog = new ParamSupportedEnumDialog(getContext(),
                    busObject, method.getName(), method.getParameterTypes(),
                    paramNames, supportedParamNames, clazzes, new ParamSupportedEnumDialog.OnOkClickListener() {
                @Override
                public void onOkClick(Object[] params) {
                    MethodSupportedParamEnumView.this.resultLayout.setVisibility(View.VISIBLE);
                    String strParam = "[ ";
                    for (Object param : params) {
                        strParam += param.toString() + " ";
                    }
                    strParam += "]";
                    MethodSupportedParamEnumView.this.paramView.setText(strParam);
                    asyncMethodCall(params);
                }
            });
            mDialog.show();
        } else {
            asyncMethodCall(null);
        }
    }
}