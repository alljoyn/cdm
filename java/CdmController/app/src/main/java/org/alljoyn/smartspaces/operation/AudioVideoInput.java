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

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.AudioVideoInput", descriptionLanguage="en")
@Secure
public interface AudioVideoInput {
    public class InputSource {
        @Position(0)
        @Signature("q")
        public short id;

        @Position(1)
        @Signature("q")
        public short sourceType;

        @Position(2)
        @Signature("y")
        public byte detectedState;

        @Position(3)
        @Signature("q")
        public short portNumber;

        @Position(4)
        @Signature("s")
        public String friendlyName;

        @Override
        public String toString() {
            return "[" + " id=" + String.valueOf(id) + " sourceType=" + String.valueOf(sourceType) + " detectedState=" + String.valueOf(detectedState) + " portNumber=" + String.valueOf(portNumber) + " friendlyName=" + "\"" + friendlyName + "\"" + " ]";
        }
    }

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getInputSourceId();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public void setInputSourceId(short inputSourceId);

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="a(qqyqs)")
    public InputSource[] getSupportedInputSources();

}