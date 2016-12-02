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

package org.alljoyn.smartspaces.userinterfacesettings;

import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.smartspaces.EnumBase;

@BusInterface(name="org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay", descriptionLanguage="en")
@Secure
public interface TemperatureDisplay {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getDisplayTemperatureUnit();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public void setDisplayTemperatureUnit(byte displayTemperatureUnit);

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="ay")
    public byte[] getSupportedDisplayTemperatureUnits();

    public enum DisplayTemperatureUnit implements EnumBase<Byte> {
        C((byte)0x00),
        F((byte)0x01),
        K((byte)0x02);

        private Byte value;
        private DisplayTemperatureUnit(byte value) {
            this.value = value;
        }

        public Byte toValue() {
            return this.value;
        }
    }
}