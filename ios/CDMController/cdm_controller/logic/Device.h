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

#ifndef Device_h
#define Device_h

#import <Foundation/Foundation.h>
#import "CdmConfig.h"
#import "DeviceInfo.h"

@interface Device : NSObject

@property (nonatomic, strong) NSMutableArray *interfaces;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSUUID *appID;
@property (nonatomic, strong) NSString *objPath;
@property NSUInteger type;
@property (nonatomic, strong) NSString *busName;
@property ajn::services::DeviceInfoPtr deviceInfo;

-(id)initWithName:(NSString *)name withAppID:(NSUUID *)appID withObjPath:(NSString *)objPath withInterfaces:(NSMutableArray *)interfaces;

@end

#endif /* Device_h */