////////////////////////////////////////////////////////////////////////////////
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
#import "TargetHumidityViewController.h"
#import "TargetHumidityListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/environment/TargetHumidityIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 5;
static NSInteger NUM_METHODS = 0;

@interface TargetHumidityViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property TargetHumidityListener *listener;
@property std::shared_ptr<ajn::services::TargetHumidityIntfController> targetHumidityIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation TargetHumidityViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"target humidity";
        _cdmController = cdmController;
        _device = device;

        _listener = new TargetHumidityListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::TARGET_HUMIDITY_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _targetHumidityIntfController = std::static_pointer_cast<ajn::services::TargetHumidityIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];


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
            _targetValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _targetValueCell.label.text = @"TargetValue";
            _targetValueCell.delegate = self;

            status = _targetHumidityIntfController->GetTargetValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTargetValue");
            }

            return _targetValueCell;
        }
        if(indexPath.row == 1) {
            _minValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _minValueCell.label.text = @"MinValue";

            status = _targetHumidityIntfController->GetMinValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMinValue");
            }

            return _minValueCell;
        }
        if(indexPath.row == 2) {
            _maxValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _maxValueCell.label.text = @"MaxValue";

            status = _targetHumidityIntfController->GetMaxValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMaxValue");
            }

            return _maxValueCell;
        }
        if(indexPath.row == 3) {
            _stepValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _stepValueCell.label.text = @"StepValue";

            status = _targetHumidityIntfController->GetStepValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetStepValue");
            }

            return _stepValueCell;
        }
        if(indexPath.row == 4) {
            _selectableHumidityLevelsCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _selectableHumidityLevelsCell.label.text = @"SelectableHumidityLevels";

            status = _targetHumidityIntfController->GetSelectableHumidityLevels();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSelectableHumidityLevels");
            }

            return _selectableHumidityLevelsCell;
        }
    }     
    return nil;
}

-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    if([property isEqualToString:@"TargetValue"]){
        _targetHumidityIntfController->SetTargetValue((uint8_t)[value longLongValue]);
    }
}




@end