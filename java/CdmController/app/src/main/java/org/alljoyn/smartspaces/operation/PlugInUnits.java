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

package org.alljoyn.smartspaces.operation;


import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Position;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.bus.annotation.Signature;

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.PlugInUnits", descriptionLanguage="en")
@Secure
public interface PlugInUnits {
    public class PlugInInfo {
        @Position(0)
        @Signature("o")
        public String objectPath;

        @Position(1)
        @Signature("u")
        public int deviceId;

        @Position(2)
        @Signature("b")
        public boolean pluggedIn;

        @Override
        public String toString() {
            return "[Unit]\n objectPath= " + String.valueOf(objectPath) + "\n deviceId= " + deviceId + "\n pluggedIn= " + pluggedIn +"\n";
        }
    }

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="a(oub)")
    public PlugInInfo[] getPlugInUnits();

}