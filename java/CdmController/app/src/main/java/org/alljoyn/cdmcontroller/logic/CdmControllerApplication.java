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

package org.alljoyn.cdmcontroller.logic;

import android.app.Application;

public class CdmControllerApplication extends Application {
   static {
        System.loadLibrary("alljoyn_java");
    }

    private final static String TAG = "CDM_ControllerApp";

    public CdmControllerApplication() {
        super();
    }

    @Override
    public void onCreate() {
        super.onCreate();
        new DeviceManagerImpl(this).init();
    }

    @Override
    public void onTerminate() {
        super.onTerminate();
    }
}