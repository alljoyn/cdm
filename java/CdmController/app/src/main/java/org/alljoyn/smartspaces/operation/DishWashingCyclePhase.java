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

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", descriptionLanguage="en")
@Secure
public interface DishWashingCyclePhase {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getCyclePhase();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="ay")
    public byte[] getSupportedCyclePhases();

    @BusMethod(name="GetVendorPhasesDescription", signature="s", replySignature = "a(yss)")
    public CyclePhaseDescriptor[] getVendorPhasesDescription(String languageTag);

    public enum CyclePhase implements EnumBase<Byte> {
        Unavailable((byte)0x00),
        Pre_Wash((byte)0x01),
        Wash((byte)0x02),
        Rinse((byte)0x03),
        Dry((byte)0x04);

        private byte value;
        private CyclePhase(byte value) {
            this.value = value;
        }
        @Override
        public Byte toValue() {
            return this.value;
        }
    }
}