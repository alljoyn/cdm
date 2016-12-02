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

#import <Foundation/Foundation.h>
#import "CDMUtil.h"
#import "FanSpeedLevelViewController.h"
#import "FanSpeedLevelListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/FanSpeedLevelIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 3;
static NSInteger NUM_METHODS = 0;

@interface FanSpeedLevelViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property FanSpeedLevelListener *listener;
@property std::shared_ptr<ajn::services::FanSpeedLevelIntfController> fanSpeedLevelIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation FanSpeedLevelViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"fan speed level";
        _cdmController = cdmController;
        _device = device;

        _listener = new FanSpeedLevelListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::FAN_SPEED_LEVEL_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _fanSpeedLevelIntfController = std::static_pointer_cast<ajn::services::FanSpeedLevelIntfController>(_cdmInterface);

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
    } 
    return 0;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    QStatus status;
    
    if (indexPath.section == SECTION_PROPERTY) {
        if(indexPath.row == 0) {
            _fanSpeedLevelCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _fanSpeedLevelCell.label.text = @"FanSpeedLevel";
            _fanSpeedLevelCell.delegate = self;

            status = _fanSpeedLevelIntfController->GetFanSpeedLevel();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetFanSpeedLevel");
            }

            return _fanSpeedLevelCell;
        }
        if(indexPath.row == 1) {
            _maxFanSpeedLevelCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _maxFanSpeedLevelCell.label.text = @"MaxFanSpeedLevel";

            status = _fanSpeedLevelIntfController->GetMaxFanSpeedLevel();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMaxFanSpeedLevel");
            }

            return _maxFanSpeedLevelCell;
        }
        if(indexPath.row == 2) {
            _autoModeCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _autoModeCell.label.text = @"AutoMode";
            _autoModeCell.delegate = self;

            status = _fanSpeedLevelIntfController->GetAutoMode();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetAutoMode");
            }

            return _autoModeCell;
        }
    }     
    return nil;
}

-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    if([property isEqualToString:@"FanSpeedLevel"]){
        _fanSpeedLevelIntfController->SetFanSpeedLevel((uint8_t)[value longLongValue]);
    }
    if([property isEqualToString:@"AutoMode"]){
        _fanSpeedLevelIntfController->SetAutoMode((FanSpeedLevelListener::AutoMode)[value longLongValue]);
    }
}




@end