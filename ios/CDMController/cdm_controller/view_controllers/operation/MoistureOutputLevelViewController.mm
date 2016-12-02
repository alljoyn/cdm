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
#import "MoistureOutputLevelViewController.h"
#import "MoistureOutputLevelListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 3;
static NSInteger NUM_METHODS = 0;

@interface MoistureOutputLevelViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property MoistureOutputLevelListener *listener;
@property std::shared_ptr<ajn::services::MoistureOutputLevelIntfController> moistureOutputLevelIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation MoistureOutputLevelViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"moisture output level";
        _cdmController = cdmController;
        _device = device;

        _listener = new MoistureOutputLevelListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::MOISTURE_OUTPUT_LEVEL_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _moistureOutputLevelIntfController = std::static_pointer_cast<ajn::services::MoistureOutputLevelIntfController>(_cdmInterface);

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
            _moistureOutputLevelCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _moistureOutputLevelCell.label.text = @"MoistureOutputLevel";
            _moistureOutputLevelCell.delegate = self;

            status = _moistureOutputLevelIntfController->GetMoistureOutputLevel();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMoistureOutputLevel");
            }

            return _moistureOutputLevelCell;
        }
        if(indexPath.row == 1) {
            _maxMoistureOutputLevelCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _maxMoistureOutputLevelCell.label.text = @"MaxMoistureOutputLevel";

            status = _moistureOutputLevelIntfController->GetMaxMoistureOutputLevel();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMaxMoistureOutputLevel");
            }

            return _maxMoistureOutputLevelCell;
        }
        if(indexPath.row == 2) {
            _autoModeCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _autoModeCell.label.text = @"AutoMode";
            _autoModeCell.delegate = self;

            status = _moistureOutputLevelIntfController->GetAutoMode();
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
    if([property isEqualToString:@"MoistureOutputLevel"]){
        _moistureOutputLevelIntfController->SetMoistureOutputLevel((uint8_t)[value longLongValue]);
    }
    if([property isEqualToString:@"AutoMode"]){
        _moistureOutputLevelIntfController->SetAutoMode((MoistureOutputLevelListener::AutoMode)[value longLongValue]);
    }
}




@end