/*
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
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