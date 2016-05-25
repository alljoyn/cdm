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