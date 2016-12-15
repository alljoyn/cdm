/*
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

package org.alljoyn.cdmcontroller.util;

import android.app.Activity;
import android.content.Context;
import android.view.inputmethod.InputMethodManager;

import org.alljoyn.smartspaces.EnumBase;

import java.lang.reflect.Array;
import java.util.UUID;

public class CdmUtil {

    public static String removeDot(String value) {
        return value.replaceAll("[.]0+$", "");
    }

    public static <M> Object[] parseParams(Class<M> clazz, Object... objs) {
        Object[] params = new Object[objs.length];

        int idx = 0;
        for (Object obj : objs) {
            params[idx] = parseParam(clazz, obj);
            idx++;
        }
        return params;
    }

    public static <M> Object parseParam(Class<M> clazz, Object obj) {
        try {
            // class compare || primitive type compare
            if (clazz == obj.getClass() || clazz == obj.getClass().getField("TYPE").get(null))
                return obj;
        } catch (IllegalAccessException e) {
        } catch (NoSuchFieldException e) {
        }

        if (clazz == String.class) {
            return obj.toString();
        }

        if (clazz == Boolean.TYPE) {
            return removeDot(obj.toString()).equals("0") || obj.equals("false") ? Boolean.FALSE : Boolean.TRUE;
        }

        // Numeric type
        String value = "";
        if (obj instanceof Boolean) {
            value = obj.equals(true) ? "1" : "0";
        } else {
            value = removeDot(obj.toString());
        }

        if (clazz == Double.TYPE) {
            return Double.parseDouble(value);
        } else if (clazz == Long.TYPE) {
            return Long.parseLong(removeDot(value));
        } else if (clazz == Integer.TYPE) {
            return Integer.parseInt(value);
        } else if (clazz == Short.TYPE) {
            return Short.parseShort(value);
        } else if (clazz == Byte.TYPE) {
            return Byte.parseByte(value);
        }
        return obj;
    }

    public static Object[] toObjectArray(Object outputs) {
        if (!outputs.getClass().isArray()) {
            Object[] result = { outputs };
            return result;
        }
        int length = Array.getLength(outputs);
        Object[] ret = new Object[length];
        for(int i = 0; i < length; i++)
            ret[i] = Array.get(outputs, i);
        return ret;
    }

    public static String toString(Object outputs) {
        if (!outputs.getClass().isArray()) {
            return removeDot(outputs.toString());
        }
        String strResult = "";
        if (outputs.getClass() == String.class) {
            strResult = outputs.toString();
        } else {
            Object[] objects = toObjectArray(outputs);
            for (int i = 0; i < objects.length; i++) {
                strResult += objects[i].toString();
                if (i < objects.length - 1) {
                    strResult += ",\n";
                }
            }
        }
        return strResult;
    }

    public static UUID byteArrayToUUID(byte[] var0) {
        long var1 = 0L;
        long var3 = 0L;
        if (var0 != null && var0.length == 16) {
            int var5;
            for (var5 = 0; var5 < 8; ++var5) {
                var1 = var1 << 8 | (long) (var0[var5] & 255);
            }

            for (var5 = 8; var5 < 16; ++var5) {
                var3 = var3 << 8 | (long) (var0[var5] & 255);
            }

            UUID var6 = new UUID(var1, var3);
            return var6;
        } else {
            return null;
        }
    }

    public static void hideKeyboard(Activity activity) {
        if (activity != null) {
            InputMethodManager inputManager = (InputMethodManager) activity.getSystemService(Context.INPUT_METHOD_SERVICE);
            if (activity.getCurrentFocus() != null && inputManager != null) {
                inputManager.hideSoftInputFromWindow(activity.getCurrentFocus().getWindowToken(), 0);
                inputManager.showSoftInputFromInputMethod(activity.getCurrentFocus().getWindowToken(), 0);
            }
        }
    }

    public static <M, T extends EnumBase<?>> EnumBase<?> findEnum(M value, Class<T> clazz) {
        for (EnumBase item : clazz.getEnumConstants()) {
            if (item.toValue().equals(value)) {
                return item;
            }
        }
        return null;
    }

    public static <T extends EnumBase<?>> EnumBase<?> findEnum(String name, Class<T> clazz) {
        for (EnumBase item : clazz.getEnumConstants()) {
            if (item.toString().equals(name)) {
                return item;
            }
        }
        return null;
    }
}