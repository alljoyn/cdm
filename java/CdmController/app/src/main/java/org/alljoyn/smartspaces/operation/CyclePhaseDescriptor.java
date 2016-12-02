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

import org.alljoyn.bus.annotation.Position;
import org.alljoyn.bus.annotation.Signature;

public class CyclePhaseDescriptor {
    @Position(0)
    @Signature("y")
    public byte phase;

    @Position(1)
    @Signature("s")
    public String name;

    @Position(2)
    @Signature("s")
    public String description;

    @Override
    public String toString() {
        return "[" + " phase=" + String.valueOf(phase) + " name=" + "\"" + name + "\"" + " description=" + "\"" + description + "\"" + " ]";
    }
}