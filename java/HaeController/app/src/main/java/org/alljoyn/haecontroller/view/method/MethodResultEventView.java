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

package org.alljoyn.haecontroller.view.method;

import android.content.Context;
import org.alljoyn.haecontroller.view.property.OnMethodResultListener;
import java.util.ArrayList;

public class MethodResultEventView extends MethodView {
    private ArrayList<OnMethodResultListener> onResultListener = null;

    public MethodResultEventView(Context context, Object obj, String methodName, String... paramNames) {
        super(context, obj, methodName, paramNames);
    }

    @Override
    protected void onResult(Object result) {
        super.onResult(result);
        if (onResultListener != null) {
            for (OnMethodResultListener listener : onResultListener) {
                listener.OnMethodResultReceived(result);
            }
        }
    }

    public void addOnResultListener(OnMethodResultListener listener) {
        if (onResultListener == null)
            onResultListener = new ArrayList<OnMethodResultListener>();
        onResultListener.add(listener);
    }

}
