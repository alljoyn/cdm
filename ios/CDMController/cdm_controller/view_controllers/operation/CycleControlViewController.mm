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
#import "CycleControlViewController.h"
#import "CycleControlListener.h"
#import "alljoyn/cdm/common/CdmInterfaceTypes.h"
#import "alljoyn/cdm/common/CdmInterface.h"
#import "interfaces/controller/operation/CycleControlIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 3;
static NSInteger NUM_PROPERTIES = 3;
static NSInteger NUM_METHODS = 1;

@interface CycleControlViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property std::shared_ptr<CycleControlListener> listener;
@property std::shared_ptr<ajn::services::CycleControlIntfController> cycleControlIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation CycleControlViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"cycle control";
        _cdmController = cdmController;
        _device = device;

        _listener = std::shared_ptr<CycleControlListener>(new CycleControlListener(self));

        _cdmInterface = _cdmController->CreateInterface(ajn::services::CdmInterface::GetInterfaceName(ajn::services::CYCLE_CONTROL_INTERFACE),
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        _listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _cycleControlIntfController = std::static_pointer_cast<ajn::services::CycleControlIntfController>(_cdmInterface);

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
            _operationalStateCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _operationalStateCell.label.text = @"OperationalState";

            status = _cycleControlIntfController->GetOperationalState();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetOperationalState");
            }

            return _operationalStateCell;
        }
        if(indexPath.row == 1) {
            _supportedOperationalStatesCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _supportedOperationalStatesCell.label.text = @"SupportedOperationalStates";

            status = _cycleControlIntfController->GetSupportedOperationalStates();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedOperationalStates");
            }

            return _supportedOperationalStatesCell;
        }
        if(indexPath.row == 2) {
            _supportedOperationalCommandsCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _supportedOperationalCommandsCell.label.text = @"SupportedOperationalCommands";

            status = _cycleControlIntfController->GetSupportedOperationalCommands();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedOperationalCommands");
            }

            return _supportedOperationalCommandsCell;
        }
    } else if (indexPath.section == SECTION_METHOD) {
        if(indexPath.row == 0) {
            _executeOperationalCommandCell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _executeOperationalCommandCell.label.text = @"ExecuteOperationalCommand";
            _executeOperationalCommandCell.delegate = self;
            return _executeOperationalCommandCell;
        }
    } else if (indexPath.section == SECTION_METHOD_OUTPUT) {
        if(indexPath.row == 0) {
            _executeOperationalCommandOutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _executeOperationalCommandOutputCell.output.text = @"";
            return _executeOperationalCommandOutputCell;
        }
    } 
    
    return nil;
}


-(void) executeMethod:(NSString *)methodName
{
    if([methodName isEqualToString:@"ExecuteOperationalCommand"]){
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
                                                              CycleControlInterface::OperationalCommands commandCommand = (CycleControlInterface::OperationalCommands)[alertController.textFields[0].text longLongValue];
                                                              _cycleControlIntfController->ExecuteOperationalCommand(commandCommand);
                                                          }]];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"command";
            textField.text = @"";
        }];

        [self presentViewController:alertController animated:YES completion:nil];
    }

}



@end
