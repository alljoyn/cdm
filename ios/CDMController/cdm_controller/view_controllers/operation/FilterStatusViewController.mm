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
#import "FilterStatusViewController.h"
#import "FilterStatusListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/FilterStatusIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 7;
static NSInteger NUM_METHODS = 0;

@interface FilterStatusViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property FilterStatusListener *listener;
@property std::shared_ptr<ajn::services::FilterStatusIntfController> filterStatusIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation FilterStatusViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"filter status";
        _cdmController = cdmController;
        _device = device;

        _listener = new FilterStatusListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::FILTER_STATUS_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _filterStatusIntfController = std::static_pointer_cast<ajn::services::FilterStatusIntfController>(_cdmInterface);

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
            _expectedLifeInDaysCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _expectedLifeInDaysCell.label.text = @"ExpectedLifeInDays";

            status = _filterStatusIntfController->GetExpectedLifeInDays();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetExpectedLifeInDays");
            }

            return _expectedLifeInDaysCell;
        }
        if(indexPath.row == 1) {
            _isCleanableCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _isCleanableCell.label.text = @"IsCleanable";

            status = _filterStatusIntfController->GetIsCleanable();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetIsCleanable");
            }

            return _isCleanableCell;
        }
        if(indexPath.row == 2) {
            _orderPercentageCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _orderPercentageCell.label.text = @"OrderPercentage";

            status = _filterStatusIntfController->GetOrderPercentage();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetOrderPercentage");
            }

            return _orderPercentageCell;
        }
        if(indexPath.row == 3) {
            _manufacturerCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _manufacturerCell.label.text = @"Manufacturer";

            status = _filterStatusIntfController->GetManufacturer();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetManufacturer");
            }

            return _manufacturerCell;
        }
        if(indexPath.row == 4) {
            _partNumberCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _partNumberCell.label.text = @"PartNumber";

            status = _filterStatusIntfController->GetPartNumber();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetPartNumber");
            }

            return _partNumberCell;
        }
        if(indexPath.row == 5) {
            _urlCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _urlCell.label.text = @"Url";

            status = _filterStatusIntfController->GetUrl();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetUrl");
            }

            return _urlCell;
        }
        if(indexPath.row == 6) {
            _lifeRemainingCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _lifeRemainingCell.label.text = @"LifeRemaining";

            status = _filterStatusIntfController->GetLifeRemaining();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetLifeRemaining");
            }

            return _lifeRemainingCell;
        }
    }     
    return nil;
}





@end