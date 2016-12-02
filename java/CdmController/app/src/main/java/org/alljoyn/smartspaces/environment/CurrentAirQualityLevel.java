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

package org.alljoyn.smartspaces.environment;

import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.smartspaces.EnumBase;

@BusInterface(name="org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel", descriptionLanguage="en")
@Secure
public interface CurrentAirQualityLevel {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getContaminantType();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getCurrentLevel();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getMaxLevel();

    public enum ContaminantType implements EnumBase<Byte> {
        CH2O((byte)0),
        CO2((byte)1),
        CO((byte)2),
        PM2_DOT_5((byte)3){
            @Override
            public String toString() {
                return "PM2.5";
            }
        },
        PM10((byte)4),
        VOC((byte)5),
        Smoke((byte)253),
        Odor((byte)254),
        AirPollution((byte)255);

        private byte value;

        ContaminantType(byte value) {
            this.value = value;
        }

        @Override
        public Byte toValue() {
            return this.value;
        }
    }
}