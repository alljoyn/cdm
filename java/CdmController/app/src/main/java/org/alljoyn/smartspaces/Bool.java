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

package org.alljoyn.smartspaces;

public enum Bool implements EnumBase<Boolean> {
    True(true) {
        @Override
        public String toString() {
            return "true";
        }
    },
    False(false) {
        @Override
        public String toString() {
            return "false";
        }
    };
    private boolean value;
    private Bool(boolean value) {
        this.value = value;
    }
    public Boolean toValue() {
        return value;
    }
}