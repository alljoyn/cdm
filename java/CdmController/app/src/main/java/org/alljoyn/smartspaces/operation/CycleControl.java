/*
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
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

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.CycleControl", descriptionLanguage="en")
@Secure
public interface CycleControl {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="y")
    public byte getOperationalState();

    @BusProperty(signature="ay")
    public byte[] getSupportedOperationalStates();

    @BusProperty(signature="ay")
    public byte[] getSupportedOperationalCommands();

    @BusMethod(name="ExecuteOperationalCommand", signature="y")
    public void executeOperationalCommand(byte command);

    public enum OperationalState implements EnumBase<Byte> {
        Idle((byte)0x00),
        Working((byte)0x01),
        ReadyToStart((byte)0x02),
        DelayedStart((byte)0x03),
        Paused((byte)0x04);

        private byte value;

        @Override
        public Byte toValue() {
            return this.value;
        }

        private OperationalState(byte value) {
            this.value = value;
        }
    }

    public enum OperationalCommand implements EnumBase<Byte> {
        Start((byte)0x00),
        Stop((byte)0x01),
        Pause((byte)0x02),
        Resume((byte)0x03);

        private byte value;

        @Override
        public Byte toValue() {
            return this.value;
        }

        private OperationalCommand(byte value) {
            this.value = value;
        }
    }
}