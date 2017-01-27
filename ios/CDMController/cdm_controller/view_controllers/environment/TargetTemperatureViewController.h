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

#ifndef TargetTemperatureViewController_h
#define TargetTemperatureViewController_h

#import "InterfaceViewController.h"
#import "alljoyn/cdm/controller/CdmController.h"
#import "Device.h"
#import "ReadOnlyValuePropertyCell.h"
#import "ReadWriteValuePropertyCell.h"

@interface TargetTemperatureViewController : InterfaceViewController <ReadWriteValueDelegate>
@property (nonatomic, strong) ReadWriteValuePropertyCell *targetValueCell;
@property (nonatomic, strong) ReadOnlyValuePropertyCell *minValueCell;
@property (nonatomic, strong) ReadOnlyValuePropertyCell *maxValueCell;
@property (nonatomic, strong) ReadOnlyValuePropertyCell *stepValueCell;

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController;

@end

#endif /* TargetTemperatureViewController_h */
