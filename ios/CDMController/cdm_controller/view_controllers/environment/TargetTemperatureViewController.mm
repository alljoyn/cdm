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
#import "TargetTemperatureViewController.h"
#import "TargetTemperatureListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/environment/TargetTemperatureIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 4;
static NSInteger NUM_METHODS = 0;

@interface TargetTemperatureViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property TargetTemperatureListener *listener;
@property std::shared_ptr<ajn::services::TargetTemperatureIntfController> targetTemperatureIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation TargetTemperatureViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"target temperature";
        _cdmController = cdmController;
        _device = device;

        _listener = new TargetTemperatureListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::TARGET_TEMPERATURE_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _targetTemperatureIntfController = std::static_pointer_cast<ajn::services::TargetTemperatureIntfController>(_cdmInterface);

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
            _targetValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_WRITE_TABLE_VIEW_CELL];
            _targetValueCell.label.text = @"TargetValue";
            _targetValueCell.delegate = self;

            status = _targetTemperatureIntfController->GetTargetValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetTargetValue");
            }

            return _targetValueCell;
        }
        if(indexPath.row == 1) {
            _minValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _minValueCell.label.text = @"MinValue";

            status = _targetTemperatureIntfController->GetMinValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMinValue");
            }

            return _minValueCell;
        }
        if(indexPath.row == 2) {
            _maxValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _maxValueCell.label.text = @"MaxValue";

            status = _targetTemperatureIntfController->GetMaxValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMaxValue");
            }

            return _maxValueCell;
        }
        if(indexPath.row == 3) {
            _stepValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _stepValueCell.label.text = @"StepValue";

            status = _targetTemperatureIntfController->GetStepValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetStepValue");
            }

            return _stepValueCell;
        }
    }     
    return nil;
}

-(void) updateValue:(NSString *)value forProperty:(NSString *)property
{
    if([property isEqualToString:@"TargetValue"]){
        _targetTemperatureIntfController->SetTargetValue((double)[value longLongValue]);
    }
}




@end