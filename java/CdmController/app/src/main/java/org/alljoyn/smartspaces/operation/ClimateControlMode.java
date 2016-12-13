/*
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.ClimateControlMode", descriptionLanguage="en")
@Secure
public interface ClimateControlMode {
    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getMode();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public void setMode(short mode);

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="aq")
    public short[] getSupportedModes();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getOperationalState();

    public enum Mode implements EnumBase<Short> {
        Off((short)0),
        Heat((short)1),
        Cool((short)2),
        Auto((short)3),
        AuxiliaryHeat((short)4),
        Dry((short)5),
        Continuous_Dry((short)6);

        private short value;

        @Override
        public Short toValue() {
            return this.value;
        }

        private Mode(short value) {
            this.value = value;
        }
    }

    public enum OperationalState implements EnumBase<Short> {
        Idle((short)0),
        Heating((short)1),
        Cooling((short)2),
        Pending_Heat((short)3),
        Pending_Cool((short)4),
        Auxilliary_Heat((short)5);

        private short value;
        private OperationalState(short value) {
            this.value = value;
        }
        @Override
        public Short toValue() {
            return this.value;
        }
    }
}