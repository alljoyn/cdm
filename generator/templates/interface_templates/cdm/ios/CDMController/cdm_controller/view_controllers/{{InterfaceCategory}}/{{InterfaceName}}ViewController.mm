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

#import <Foundation/Foundation.h>
#import "CDMUtil.h"
#import "{{Interface.Name}}ViewController.h"
#import "{{Interface.Name}}Listener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/{{Interface.Category}}/{{Interface.Name}}IntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = {% if Interface.Methods %}3{% else %}1{% endif %};
static NSInteger NUM_PROPERTIES = {{ Interface.UIProperties | length }};
static NSInteger NUM_METHODS = {{ Interface.Methods | length }};

{% if Interface.has_property_with_selector() %}
typedef NS_ENUM(NSInteger, PICKER_TAG) {
{% for property in Interface.UserProperties if property.Selector %}
    {{property.Name.upper_snake()}}_PICKER_TAG = {{loop.index}},
{% endfor %}
};

{%endif%}
@interface {{Interface.Name}}ViewController() {% if Interface.has_property_with_selector() %}<UIPickerViewDelegate, UIPickerViewDataSource>{% endif %}

@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property {{Interface.Name}}Listener *listener;
@property std::shared_ptr<ajn::services::{{Interface.Name}}IntfController> {{Interface.Name.camel_case()}}IntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

{% for property in Interface.UserProperties if property.Selector %}
@property (nonatomic, strong) UIPickerView *{{property.Name.camel_case()}}Picker;
@property {{property.Selector.Property.Type.cpptype()}} *selectorValuesFor{{property.Name}};
{% endfor %}

@end


@implementation {{Interface.Name}}ViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"{{Interface.Name.add_spaces()}}";
        _cdmController = cdmController;
        _device = device;

        _listener = new {{Interface.Name}}Listener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::{{Interface.Name.upper_snake()}}_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _{{Interface.Name.camel_case()}}IntfController = std::static_pointer_cast<ajn::services::{{Interface.Name}}IntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    {% for property in Interface.UserProperties if property.Selector %}
    _{{property.Name.camel_case()}}Picker = [[UIPickerView alloc] init];
    _{{property.Name.camel_case()}}Picker.delegate = self;
    _{{property.Name.camel_case()}}Picker.dataSource = self;
    _{{property.Name.camel_case()}}Picker.showsSelectionIndicator = YES;
    _{{property.Name.camel_case()}}Picker.hidden = NO;
    _{{property.Name.camel_case()}}Picker.tag = {{property.Name.upper_snake()}}_PICKER_TAG;
    {% endfor %}
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    {% for property in Interface.UserProperties if property.Selector %}
    if (_selectorValuesFor{{property.Name}}) {
        delete _selectorValuesFor{{property.Name}};
    }
    {% endfor %}

    delete _listener;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return NUM_MEMBER_CATEGORIES;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == SECTION_PROPERTY) {
        return NUM_PROPERTIES;
    } {% if Interface.Methods %}else if (section == SECTION_METHOD) {
        return NUM_METHODS;
    } else if (section == SECTION_METHOD_OUTPUT) {
        return NUM_METHODS;
    } 
    {% endif %}

    return 0;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QStatus status;
    
    if (indexPath.section == SECTION_PROPERTY) {
        {% for property in Interface.UIProperties %}
        if(indexPath.row == {{loop.index0}}) {
            _{{property.Name.camel_case()}}Cell  = [tableView dequeueReusableCellWithIdentifier:{% if property.Writable and not property.Selector %}READ_WRITE_TABLE_VIEW_CELL{% elif property.Selector %}SELECTABLE_TABLE_VIEW_CELL{% else %}READ_ONLY_TABLE_VIEW_CELL{% endif %}];
            _{{property.Name.camel_case()}}Cell.label.text = @"{{property.Name}}";
            {% if property.Writable and not property.Selector %}
            _{{property.Name.camel_case()}}Cell.delegate = self;
            {% endif %}
            {% if property.Selector %}
            _{{property.Name.camel_case()}}Cell.value.inputView = _{{property.Name.camel_case()}}Picker;

            status = _{{Interface.Name.camel_case()}}IntfController->Get{{property.Selector.Name}}();
            if(status != ER_OK) {
                NSLog(@"Failed to get Get{{property.Selector.Name}}");
            }                
            {% endif %}

            status = _{{Interface.Name.camel_case()}}IntfController->Get{{property.Name}}();
            if(status != ER_OK) {
                NSLog(@"Failed to get Get{{property.Name}}");
            }

            return _{{property.Name.camel_case()}}Cell;
        }
        {% endfor %}
    } {% if Interface.Methods %}else if (indexPath.section == SECTION_METHOD) {
        {% for method in Interface.Methods %}
        if(indexPath.row == {{loop.index0}}) {
            _{{method.Name.camel_case()}}Cell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _{{method.Name.camel_case()}}Cell.label.text = @"{{method.Name}}";
            _{{method.Name.camel_case()}}Cell.delegate = self;
            return _{{method.Name.camel_case()}}Cell;
        }
        {% endfor %}
    } else if (indexPath.section == SECTION_METHOD_OUTPUT) {
        {% for method in Interface.Methods %}
        if(indexPath.row == {{loop.index0}}) {
            _{{method.Name.camel_case()}}OutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _{{method.Name.camel_case()}}OutputCell.output.text = @"";
            return _{{method.Name.camel_case()}}OutputCell;
        }
        {% endfor %}
    } 
    {% endif %}
    
    return nil;
}

{% if Interface.has_writable_property() %}
-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    {% for property in Interface.UIProperties %}
    {% if property.Writable %}
    if([property isEqualToString:@"{{property.Name}}"]){
        {% if property.is_bool() %}
        _{{Interface.Name.camel_case()}}IntfController->Set{{property.Name}}(({{property.Type.cpptype_arg()}})[value boolValue]);
        {% elif property.is_string() %}
        _{{Interface.Name.camel_case()}}IntfController->Set{{property.Name}}({{property.Type.cpptype()}}([value cStringUsingEncoding:NSUTF8StringEncoding]));
        {% else %}
        _{{Interface.Name.camel_case()}}IntfController->Set{{property.Name}}(({{property.Type.cpptype_arg()}})[value longLongValue]);
        {% endif %}
    }
    {% endif %}
    {% endfor %}
}
{% endif %}

{% if Interface.Methods %}
-(void) executeMethod:(NSString *)methodName
{
    {% for method in Interface.Methods %}
    if([methodName isEqualToString:@"{{method.Name}}"]){
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Enter parameters"
                                                                                 message:@""
                                                                          preferredStyle:UIAlertControllerStyleAlert];

        [alertController addAction:[UIAlertAction actionWithTitle:@"Cancel"
                                                            style:UIAlertActionStyleDefault
                                                          handler:nil]];

        [alertController addAction:[UIAlertAction actionWithTitle:@"Run"
                                                            style:UIAlertActionStyleDefault
                                                          handler:^(UIAlertAction * _Nonnull action) {
                                                              NSLog(@"Executing %@ from the view controller", methodName);
                                                              {% for arg in method.input_args() %}
                                                              {% if arg.Type.is_bool() %}
                                                              {{arg.Type.cpptype()}} {{arg.Name.camel_case()}}Command = ({{arg.Type.cpptype()}})[alertController.textFields[{{loop.index0}}].text boolValue];
                                                              {% elif arg.Type.is_string() %}
                                                              {{arg.Type.cpptype()}} {{arg.Name.camel_case()}}Command = ({{arg.Type.cpptype()}})[alertController.textFields[{{loop.index0}}].text cStringUsingEncoding:NSUTF8StringEncoding];
                                                              {% else %}
                                                              {{arg.Type.cpptype()}} {{arg.Name.camel_case()}}Command = ({{arg.Type.cpptype()}})[alertController.textFields[{{loop.index0}}].text longLongValue];
                                                              {% endif %}
                                                              {% endfor %}
                                                              _{{Interface.Name.camel_case()}}IntfController->{{method.Name}}({% for arg in method.input_args() %}{{arg.Name.camel_case()}}Command{% if not loop.last %},{% endif %}{% endfor %});
                                                          }]];

        {% for arg in method.input_args() %}
        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"{{arg.Name}}";
            textField.text = @"";
        }];
        {% endfor %}

        [self presentViewController:alertController animated:YES completion:nil];
    }

    {% endfor %}
}
{% endif %}

{% for property in Interface.UserProperties if property.Selector %}
- (void) set{{property.Selector.Name}}:(const {{property.Selector.Property.Type.cpptype_arg()}}){{property.Selector.Name.camel_case()}}
{
    if(self.self.selectorValuesFor{{property.Name}}) {
        delete _selectorValuesFor{{property.Name}};
    }

    self.selectorValuesFor{{property.Name}} = new {{property.Selector.Property.Type.cpptype()}}({{property.Selector.Name.camel_case()}});
}
{% endfor %}

{% if Interface.has_property_with_selector() %}
#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        {% for property in Interface.UserProperties if property.Selector %}
        case {{property.Name.upper_snake()}}_PICKER_TAG:
            return (NSInteger)self.selectorValuesFor{{property.Name}}->size();
        {% endfor %}
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        {% for property in Interface.UserProperties if property.Selector %}
        case {{property.Name.upper_snake()}}_PICKER_TAG:
        {
            {{property.Type.cpptype()}} {{property.Name.camel_case()}} = self.selectorValuesFor{{property.Name}}->at(row);
            return [NSString stringWithFormat:@"%{{property.Type.objc_format_str()}}", {{property.Name.camel_case()}}];
        }
        {% endfor %}
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        {% for property in Interface.UserProperties if property.Selector %}
        case {{property.Name.upper_snake()}}_PICKER_TAG:
        {
            {{property.Type.cpptype()}} {{property.Name.camel_case()}} = self.selectorValuesFor{{property.Name}}->at(row);
            _{{Interface.Name.camel_case()}}IntfController->Set{{property.Name}}({{property.Name.camel_case()}});
            [self.{{property.Name.camel_case()}}Cell.value resignFirstResponder];
            break;
        }
        {% endfor %}
        default:
            break;
    }    
}
{% endif %}

@end