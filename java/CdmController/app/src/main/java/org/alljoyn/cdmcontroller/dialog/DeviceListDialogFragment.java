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

package org.alljoyn.cdmcontroller.dialog;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;

import org.alljoyn.cdmcontroller.logic.Device;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;


public class DeviceListDialogFragment extends DialogFragment implements DialogListener
{
    private static final String TAG = "CDM_DevListDialogFrag";
    private ArrayList<Device> selectedDevices;
    private Collection<Device> selectableDevices;
    private String groupName = null;
    private DialogListener targetFragment = null;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        try{
            targetFragment = (DialogListener) getTargetFragment();
        } catch (ClassCastException e) {
            throw new ClassCastException("Target fragment must implement the DeviceGroupNameDialogListener interface");
        }
    }

    public Device getDeviceAtIndex(int index) {
        Iterator selectableDevicesIter = selectableDevices.iterator();
        int i = 0;
        while (selectableDevicesIter.hasNext()) {
            Device device = (Device)selectableDevicesIter.next();
            if(index == i) {
                return device;
            }
            i++;
        }
        return null;
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        selectedDevices = new ArrayList();

        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        final String devicesByName[] = new String[selectableDevices.size()];
        Iterator selectableDevicesIter = selectableDevices.iterator();
        int index = 0;
        while (selectableDevicesIter.hasNext()) {
            devicesByName[index] = ((Device)selectableDevicesIter.next()).getName();
            index++;
        }

        builder.setTitle("Choose devices to create a new group")
               .setMultiChoiceItems(devicesByName, null, new DialogInterface.OnMultiChoiceClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which, boolean isChecked) {
                        if(isChecked) {
                            selectedDevices.add(getDeviceAtIndex(which));
                        } else {
                            Device uncheckedDevice = getDeviceAtIndex(which);
                            selectedDevices.remove(uncheckedDevice);
                        }
                    }
                })
               .setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                   @Override
                   public void onClick(DialogInterface dialog, int which) {
                       DeviceGroupNameDialogFragment deviceGroupNameDialogFragment = new DeviceGroupNameDialogFragment();
                       deviceGroupNameDialogFragment.setTargetFragment(DeviceListDialogFragment.this, 0);
                       deviceGroupNameDialogFragment.show(getFragmentManager(), "DeviceGroupNameDialogFragment");
                   }
               })
               .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                   @Override
                   public void onClick(DialogInterface dialog, int which) {
                       targetFragment.onDialogNegativeClick(DeviceListDialogFragment.this);
                   }
               });

        return builder.create();
    }

    public void setSelectableDevices(Collection<Device> selectableDevices) {
        this.selectableDevices = selectableDevices;
    }

    public ArrayList<Device> getSelectedDevices() {
        return selectedDevices;
    }

    public String getGroupName() {
        return groupName;
    }

    @Override
    public void onDialogPositiveClick(DialogFragment dialogFragment) {
        groupName = ((DeviceGroupNameDialogFragment)dialogFragment).getGroupName();
        targetFragment.onDialogPositiveClick(DeviceListDialogFragment.this);
    }

    @Override
    public void onDialogNegativeClick(DialogFragment dialogFragment) {
        targetFragment.onDialogNegativeClick(DeviceListDialogFragment.this);
    }
}
