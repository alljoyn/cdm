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
import org.alljoyn.smartspaces.EnumBase;

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", descriptionLanguage="en")
@Secure
public interface MoistureOutputLevel {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getMoistureOutputLevel();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public void setMoistureOutputLevel(byte value);

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getMaxMoistureOutputLevel();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getAutoMode();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public void setAutoMode(byte autoMode);

    public enum Mode implements EnumBase<Byte> {
        Off((byte)0x00),
        On((byte)0x01),
        Not_Supported((byte)0xFF) {
            @Override
            public String toString() {
                return super.toString().replace('_', ' ');
            }
        };

        private Byte value;
        private Mode(byte value) {
            this.value = value;
        }

        public Byte toValue() {
            return this.value;
        }
    }
}