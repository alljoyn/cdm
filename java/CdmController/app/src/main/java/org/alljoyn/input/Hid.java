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

package org.alljoyn.input;

import org.alljoyn.bus.annotation.BusAnnotation;
import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.Signature;
import org.alljoyn.bus.annotation.Position;

@BusInterface(name="org.alljoyn.Input.Hid", descriptionLanguage="en")
@Secure
public interface Hid {
    public class SupportedEvent {
        @Position(0)
        @Signature("q")
        public short type;

        @Position(1)
        @Signature("q")
        public short code;

        @Position(2)
        @Signature("i")
        public int min;

        @Position(3)
        @Signature("i")
        public int max;

        @Override
        public String toString() {
            return "[" + " type=" + "\"" + type + "\""
                    + " code=" + "\"" + code + "\""
                    + " min=" + "\"" + min + "\""
                    + " max=" + "\"" + max + "\"" + " ]";
        }
    }

    public class InputEvent {
        @Position(0)
        @Signature("q")
        public short type;

        @Position(1)
        @Signature("q")
        public short code;

        @Position(2)
        @Signature("i")
        public int value;

        public String toString() {
            return "[" + " type=" + "\"" + type + "\""
                    + " code=" + "\"" + code + "\""
                    + " value=" + "\"" + value + "\"" + " ]";
        }
    }

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="a(qqii)")
    public SupportedEvent[] getSupportedEvents();

    @BusMethod(name="InjectEvents", signature="ar", annotation=BusMethod.ANNOTATE_NO_REPLY)
    //@BusMethod(name="InjectEvents", annotation=BusMethod.ANNOTATE_NO_REPLY)
    public void injectEvents(InputEvent[] inputEvents) throws BusException;

}