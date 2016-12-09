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
#import "ChannelViewController.h"
#import "ChannelListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/ChannelIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 3;
static NSInteger NUM_PROPERTIES = 2;
static NSInteger NUM_METHODS = 1;

@interface ChannelViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property ChannelListener *listener;
@property std::shared_ptr<ajn::services::ChannelIntfController> channelIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation ChannelViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"channel";
        _cdmController = cdmController;
        _device = device;

        _listener = new ChannelListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::CHANNEL_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _channelIntfController = std::static_pointer_cast<ajn::services::ChannelIntfController>(_cdmInterface);

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
    } else if (section == SECTION_METHOD) {
        return NUM_METHODS;
    } else if (section == SECTION_METHOD_OUTPUT) {
        return NUM_METHODS;
    } 

    return 0;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QStatus status;
    
    if (indexPath.section == SECTION_PROPERTY) {
        if(indexPath.row == 0) {
            _channelIdCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _channelIdCell.label.text = @"ChannelId";
            _channelIdCell.delegate = self;

            status = _channelIntfController->GetChannelId();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetChannelId");
            }

            return _channelIdCell;
        }
        if(indexPath.row == 1) {
            _totalNumberOfChannelsCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _totalNumberOfChannelsCell.label.text = @"TotalNumberOfChannels";

            status = _channelIntfController->GetTotalNumberOfChannels();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTotalNumberOfChannels");
            }

            return _totalNumberOfChannelsCell;
        }
    } else if (indexPath.section == SECTION_METHOD) {
        if(indexPath.row == 0) {
            _getChannelListCell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _getChannelListCell.label.text = @"GetChannelList";
            _getChannelListCell.delegate = self;
            return _getChannelListCell;
        }
    } else if (indexPath.section == SECTION_METHOD_OUTPUT) {
        if(indexPath.row == 0) {
            _getChannelListOutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _getChannelListOutputCell.output.text = @"";
            return _getChannelListOutputCell;
        }
    } 
    
    return nil;
}

-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    if([property isEqualToString:@"ChannelId"]){
        _channelIntfController->SetChannelId(qcc::String([value cStringUsingEncoding:NSUTF8StringEncoding]));
    }
}

-(void) executeMethod:(NSString *)methodName
{
    if([methodName isEqualToString:@"GetChannelList"]){
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
                                                              uint16_t startingRecordCommand = (uint16_t)[alertController.textFields[0].text longLongValue];
                                                              uint16_t numRecordsCommand = (uint16_t)[alertController.textFields[1].text longLongValue];
                                                              _channelIntfController->GetChannelList(startingRecordCommand,numRecordsCommand);
                                                          }]];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"startingRecord";
            textField.text = @"";
        }];
        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"numRecords";
            textField.text = @"";
        }];

        [self presentViewController:alertController animated:YES completion:nil];
    }

}



@end