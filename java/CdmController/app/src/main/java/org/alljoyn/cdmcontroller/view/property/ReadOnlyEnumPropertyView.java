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

package org.alljoyn.haecontroller.view.property;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.alljoyn.haecontroller.view.PropertyView;
import org.alljoyn.smartspaces.EnumBase;
import org.alljoyn.haecontroller.R;
import org.alljoyn.haecontroller.util.HaeUtil;

public class ReadOnlyEnumPropertyView<T extends EnumBase<?>> extends PropertyView {
    private static final String TAG = "HAE_ReadWriteProperty";

    private TextView nameView;
    private TextView valueView;

    private Class<T> clazz;

    public ReadOnlyEnumPropertyView(Context context, Object obj, String propertyName, Class<T> clazz) {
        super(context, obj, propertyName, null);
        this.clazz = clazz;
    }

    public void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        ViewGroup view = (ViewGroup) inflater.inflate(R.layout.view_readonly_property, this, false);

        this.addView(view);

        this.nameView = (TextView) view.findViewById(R.id.property_name);
        this.valueView = (TextView) view.findViewById(R.id.property_value);
        view.findViewById(R.id.property_value_ext).setVisibility(View.GONE);
        view.findViewById(R.id.property_unit).setVisibility(View.GONE);
        Log.d(TAG, "1: valueView is " + this.valueView.toString());

        this.nameView.setText(this.name);
    }

    @Override
    public void setValueView(Object value) {
        T item = (T)HaeUtil.findEnum(value, this.clazz);
        if (item != null) {
            this.valueView.setText(item.toString());
        } else {
            this.valueView.setText("Undefined");
        }
    }
}
