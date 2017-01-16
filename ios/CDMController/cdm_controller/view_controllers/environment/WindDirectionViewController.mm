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
#import "WindDirectionViewController.h"
#import "WindDirectionListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/environment/WindDirectionIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 6;
static NSInteger NUM_METHODS = 0;

@interface WindDirectionViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property WindDirectionListener *listener;
@property std::shared_ptr<ajn::services::WindDirectionIntfController> windDirectionIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation WindDirectionViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"wind direction";
        _cdmController = cdmController;
        _device = device;

        _listener = new WindDirectionListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::WIND_DIRECTION_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _windDirectionIntfController = std::static_pointer_cast<ajn::services::WindDirectionIntfController>(_cdmInterface);

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
            _horizontalDirectionCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _horizontalDirectionCell.label.text = @"HorizontalDirection";
            _horizontalDirectionCell.delegate = self;

            status = _windDirectionIntfController->GetHorizontalDirection();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetHorizontalDirection");
            }

            return _horizontalDirectionCell;
        }
        if(indexPath.row == 1) {
            _horizontalMaxCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _horizontalMaxCell.label.text = @"HorizontalMax";

            status = _windDirectionIntfController->GetHorizontalMax();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetHorizontalMax");
            }

            return _horizontalMaxCell;
        }
        if(indexPath.row == 2) {
            _horizontalAutoModeCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _horizontalAutoModeCell.label.text = @"HorizontalAutoMode";
            _horizontalAutoModeCell.delegate = self;

            status = _windDirectionIntfController->GetHorizontalAutoMode();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetHorizontalAutoMode");
            }

            return _horizontalAutoModeCell;
        }
        if(indexPath.row == 3) {
            _verticalDirectionCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _verticalDirectionCell.label.text = @"VerticalDirection";
            _verticalDirectionCell.delegate = self;

            status = _windDirectionIntfController->GetVerticalDirection();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetVerticalDirection");
            }

            return _verticalDirectionCell;
        }
        if(indexPath.row == 4) {
            _verticalMaxCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _verticalMaxCell.label.text = @"VerticalMax";

            status = _windDirectionIntfController->GetVerticalMax();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetVerticalMax");
            }

            return _verticalMaxCell;
        }
        if(indexPath.row == 5) {
            _verticalAutoModeCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _verticalAutoModeCell.label.text = @"VerticalAutoMode";
            _verticalAutoModeCell.delegate = self;

            status = _windDirectionIntfController->GetVerticalAutoMode();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetVerticalAutoMode");
            }

            return _verticalAutoModeCell;
        }
    }     
    return nil;
}

-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    if([property isEqualToString:@"HorizontalDirection"]){
        _windDirectionIntfController->SetHorizontalDirection((uint16_t)[value longLongValue]);
    }
    if([property isEqualToString:@"HorizontalAutoMode"]){
        _windDirectionIntfController->SetHorizontalAutoMode((WindDirectionListener::AutoMode)[value longLongValue]);
    }
    if([property isEqualToString:@"VerticalDirection"]){
        _windDirectionIntfController->SetVerticalDirection((uint16_t)[value longLongValue]);
    }
    if([property isEqualToString:@"VerticalAutoMode"]){
        _windDirectionIntfController->SetVerticalAutoMode((WindDirectionListener::AutoMode)[value longLongValue]);
    }
}




@end