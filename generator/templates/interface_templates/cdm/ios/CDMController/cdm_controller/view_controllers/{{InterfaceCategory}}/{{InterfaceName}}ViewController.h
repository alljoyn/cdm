////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
//
//    SPDX-License-Identifier: Apache-2.0
//
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
//    Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for
//    any purpose with or without fee is hereby granted, provided that the
//    above copyright notice and this permission notice appear in all
//    copies.
//
//     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//     PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef {{Interface.Name}}ViewController_h
#define {{Interface.Name}}ViewController_h

#import "InterfaceViewController.h"
#import "alljoyn/cdm/CdmController.h"
#import "Device.h"
#import "ReadOnlyValuePropertyCell.h"
{% if Interface.has_writable_property() %}
#import "ReadWriteValuePropertyCell.h"
{% endif %}
{% if Interface.has_property_with_selector() %}
#import "SelectableValuePropertyCell.h"
{% endif %}
{% if Interface.Methods %}
#import "MethodViewCell.h"
#import "MethodViewOutputCell.h"
{% endif %}

@interface {{Interface.Name}}ViewController : InterfaceViewController {% if Interface.has_writable_property() or Interface.Methods %}<{% if Interface.has_writable_property() %}ReadWriteValueDelegate{% endif %}{% if Interface.Methods %}{% if Interface.has_writable_property() %}, {% endif %}MethodViewDelegate{% endif %}>{% endif %}

{% for property in Interface.UIProperties %}
{% if property.Writable %}
{% if property.Selector %}
@property (nonatomic, strong) SelectableValuePropertyCell *{{property.Name.camel_case()}}Cell;
{% else %}
@property (nonatomic, strong) ReadWriteValuePropertyCell *{{property.Name.camel_case()}}Cell;
{% endif %}
{% else %}
@property (nonatomic, strong) ReadOnlyValuePropertyCell *{{property.Name.camel_case()}}Cell;
{% endif %}
{% endfor %}
{% for method in Interface.Methods %}
@property (nonatomic, strong) MethodViewCell *{{method.Name.camel_case()}}Cell;
@property (nonatomic, strong) MethodViewOutputCell *{{method.Name.camel_case()}}OutputCell;
{% endfor %}

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController;
{% for property in Interface.UserProperties if property.Selector %}
- (void) set{{property.Selector.Name}}:(const {{property.Selector.Property.Type.cpptype_arg()}}){{property.Selector.Name.camel_case()}};
{% endfor %}

@end

#endif /* {{Interface.Name}}ViewController_h */