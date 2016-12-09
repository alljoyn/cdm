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

package org.alljoyn.cdmcontroller.logic;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class PresetManager
{
    private static PresetManager manager = null;
    private Map<String, List<Preset>> interfacePresets = null;

    public PresetManager() {
        interfacePresets = new HashMap<>();
    }

    public static PresetManager getInstance() {
        if(manager == null) {
            manager = new PresetManager();
        }
        return manager;
    }

    public void addPreset(String interfaceName, Preset preset) {
        List presets = interfacePresets.get(interfaceName);
        if(presets == null){
            presets = new ArrayList();
            interfacePresets.put(interfaceName, presets);
        }
        presets.add(preset);
    }

    public void removePreset(String interfaceName, Preset preset) {
        List presets = interfacePresets.get(interfaceName);
        if(presets == null){
            return;
        }
        presets.remove(preset);
    }

    public List<Preset> getPresetsForInterface(String interfaceName) {
        return interfacePresets.get(interfaceName);
    }
}