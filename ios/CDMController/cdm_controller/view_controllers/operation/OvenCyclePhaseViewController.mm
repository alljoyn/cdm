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
#import "OvenCyclePhaseViewController.h"
#import "OvenCyclePhaseListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/OvenCyclePhaseIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 3;
static NSInteger NUM_PROPERTIES = 1;
static NSInteger NUM_METHODS = 1;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    CYCLE_PHASE_PICKER_TAG = 1,
};

@interface OvenCyclePhaseViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property OvenCyclePhaseListener *listener;
@property std::shared_ptr<ajn::services::OvenCyclePhaseIntfController> ovenCyclePhaseIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *cyclePhasePicker;
@property std::vector<uint8_t> *selectorValuesForCyclePhase;

@end


@implementation OvenCyclePhaseViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"oven cycle phase";
        _cdmController = cdmController;
        _device = device;

        _listener = new OvenCyclePhaseListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::OVEN_CYCLE_PHASE_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _ovenCyclePhaseIntfController = std::static_pointer_cast<ajn::services::OvenCyclePhaseIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    _cyclePhasePicker = [[UIPickerView alloc] init];
    _cyclePhasePicker.delegate = self;
    _cyclePhasePicker.dataSource = self;
    _cyclePhasePicker.showsSelectionIndicator = YES;
    _cyclePhasePicker.hidden = NO;
    _cyclePhasePicker.tag = CYCLE_PHASE_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForCyclePhase) {
        delete _selectorValuesForCyclePhase;
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
            _cyclePhaseCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _cyclePhaseCell.label.text = @"CyclePhase";
            _cyclePhaseCell.value.inputView = _cyclePhasePicker;

            status = _ovenCyclePhaseIntfController->GetSupportedCyclePhases();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedCyclePhases");
            }                

            status = _ovenCyclePhaseIntfController->GetCyclePhase();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetCyclePhase");
            }

            return _cyclePhaseCell;
        }
    } else if (indexPath.section == SECTION_METHOD) {
        if(indexPath.row == 0) {
            _getVendorPhasesDescriptionCell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _getVendorPhasesDescriptionCell.label.text = @"GetVendorPhasesDescription";
            _getVendorPhasesDescriptionCell.delegate = self;
            return _getVendorPhasesDescriptionCell;
        }
    } else if (indexPath.section == SECTION_METHOD_OUTPUT) {
        if(indexPath.row == 0) {
            _getVendorPhasesDescriptionOutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _getVendorPhasesDescriptionOutputCell.output.text = @"";
            return _getVendorPhasesDescriptionOutputCell;
        }
    } 
    
    return nil;
}


-(void) executeMethod:(NSString *)methodName
{
    if([methodName isEqualToString:@"GetVendorPhasesDescription"]){
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
                                                              qcc::String languageTagCommand = (qcc::String)[alertController.textFields[0].text cStringUsingEncoding:NSUTF8StringEncoding];
                                                              _ovenCyclePhaseIntfController->GetVendorPhasesDescription(languageTagCommand);
                                                          }]];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = @"languageTag";
            textField.text = @"";
        }];

        [self presentViewController:alertController animated:YES completion:nil];
    }

}

- (void) setSupportedCyclePhases:(const std::vector<uint8_t>&)supportedCyclePhases
{
    if(self.self.selectorValuesForCyclePhase) {
        delete _selectorValuesForCyclePhase;
    }

    self.selectorValuesForCyclePhase = new std::vector<uint8_t>(supportedCyclePhases);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case CYCLE_PHASE_PICKER_TAG:
            return (NSInteger)self.selectorValuesForCyclePhase->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case CYCLE_PHASE_PICKER_TAG:
        {
            uint8_t cyclePhase = self.selectorValuesForCyclePhase->at(row);
            return [NSString stringWithFormat:@"%u", cyclePhase];
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case CYCLE_PHASE_PICKER_TAG:
        {
//            uint8_t cyclePhase = self.selectorValuesForCyclePhase->at(row);
//            _ovenCyclePhaseIntfController->SetCyclePhase(cyclePhase);
            [self.cyclePhaseCell.value resignFirstResponder];
            break;
        }
        default:
            break;
    }    
}

@end