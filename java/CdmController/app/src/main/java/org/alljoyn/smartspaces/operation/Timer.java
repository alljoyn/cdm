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
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.Signature;
import org.alljoyn.bus.annotation.Position;

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.Timer", descriptionLanguage="en")
@Secure
public interface Timer {
    @BusProperty(signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="i")
    public int getReferenceTimer();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="i")
    public int getTargetTimeToStart();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="i")
    public int getTargetTimeToStop();

    @BusProperty(signature="i")
    public int getEstimatedTimeToEnd();

    @BusProperty(signature="i")
    public int getRunningTime();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="i")
    public int getTargetDuration();

    @BusMethod(name="SetTargetTimeToStart", signature="i")
    public void setTargetTimeToStart(int targetTimeToStart);

    @BusMethod(name="SetTargetTimeToStop", signature="i")
    public void setTargetTimeToStop(int targetTimeToStop);

}