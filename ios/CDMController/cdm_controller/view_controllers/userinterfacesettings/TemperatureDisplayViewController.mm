////////////////////////////////////////////////////////////////////////////////
// //    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#import "TemperatureDisplayViewController.h"
#import "TemperatureDisplayListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 1;
static NSInteger NUM_METHODS = 0;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    DISPLAY_TEMPERATURE_UNIT_PICKER_TAG = 1,
};

@interface TemperatureDisplayViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property TemperatureDisplayListener *listener;
@property std::shared_ptr<ajn::services::TemperatureDisplayIntfController> temperatureDisplayIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *displayTemperatureUnitPicker;
@property std::vector<uint8_t> *selectorValuesForDisplayTemperatureUnit;

@end


@implementation TemperatureDisplayViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"temperature display";
        _cdmController = cdmController;
        _device = device;

        _listener = new TemperatureDisplayListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::TEMPERATURE_DISPLAY_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _temperatureDisplayIntfController = std::static_pointer_cast<ajn::services::TemperatureDisplayIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    _displayTemperatureUnitPicker = [[UIPickerView alloc] init];
    _displayTemperatureUnitPicker.delegate = self;
    _displayTemperatureUnitPicker.dataSource = self;
    _displayTemperatureUnitPicker.showsSelectionIndicator = YES;
    _displayTemperatureUnitPicker.hidden = NO;
    _displayTemperatureUnitPicker.tag = DISPLAY_TEMPERATURE_UNIT_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForDisplayTemperatureUnit) {
        delete _selectorValuesForDisplayTemperatureUnit;
    }

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
    } 
    return 0;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QStatus status;
    
    if (indexPath.section == SECTION_PROPERTY) {
        if(indexPath.row == 0) {
            _displayTemperatureUnitCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _displayTemperatureUnitCell.label.text = @"DisplayTemperatureUnit";
            _displayTemperatureUnitCell.value.inputView = _displayTemperatureUnitPicker;

            status = _temperatureDisplayIntfController->GetSupportedDisplayTemperatureUnits();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedDisplayTemperatureUnits");
            }                

            status = _temperatureDisplayIntfController->GetDisplayTemperatureUnit();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetDisplayTemperatureUnit");
            }

            return _displayTemperatureUnitCell;
        }
    }     
    return nil;
}



- (void) setSupportedDisplayTemperatureUnits:(const std::vector<uint8_t>&)supportedDisplayTemperatureUnits
{
    if(self.self.selectorValuesForDisplayTemperatureUnit) {
        delete _selectorValuesForDisplayTemperatureUnit;
    }

    self.selectorValuesForDisplayTemperatureUnit = new std::vector<uint8_t>(supportedDisplayTemperatureUnits);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case DISPLAY_TEMPERATURE_UNIT_PICKER_TAG:
            return (NSInteger)self.selectorValuesForDisplayTemperatureUnit->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case DISPLAY_TEMPERATURE_UNIT_PICKER_TAG:
        {
            uint8_t displayTemperatureUnit = self.selectorValuesForDisplayTemperatureUnit->at(row);
            return [NSString stringWithFormat:@"%u", displayTemperatureUnit];
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case DISPLAY_TEMPERATURE_UNIT_PICKER_TAG:
        {
            uint8_t displayTemperatureUnit = self.selectorValuesForDisplayTemperatureUnit->at(row);
            _temperatureDisplayIntfController->SetDisplayTemperatureUnit(displayTemperatureUnit);
            [self.displayTemperatureUnitCell.value resignFirstResponder];
            break;
        }
        default:
            break;
    }    
}

@end