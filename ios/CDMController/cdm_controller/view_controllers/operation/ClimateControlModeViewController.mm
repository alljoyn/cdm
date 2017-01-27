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
#import "ClimateControlModeViewController.h"
#import "ClimateControlModeListener.h"
#import "alljoyn/cdm/common/CdmInterfaceTypes.h"
#import "alljoyn/cdm/common/CdmInterface.h"
#import "interfaces/controller/operation/ClimateControlModeIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 3;
static NSInteger NUM_METHODS = 0;

@interface ClimateControlModeViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property std::shared_ptr<ClimateControlModeListener> listener;
@property std::shared_ptr<ajn::services::ClimateControlModeIntfController> climateControlModeIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation ClimateControlModeViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"climate control mode";
        _cdmController = cdmController;
        _device = device;

        _listener = std::shared_ptr<ClimateControlModeListener>(new ClimateControlModeListener(self));

        _cdmInterface = _cdmController->CreateInterface(ajn::services::CdmInterface::GetInterfaceName(ajn::services::CLIMATE_CONTROL_MODE_INTERFACE),
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        _listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _climateControlModeIntfController = std::static_pointer_cast<ajn::services::ClimateControlModeIntfController>(_cdmInterface);

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
            _modeCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _modeCell.label.text = @"Mode";
            _modeCell.delegate = self;

            status = _climateControlModeIntfController->GetMode();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMode");
            }

            return _modeCell;
        }
        if(indexPath.row == 1) {
            _supportedModesCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _supportedModesCell.label.text = @"SupportedModes";

            status = _climateControlModeIntfController->GetSupportedModes();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedModes");
            }

            return _supportedModesCell;
        }
        if(indexPath.row == 2) {
            _operationalStateCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _operationalStateCell.label.text = @"OperationalState";

            status = _climateControlModeIntfController->GetOperationalState();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetOperationalState");
            }

            return _operationalStateCell;
        }
    }     
    return nil;
}

-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    if([property isEqualToString:@"Mode"]){
        _climateControlModeIntfController->SetMode((ClimateControlModeInterface::Mode)[value longLongValue]);
    }
}




@end
