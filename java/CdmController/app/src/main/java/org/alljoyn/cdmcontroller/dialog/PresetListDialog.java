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

package org.alljoyn.cdmcontroller.dialog;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;

import org.alljoyn.cdmcontroller.logic.Preset;
import org.alljoyn.cdmcontroller.logic.PresetManager;

import java.util.ArrayList;
import java.util.List;


public class PresetListDialog extends DialogFragment
{
    private static final String TAG = "CDM_PresetListDialog";
    private Preset selectedPreset;
    private String interfaceName;
    private DialogListener targetFragment = null;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        try{
            targetFragment = (DialogListener) getTargetFragment();
        } catch (ClassCastException e) {
            throw new ClassCastException("Target fragment must implement the DialogListener interface");
        }
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        List<Preset> presets = PresetManager.getInstance().getPresetsForInterface(interfaceName);
        if (presets == null){
            presets = new ArrayList<>();
        }

        String[] presetNames = new String[presets.size()];

        int i = 0;
        for(Preset preset : presets) {
            presetNames[i] = preset.getName();
            i++;
        }

        final List<Preset> finalPresets = presets;
        builder.setTitle("Choose preset")
                .setSingleChoiceItems(presetNames, -1, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        selectedPreset = finalPresets.get(which);
                    }
                })
                .setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    targetFragment.onDialogPositiveClick(PresetListDialog.this);
                    }
                })
                .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    targetFragment.onDialogNegativeClick(PresetListDialog.this);
                    }
                });

        return builder.create();
    }

    public void setInterface(String interfaceName) {
        this.interfaceName = interfaceName;
    }

    public Preset getSelectedPreset() {
        return selectedPreset;
    }
}