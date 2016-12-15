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
#import "MethodViewCell.h"
#import "CDMUtil.h"


@interface MethodViewCell()

@end


@implementation MethodViewCell

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Add some fake data for testing
        self.label = [[UITextView alloc] initWithFrame:CGRectMake(10, 12.5, 150, 25)];
        self.label.text = @"switchOn";
        
        self.invokeButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [self.invokeButton setTitle:@"invoke" forState:UIControlStateNormal];
        [self.invokeButton setFrame:CGRectMake(self.frame.size.width-75, 12.5, 50, 25)];
        [[self.invokeButton layer] setBorderWidth:1.0f];
        [[self.invokeButton layer] setBorderColor:[UIColor colorWithRed:0.02 green:0.49 blue:1 alpha:1].CGColor];
        [[self.invokeButton layer] setCornerRadius:10];
        [self.invokeButton setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
        [self.invokeButton addTarget:self action:@selector(buttonPressed) forControlEvents:UIControlEventTouchDown];
        
        [CDMUtil removeCellInset:self];
        
        [self addSubview:self.label];
        [self addSubview:self.invokeButton];
    }
    return self;
}

- (void)buttonPressed
{
    NSLog(@"Method %@ invoked", self.label.text);
    [self.delegate executeMethod:self.label.text];
}

@end