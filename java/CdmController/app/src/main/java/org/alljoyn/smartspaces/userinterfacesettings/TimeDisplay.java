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

@BusInterface(name="org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay", descriptionLanguage="en")
@Secure
public interface TimeDisplay {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getDisplayTimeFormat();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public void setDisplayTimeFormat(byte displayTimeFormat);

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="ay")
    public byte[] getSupportedDisplayTimeFormats();

    public enum DisplayTimeFormat implements EnumBase<Byte> {
        t12_hour((byte)0x00) {
            @Override
            public String toString() {
                String s = super.toString().replace('_', '-');
                return s.substring(1);
            }
        },
        t24_hour((byte)0x01){
            @Override
            public String toString() {
                String s = super.toString().replace('_', '-');
                return s.substring(1);
            }
        };

        private Byte value;
        private DisplayTimeFormat(byte value) {
            this.value = value;
        }

        public Byte toValue() {
            return this.value;
        }
    }
}