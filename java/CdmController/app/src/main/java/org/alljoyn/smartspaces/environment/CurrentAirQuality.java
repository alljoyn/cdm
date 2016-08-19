/*
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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