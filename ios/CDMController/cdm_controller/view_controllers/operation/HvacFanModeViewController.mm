////////////////////////////////////////////////////////////////////////////////
//    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
//    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
//    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
//    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
//    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
//    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
//    PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import "CDMUtil.h"
#import "HvacFanModeViewController.h"
#import "HvacFanModeListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/HvacFanModeIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 1;
static NSInteger NUM_METHODS = 0;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    MODE_PICKER_TAG = 1,
};

@interface HvacFanModeViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property HvacFanModeListener *listener;
@property std::shared_ptr<ajn::services::HvacFanModeIntfController> hvacFanModeIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *modePicker;
@property std::vector<HvacFanModeListener::Mode> *selectorValuesForMode;

@end


@implementation HvacFanModeViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"hvac fan mode";
        _cdmController = cdmController;
        _device = device;

        _listener = new HvacFanModeListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::HVAC_FAN_MODE_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _hvacFanModeIntfController = std::static_pointer_cast<ajn::services::HvacFanModeIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    _modePicker = [[UIPickerView alloc] init];
    _modePicker.delegate = self;
    _modePicker.dataSource = self;
    _modePicker.showsSelectionIndicator = YES;
    _modePicker.hidden = NO;
    _modePicker.tag = MODE_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForMode) {
        delete _selectorValuesForMode;
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
            _modeCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _modeCell.label.text = @"Mode";
            _modeCell.value.inputView = _modePicker;

            status = _hvacFanModeIntfController->GetSupportedModes();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedModes");
            }                

            status = _hvacFanModeIntfController->GetMode();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMode");
            }

            return _modeCell;
        }
    }     
    return nil;
}



- (void) setSupportedModes:(const std::vector<HvacFanModeListener::Mode>&)supportedModes
{
    if(self.self.selectorValuesForMode) {
        delete _selectorValuesForMode;
    }

    self.selectorValuesForMode = new std::vector<HvacFanModeListener::Mode>(supportedModes);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case MODE_PICKER_TAG:
            return (NSInteger)self.selectorValuesForMode->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case MODE_PICKER_TAG:
        {
            HvacFanModeListener::Mode mode = self.selectorValuesForMode->at(row);
            return [NSString stringWithFormat:@"%hu", mode];
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case MODE_PICKER_TAG:
        {
            HvacFanModeListener::Mode mode = self.selectorValuesForMode->at(row);
            _hvacFanModeIntfController->SetMode(mode);
            [self.modeCell.value resignFirstResponder];
            break;
        }
        default:
            break;
    }    
}

@end