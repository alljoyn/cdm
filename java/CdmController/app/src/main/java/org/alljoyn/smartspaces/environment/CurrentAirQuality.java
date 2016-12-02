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

@BusInterface(name="org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", descriptionLanguage="en")
@Secure
public interface CurrentAirQuality {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getContaminantType();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="d")
    public double getCurrentValue();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="d")
    public double getMaxValue();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="d")
    public double getMinValue();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="d")
    public double getPrecision();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getUpdateMinTime();

    public enum ContaminantType implements EnumBase<Byte> {
        CH2O((byte)0) {
            @Override
            public String getUnit() {
                return "ug/m3";
            }
        },
        CO2((byte)1) {
            @Override
            public String getUnit() {
                return "ppm";
            }
        },
        CO((byte)2) {
            @Override
            public String getUnit() {
                return "ppm";
            }
        },
        PM2_DOT_5((byte)3){
            @Override
            public String getUnit() {
                return "ug/m3";
            }

            @Override
            public String toString() {
                return "PM2.5";
            }
        },
        PM10((byte)4) {
            @Override
            public String getUnit() {
                return "ug/m3";
            }
        },
        VOC((byte)5) {
            @Override
            public String getUnit() {
                return "ug/m3";
            }
        };

        private byte value;

        ContaminantType(byte value) {
            this.value = value;
        }

        @Override
        public Byte toValue() {
            return this.value;
        }

        public abstract String getUnit();
    }
}