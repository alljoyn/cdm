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
import org.alljoyn.cdmcontroller.view.property.OnMethodResultListener;
import java.util.ArrayList;

public class MethodResultEventView extends MethodView {
    private ArrayList<OnMethodResultListener> onResultListener = null;

    public MethodResultEventView(Context context, Object obj, String methodName, String... paramNames) {
        super(context, obj, methodName, paramNames);
    }

    @Override
    protected void onResult(Object result) {
        super.onResult(result);
        if (onResultListener != null) {
            for (OnMethodResultListener listener : onResultListener) {
                listener.OnMethodResultReceived(result);
            }
        }
    }

    public void addOnResultListener(OnMethodResultListener listener) {
        if (onResultListener == null)
            onResultListener = new ArrayList<OnMethodResultListener>();
        onResultListener.add(listener);
    }

}