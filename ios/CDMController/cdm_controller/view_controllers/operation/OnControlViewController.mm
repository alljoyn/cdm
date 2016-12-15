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
#import "OnControlViewController.h"
#import "OnControlListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/OnControlIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 3;
static NSInteger NUM_PROPERTIES = 0;
static NSInteger NUM_METHODS = 1;

@interface OnControlViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property OnControlListener *listener;
@property std::shared_ptr<ajn::services::OnControlIntfController> onControlIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation OnControlViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"on control";
        _cdmController = cdmController;
        _device = device;

        _listener = new OnControlListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::ON_CONTROL_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _onControlIntfController = std::static_pointer_cast<ajn::services::OnControlIntfController>(_cdmInterface);

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
    } else if (indexPath.section == SECTION_METHOD) {
        if(indexPath.row == 0) {
            _switchOnCell  = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_TABLE_VIEW_CELL];
            _switchOnCell.label.text = @"SwitchOn";
            _switchOnCell.delegate = self;
            return _switchOnCell;
        }
    } else if (indexPath.section == SECTION_METHOD_OUTPUT) {
        if(indexPath.row == 0) {
            _switchOnOutputCell = [tableView dequeueReusableCellWithIdentifier:METHOD_VIEW_OUTPUT_TABLE_VIEW_CELL];
            _switchOnOutputCell.output.text = @"";
            return _switchOnOutputCell;
        }
    } 
    
    return nil;
}


-(void) executeMethod:(NSString *)methodName
{
    if([methodName isEqualToString:@"SwitchOn"]){
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
                                                              _onControlIntfController->SwitchOn();
                                                          }]];


        [self presentViewController:alertController animated:YES completion:nil];
    }

}



@end