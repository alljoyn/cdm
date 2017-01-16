////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
//    Source Project (AJOSP) Contributors and others.
// 
//    SPDX-License-Identifier: Apache-2.0
// 
//    All rights reserved. This program and the accompanying materials are
//    made available under the terms of the Apache License, Version 2.0
//    which accompanies this distribution, and is available at
//    http://www.apache.org/licenses/LICENSE-2.0
// 
//    Copyright 2016 Open Connectivity Foundation and Contributors to
//    AllSeen Alliance. All rights reserved.
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
#import "SpinSpeedLevelViewController.h"
#import "SpinSpeedLevelListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/SpinSpeedLevelIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 2;
static NSInteger NUM_METHODS = 0;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    TARGET_LEVEL_PICKER_TAG = 1,
};

@interface SpinSpeedLevelViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property SpinSpeedLevelListener *listener;
@property std::shared_ptr<ajn::services::SpinSpeedLevelIntfController> spinSpeedLevelIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *targetLevelPicker;
@property std::vector<uint8_t> *selectorValuesForTargetLevel;

@end


@implementation SpinSpeedLevelViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"spin speed level";
        _cdmController = cdmController;
        _device = device;

        _listener = new SpinSpeedLevelListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::SPIN_SPEED_LEVEL_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _spinSpeedLevelIntfController = std::static_pointer_cast<ajn::services::SpinSpeedLevelIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    _targetLevelPicker = [[UIPickerView alloc] init];
    _targetLevelPicker.delegate = self;
    _targetLevelPicker.dataSource = self;
    _targetLevelPicker.showsSelectionIndicator = YES;
    _targetLevelPicker.hidden = NO;
    _targetLevelPicker.tag = TARGET_LEVEL_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForTargetLevel) {
        delete _selectorValuesForTargetLevel;
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
            _maxLevelCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _maxLevelCell.label.text = @"MaxLevel";

            status = _spinSpeedLevelIntfController->GetMaxLevel();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMaxLevel");
            }

            return _maxLevelCell;
        }
        if(indexPath.row == 1) {
            _targetLevelCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _targetLevelCell.label.text = @"TargetLevel";
            _targetLevelCell.value.inputView = _targetLevelPicker;

            status = _spinSpeedLevelIntfController->GetSelectableLevels();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSelectableLevels");
            }                

            status = _spinSpeedLevelIntfController->GetTargetLevel();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTargetLevel");
            }

            return _targetLevelCell;
        }
    }     
    return nil;
}



- (void) setSelectableLevels:(const std::vector<uint8_t>&)selectableLevels
{
    if(self.self.selectorValuesForTargetLevel) {
        delete _selectorValuesForTargetLevel;
    }

    self.selectorValuesForTargetLevel = new std::vector<uint8_t>(selectableLevels);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case TARGET_LEVEL_PICKER_TAG:
            return (NSInteger)self.selectorValuesForTargetLevel->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case TARGET_LEVEL_PICKER_TAG:
        {
            uint8_t targetLevel = self.selectorValuesForTargetLevel->at(row);
            return [NSString stringWithFormat:@"%u", targetLevel];
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case TARGET_LEVEL_PICKER_TAG:
        {
            uint8_t targetLevel = self.selectorValuesForTargetLevel->at(row);
            _spinSpeedLevelIntfController->SetTargetLevel(targetLevel);
            [self.targetLevelCell.value resignFirstResponder];
            break;
        }
        default:
            break;
    }    
}

@end