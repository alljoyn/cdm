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

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.FanSpeedLevel", descriptionLanguage="en")
@Secure
public interface FanSpeedLevel {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getFanSpeedLevel();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public void setFanSpeedLevel(byte fanSpeedLevel);

    @BusProperty(signature="y")
    public byte getMaxFanSpeedLevel();

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