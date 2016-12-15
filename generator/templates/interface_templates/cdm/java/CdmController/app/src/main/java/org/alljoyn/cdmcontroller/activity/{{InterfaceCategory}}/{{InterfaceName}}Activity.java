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

package org.alljoyn.cdmcontroller.activity.{{Interface.Category}};

import android.view.View;

import org.alljoyn.bus.annotation.BusSignalHandler;
import org.alljoyn.cdmcontroller.activity.InterfaceActivity;
import org.alljoyn.cdmcontroller.view.property.MinMaxPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadOnlyValuePropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteValuePropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteEnumPropertyView;
import org.alljoyn.cdmcontroller.view.property.ReadWriteBoolPropertyView;
import org.alljoyn.cdmcontroller.view.method.MethodView;
import org.alljoyn.smartspaces.{{Interface.Category}}.{{Interface.Name}};

// This generated activity presents the view to the best of its ability.
// It is up to the developer to use different PropertyViews to provide better UX
// and to specify the units of properties (absent on the interface descriptions).
public class {{Interface.Name}}Activity extends InterfaceActivity {
    private static final String INTERFACE_NAME = "{{Interface.FullName}}";

    @Override
    protected void generatePropertyView(CustomView properties, CustomView methods) {
        {% for property in Interface.UserProperties %}
        {% if property.Writable %}
        {% if property.is_bool() %}
        View {{property.Name.camel_case()}}View = new ReadWriteBoolPropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "{{property.Name}}");
        {% elif property.is_enum() %}
        View {{property.Name.camel_case()}}View = new ReadWriteEnumPropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "{{property.Name}}", {{property.parent_interface.Name}}.{{property.enum_name()}}.class);
        {% else %}
        View {{property.Name.camel_case()}}View = new ReadWriteValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "{{property.Name}}", null);
        {% endif %}
        {% else %}
        {% if property.is_enum() %}
        View {{property.Name.camel_case()}}View = new ReadOnlyEnumPropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "{{property.Name}}", {{property.parent_interface.Name}}.{{property.enum_name()}}.class);
        {% endif %}
        View {{property.Name.camel_case()}}View = new ReadOnlyValuePropertyView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "{{property.Name}}", null);
        {% endif %}
        properties.addView({{property.Name.camel_case()}}View);

        {% endfor %}
        {% for method in Interface.Methods %}
        View {{method.Name.camel_case()}}View = new MethodView(getActivity(), this.device, this.objPath, INTERFACE_NAME, "{{method.Name}}");
        methods.addView({{method.Name.camel_case()}}View);

        {% endfor %}
    }

    {% for signal in Interface.Signals %}
    @BusSignalHandler(iface = "{{Interface.FullName}}", signal = "{{signal.Name}}")
    public void {{signal.Name.camel_case()}}() {
        notifyEvent("{{signal.Name}}");
    }

    {% endfor %}
}
