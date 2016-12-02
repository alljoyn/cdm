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

package org.alljoyn.smartspaces.operation;

import org.alljoyn.bus.annotation.BusInterface;
import org.alljoyn.bus.annotation.BusMethod;
import org.alljoyn.bus.annotation.BusSignal;
import org.alljoyn.bus.annotation.BusProperty;
import org.alljoyn.bus.annotation.Secure;
import org.alljoyn.bus.BusException;
import org.alljoyn.bus.annotation.Signature;
import org.alljoyn.bus.annotation.Position;

@BusInterface(name="org.alljoyn.SmartSpaces.Operation.Channel", descriptionLanguage="en")
@Secure
public interface Channel {
    public class ChannelInfoRecord {
        @Position(0)
        @Signature("s")
        public String channelID;

        @Position(1)
        @Signature("s")
        public String channelNumber;

        @Position(2)
        @Signature("s")
        public String channelName;

        @Override
        public String toString() {
            return "[" + " channelID=" + "\"" + channelID + "\"" + " channelNumber=" + "\"" + channelNumber + "\"" + " channelName=" + "\"" + channelName + "\"" + " ]";
        }
    }

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getVersion();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="s")
    public String getChannelId();

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="s")
    public void setChannelId(String channelId);

    @BusProperty(annotation=BusProperty.ANNOTATE_EMIT_CHANGED_SIGNAL, signature="q")
    public short getTotalNumberOfChannels();

    @BusMethod(name="GetChannelList", signature="qq", replySignature = "a(sss)")
    public ChannelInfoRecord[] getChannelList(short startingRecord, short numRecords);

    @BusSignal(name="ChannelListChanged")
    public void channelListChanged();
}