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
#import "TimerViewController.h"
#import "TimerListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/TimerIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 3;
static NSInteger NUM_PROPERTIES = 6;
static NSInteger NUM_METHODS = 2;

@interface TimerViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property TimerListener *listener;
@property std::shared_ptr<ajn::services::TimerIntfController> timerIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation TimerViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"timer";
        _cdmController = cdmController;
        _device = device;

        _listener = new TimerListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::TIMER_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _timerIntfController = std::static_pointer_cast<ajn::services::TimerIntfController>(_cdmInterface);

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
            _referenceTimerCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _referenceTimerCell.label.text = @"ReferenceTimer";

            status = _timerIntfController->GetReferenceTimer();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetReferenceTimer");
            }

            return _referenceTimerCell;
        }
        if(indexPath.row == 1) {
            _targetTimeToStartCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _targetTimeToStartCell.label.text = @"TargetTimeToStart";

            status = _timerIntfController->GetTargetTimeToStart();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTargetTimeToStart");
            }

            return _targetTimeToStartCell;
        }
        if(indexPath.row == 2) {
            _targetTimeToStopCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _targetTimeToStopCell.label.text = @"TargetTimeToStop";

            status = _timerIntfController->GetTargetTimeToStop();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTargetTimeToStop");
            }

            return _targetTimeToStopCell;
        }
        if(indexPath.row == 3) {
            _estimatedTimeToEndCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _estimatedTimeToEndCell.label.text = @"EstimatedTimeToEnd";

            status = _timerIntfController->GetEstimatedTimeToEnd();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetEstimatedTimeToEnd");
            }

            return _estimatedTimeToEndCell;
        }
        if(indexPath.row == 4) {
            _runningTimeCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _runningTimeCell.label.text = @"RunningTime";

            status = _timerIntfController->GetRunningTime();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetRunningTime");
            }

            return _runningTimeCell;
        }
        if(indexPath.row == 5) {
            _targetDurationCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _targetDurationCell.label.text = @"TargetDuration";

            status = _timerIntfController->GetTargetDuration();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTargetDuration");
            }

            return _targetDurationCell;
        }
    } else if (indexPath.section == SECTION_METHOD) {
        if(indexPath.row == 0) {
            _setTargetTimeToStartCell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _setTargetTimeToStartCell.label.text = @"SetTargetTimeToStart";
            _setTargetTimeToStartCell.delegate = self;
            return _setTargetTimeToStartCell;
        }
        if(indexPath.row == 1) {
            _setTargetTimeToStopCell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _setTargetTimeToStopCell.label.text = @"SetTargetTimeToStop";
            _setTargetTimeToStopCell.delegate = self;
            return _setTargetTimeToStopCell;
        }
    } else if (indexPath.section == SECTION_METHOD_OUTPUT) {
        if(indexPath.row == 0) {
            _setTargetTimeToStartOutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _setTargetTimeToStartOutputCell.output.text = @"";
            return _setTargetTimeToStartOutputCell;
        }
        if(indexPath.row == 1) {
            _setTargetTimeToStopOutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _setTargetTimeToStopOutputCell.output.text = @"";
            return _setTargetTimeToStopOutputCell;
        }
    } 
    
    return nil;
}


-(void) executeMethod:(NSString *)methodName
{
    if([methodName isEqualToString:@"SetTargetTimeToStart"]){
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
                                                              int32_t targetTimeToStartCommand = (int32_t)[alertController.textFields[0].text longLongValue];
                                                              _timerIntfController->SetTargetTimeToStart(targetTimeToStartCommand);
                                                          }]];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"targetTimeToStart";
            textField.text = @"";
        }];

        [self presentViewController:alertController animated:YES completion:nil];
    }

    if([methodName isEqualToString:@"SetTargetTimeToStop"]){
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
                                                              int32_t targetTimeToStopCommand = (int32_t)[alertController.textFields[0].text longLongValue];
                                                              _timerIntfController->SetTargetTimeToStop(targetTimeToStopCommand);
                                                          }]];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"targetTimeToStop";
            textField.text = @"";
        }];

        [self presentViewController:alertController animated:YES completion:nil];
    }

}



@end