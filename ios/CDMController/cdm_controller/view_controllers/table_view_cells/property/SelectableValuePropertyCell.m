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
#import "SelectableValuePropertyCell.h"
#import "CDMUtil.h"


@interface SelectableValuePropertyCell()

@end


@implementation SelectableValuePropertyCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        self.label = [[UITextView alloc] initWithFrame:CGRectMake(10, 12.5, 150, 25)];
        self.label.text = @"";
        self.label.userInteractionEnabled = NO;
        
        self.value = [[UITextField alloc] initWithFrame:CGRectMake(self.frame.size.width-90, 12.5, 75, 25)];
        self.value.text = @"";
        self.value.textAlignment = NSTextAlignmentCenter;
        self.value.font = [UIFont systemFontOfSize:14];
        
        [self addBorders:self.value];
        
        [CDMUtil removeCellInset:self];
        
        [self addSubview:self.label];
        [self addSubview:self.value];
    }
    return self;
}

- (void)addBorders:(UITextField *)textField
{
    CALayer *bottomBorder = [CALayer layer];
    bottomBorder.frame = CGRectMake(0.0f, textField.frame.size.height - 1, textField.frame.size.width, 0.5f);
    bottomBorder.backgroundColor = [UIColor lightGrayColor].CGColor;
    [self.value.layer addSublayer:bottomBorder];
    
    CALayer *leftBorder = [CALayer layer];
    leftBorder.frame = CGRectMake(0.0f, 20.0f, 0.5f, textField.frame.size.height-20);
    leftBorder.backgroundColor = [UIColor lightGrayColor].CGColor;
    [self.value.layer addSublayer:leftBorder];
    
    CALayer *rightBorder = [CALayer layer];
    rightBorder.frame = CGRectMake(textField.frame.size.width-1, 20.0f, 0.5f, textField.frame.size.height-20);
    rightBorder.backgroundColor = [UIColor lightGrayColor].CGColor;
    [self.value.layer addSublayer:rightBorder];
}

@end