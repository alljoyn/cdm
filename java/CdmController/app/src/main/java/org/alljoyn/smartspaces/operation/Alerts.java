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

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.Alerts", descriptionLanguage="en")
@Secure
public interface Alerts {
    @BusProperty(signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="a(yqb)")
    public AlertRecord[] getAlerts();

    @BusMethod(name="GetAlertCodesDescription", signature="s", replySignature = "a(qs)")
    public AlertCodesDescriptor[] getAlertCodesDescription(String languageTag);

    @BusMethod(name="AcknowledgeAlert", signature="q")
    public void acknowledgeAlert(short alertCode);

    @BusMethod(name="AcknowledgeAllAlerts")
    public void acknowledgeAllAlerts();

    public enum Severity implements EnumBase<Integer> {
        warning((int)0),
        alarm((int)1),
        fault((int)2){};

        private Integer value;
        private Severity(int value) {
            this.value = value;
        }

        public Integer toValue() {
            return this.value;
        }
    }

    public class AlertRecord {
        @Position(0)
        @Signature("i")
        public int severity;

        @Position(1)
        @Signature("q")
        public short alertCode;

        @Position(2)
        @Signature("b")
        public boolean needAcknowledgement;

        @Override
        public String toString() {
            return "[" + " severity=" + "\"" + severity + "\"" + " alertCode=" + "\"" + alertCode + "\"" + " needAcknowledgement=" + "\"" + needAcknowledgement + "\"" + " ]";
        }
    }

    public class AlertCodesDescriptor {
        @Position(0)
        @Signature("q")
        public short alertCode;

        @Position(1)
        @Signature("s")
        public String description;

        @Override
        public String toString() {
            return "[" + " alertCode=" + "\"" + alertCode + "\"" + " description=" + "\"" + description + "\"" + " ]";
        }
    }

}