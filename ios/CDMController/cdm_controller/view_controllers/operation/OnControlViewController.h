////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Permission to use, copy, modify, and/or distribute this software for any
//    purpose with or without fee is hereby granted, provided that the above
//    copyright notice and this permission notice appear in all copies.
//
//    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef OnControlViewController_h
#define OnControlViewController_h

#import "InterfaceViewController.h"
#import "alljoyn/cdm/CdmController.h"
#import "Device.h"
#import "ReadOnlyValuePropertyCell.h"
#import "MethodViewCell.h"
#import "MethodViewOutputCell.h"

@interface OnControlViewController : InterfaceViewController <MethodViewDelegate>
@property (nonatomic, strong) MethodViewCell *switchOnCell;
@property (nonatomic, strong) MethodViewOutputCell *switchOnOutputCell;

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController;

@end

#endif /* OnControlViewController_h */