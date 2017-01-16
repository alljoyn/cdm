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
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/CycleControlIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 3;
static NSInteger NUM_PROPERTIES = 2;
static NSInteger NUM_METHODS = 1;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    OPERATIONAL_STATE_PICKER_TAG = 1,
};

@interface CycleControlViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property CycleControlListener *listener;
@property std::shared_ptr<ajn::services::CycleControlIntfController> cycleControlIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *operationalStatePicker;
@property std::vector<CycleControlListener::OperationalState> *selectorValuesForOperationalState;

@end


@implementation CycleControlViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"cycle control";
        _cdmController = cdmController;
        _device = device;

        _listener = new CycleControlListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::CYCLE_CONTROL_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
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

    _operationalStatePicker = [[UIPickerView alloc] init];
    _operationalStatePicker.delegate = self;
    _operationalStatePicker.dataSource = self;
    _operationalStatePicker.showsSelectionIndicator = YES;
    _operationalStatePicker.hidden = NO;
    _operationalStatePicker.tag = OPERATIONAL_STATE_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForOperationalState) {
        delete _selectorValuesForOperationalState;
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
            _operationalStateCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _operationalStateCell.label.text = @"OperationalState";
            _operationalStateCell.value.inputView = _operationalStatePicker;

            status = _cycleControlIntfController->GetSupportedOperationalStates();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedOperationalStates");
            }                

            status = _cycleControlIntfController->GetOperationalState();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetOperationalState");
            }

            return _operationalStateCell;
        }
        if(indexPath.row == 1) {
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
                                                              CycleControlListener::OperationalCommands commandCommand = (CycleControlListener::OperationalCommands)[alertController.textFields[0].text longLongValue];
                                                              _cycleControlIntfController->ExecuteOperationalCommand(commandCommand);
                                                          }]];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"command";
            textField.text = @"";
        }];

        [self presentViewController:alertController animated:YES completion:nil];
    }

}

- (void) setSupportedOperationalStates:(const std::vector<CycleControlListener::OperationalState>&)supportedOperationalStates
{
    if(self.self.selectorValuesForOperationalState) {
        delete _selectorValuesForOperationalState;
    }

    self.selectorValuesForOperationalState = new std::vector<CycleControlListener::OperationalState>(supportedOperationalStates);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case OPERATIONAL_STATE_PICKER_TAG:
            return (NSInteger)self.selectorValuesForOperationalState->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case OPERATIONAL_STATE_PICKER_TAG:
        {
            CycleControlListener::OperationalState operationalState = self.selectorValuesForOperationalState->at(row);
            return [NSString stringWithFormat:@"%u", operationalState];
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case OPERATIONAL_STATE_PICKER_TAG:
        {
//            CycleControlListener::OperationalState operationalState = self.selectorValuesForOperationalState->at(row);
//            _cycleControlIntfController->SetOperationalState(operationalState);
            [self.operationalStateCell.value resignFirstResponder];
            break;
        }
        default:
            break;
    }    
}

@end