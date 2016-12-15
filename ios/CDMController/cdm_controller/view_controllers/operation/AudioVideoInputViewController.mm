////////////////////////////////////////////////////////////////////////////////
// // Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#import "AudioVideoInputViewController.h"
#import "AudioVideoInputListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/AudioVideoInputIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 1;
static NSInteger NUM_METHODS = 0;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    INPUT_SOURCE_ID_PICKER_TAG = 1,
};

@interface AudioVideoInputViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property AudioVideoInputListener *listener;
@property std::shared_ptr<ajn::services::AudioVideoInputIntfController> audioVideoInputIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *inputSourceIdPicker;
@property AudioVideoInputListener::InputSources *selectorValuesForInputSourceId;

@end


@implementation AudioVideoInputViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"audio video input";
        _cdmController = cdmController;
        _device = device;

        _listener = new AudioVideoInputListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::AUDIO_VIDEO_INPUT_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _audioVideoInputIntfController = std::static_pointer_cast<ajn::services::AudioVideoInputIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    _inputSourceIdPicker = [[UIPickerView alloc] init];
    _inputSourceIdPicker.delegate = self;
    _inputSourceIdPicker.dataSource = self;
    _inputSourceIdPicker.showsSelectionIndicator = YES;
    _inputSourceIdPicker.hidden = NO;
    _inputSourceIdPicker.tag = INPUT_SOURCE_ID_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForInputSourceId) {
        delete _selectorValuesForInputSourceId;
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
            _inputSourceIdCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _inputSourceIdCell.label.text = @"InputSourceId";
            _inputSourceIdCell.value.inputView = _inputSourceIdPicker;

            status = _audioVideoInputIntfController->GetSupportedInputSources();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedInputSources");
            }                

            status = _audioVideoInputIntfController->GetInputSourceId();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetInputSourceId");
            }

            return _inputSourceIdCell;
        }
    }     
    return nil;
}

- (void) setSupportedInputSources:(const AudioVideoInputListener::InputSources&)supportedInputSources
{
    if(self.self.selectorValuesForInputSourceId) {
        delete _selectorValuesForInputSourceId;
    }

    self.selectorValuesForInputSourceId = new AudioVideoInputListener::InputSources(supportedInputSources);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case INPUT_SOURCE_ID_PICKER_TAG:
            return (NSInteger)self.selectorValuesForInputSourceId->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case INPUT_SOURCE_ID_PICKER_TAG:
        {
            AudioVideoInputListener::InputSources::iterator it;
            int index = 0;
            for(it = self.selectorValuesForInputSourceId->begin(); it != self.selectorValuesForInputSourceId->end(); ++it) {
                if (index == row) {
                    uint16_t inputSourceId = it->first;
                    return [NSString stringWithFormat:@"%hu", inputSourceId];
                }
                ++index;
            }
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case INPUT_SOURCE_ID_PICKER_TAG:
        {
            AudioVideoInputListener::InputSources::iterator it;
            int index = 0;
            for(it = self.selectorValuesForInputSourceId->begin(); it != self.selectorValuesForInputSourceId->end(); ++it) {
                if (index == row) {
                    uint16_t inputSourceId = it->first;
                    _audioVideoInputIntfController->SetInputSourceId(inputSourceId);
                    [self.inputSourceIdCell.value resignFirstResponder];
                    break;
                }
                ++index;
            }
        }
        default:
            break;
    }    
}

@end