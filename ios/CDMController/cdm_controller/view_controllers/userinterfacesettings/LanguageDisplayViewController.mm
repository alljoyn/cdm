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
#import "LanguageDisplayViewController.h"
#import "LanguageDisplayListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 1;
static NSInteger NUM_METHODS = 0;

typedef NS_ENUM(NSInteger, PICKER_TAG) {
    DISPLAY_LANGUAGE_PICKER_TAG = 1,
};

@interface LanguageDisplayViewController() <UIPickerViewDelegate, UIPickerViewDataSource>
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property LanguageDisplayListener *listener;
@property std::shared_ptr<ajn::services::LanguageDisplayIntfController> languageDisplayIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;

@property (nonatomic, strong) UIPickerView *displayLanguagePicker;
@property std::vector<qcc::String> *selectorValuesForDisplayLanguage;

@end


@implementation LanguageDisplayViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"language display";
        _cdmController = cdmController;
        _device = device;

        _listener = new LanguageDisplayListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::LANGUAGE_DISPLAY_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _languageDisplayIntfController = std::static_pointer_cast<ajn::services::LanguageDisplayIntfController>(_cdmInterface);

    }
    return self;
}

- (void) viewDidLoad
{
    [super viewDidLoad];

    _displayLanguagePicker = [[UIPickerView alloc] init];
    _displayLanguagePicker.delegate = self;
    _displayLanguagePicker.dataSource = self;
    _displayLanguagePicker.showsSelectionIndicator = YES;
    _displayLanguagePicker.hidden = NO;
    _displayLanguagePicker.tag = DISPLAY_LANGUAGE_PICKER_TAG;
}

- (void) viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    if (_selectorValuesForDisplayLanguage) {
        delete _selectorValuesForDisplayLanguage;
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
            _displayLanguageCell  = [tableView dequeueReusableCellWithIdentifier:SELECTABLE_TABLE_VIEW_CELL];
            _displayLanguageCell.label.text = @"DisplayLanguage";
            _displayLanguageCell.value.inputView = _displayLanguagePicker;

            status = _languageDisplayIntfController->GetSupportedDisplayLanguages();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetSupportedDisplayLanguages");
            }                

            status = _languageDisplayIntfController->GetDisplayLanguage();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetDisplayLanguage");
            }

            return _displayLanguageCell;
        }
    }     
    return nil;
}



- (void) setSupportedDisplayLanguages:(const std::vector<qcc::String>&)supportedDisplayLanguages
{
    if(self.self.selectorValuesForDisplayLanguage) {
        delete _selectorValuesForDisplayLanguage;
    }

    self.selectorValuesForDisplayLanguage = new std::vector<qcc::String>(supportedDisplayLanguages);
}

#pragma mark UIPickerViewDataSource

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{   
    switch(pickerView.tag) {
        case DISPLAY_LANGUAGE_PICKER_TAG:
            return (NSInteger)self.selectorValuesForDisplayLanguage->size();
        default:
            return 0;
    }
}

#pragma mark UIPickerViewDelegate

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
    switch(pickerView.tag) {
        case DISPLAY_LANGUAGE_PICKER_TAG:
        {
            qcc::String displayLanguage = self.selectorValuesForDisplayLanguage->at(row);
            return [NSString stringWithFormat:@"%s", displayLanguage.c_str()];
        }
        default:
            return nil;
    }
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
   switch(pickerView.tag) {
        case DISPLAY_LANGUAGE_PICKER_TAG:
        {
            qcc::String displayLanguage = self.selectorValuesForDisplayLanguage->at(row);
            _languageDisplayIntfController->SetDisplayLanguage(displayLanguage);
            [self.displayLanguageCell.value resignFirstResponder];
            break;
        }
        default:
            break;
    }    
}

@end