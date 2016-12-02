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
#import "CurrentAirQualityViewController.h"
#import "CurrentAirQualityListener.h"
#import "alljoyn/cdm/interfaces/CdmInterfaceTypes.h"
#import "alljoyn/cdm/interfaces/CdmInterface.h"
#import "alljoyn/cdm/interfaces/environment/CurrentAirQualityIntfController.h"

static NSInteger NUM_MEMBER_CATEGORIES = 1;
static NSInteger NUM_PROPERTIES = 6;
static NSInteger NUM_METHODS = 0;

@interface CurrentAirQualityViewController() 
@property ajn::services::CdmController *cdmController;
@property (nonatomic, strong) Device* device;
@property CurrentAirQualityListener *listener;
@property std::shared_ptr<ajn::services::CurrentAirQualityIntfController> currentAirQualityIntfController;
@property std::shared_ptr<ajn::services::CdmInterface> cdmInterface;


@end


@implementation CurrentAirQualityViewController

- (instancetype)initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [super init];
    if (self) {
        self.title = @"current air quality";
        _cdmController = cdmController;
        _device = device;

        _listener = new CurrentAirQualityListener(self);

        _cdmInterface = _cdmController->CreateInterface(ajn::services::CURRENT_AIR_QUALITY_INTERFACE,
                                                        _device.deviceInfo->GetBusName(),
                                                        qcc::String([_device.objPath cStringUsingEncoding:NSUTF8StringEncoding]),
                                                        _device.deviceInfo->GetSessionId(),
                                                        *_listener);
        if (_cdmInterface == NULL) {
            return nil;
        }
        
        _currentAirQualityIntfController = std::static_pointer_cast<ajn::services::CurrentAirQualityIntfController>(_cdmInterface);

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
            _contaminantTypeCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _contaminantTypeCell.label.text = @"ContaminantType";

            status = _currentAirQualityIntfController->GetContaminantType();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetContaminantType");
            }

            return _contaminantTypeCell;
        }
        if(indexPath.row == 1) {
            _currentValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _currentValueCell.label.text = @"CurrentValue";

            status = _currentAirQualityIntfController->GetCurrentValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetCurrentValue");
            }

            return _currentValueCell;
        }
        if(indexPath.row == 2) {
            _minValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _minValueCell.label.text = @"MinValue";

            status = _currentAirQualityIntfController->GetMinValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMinValue");
            }

            return _minValueCell;
        }
        if(indexPath.row == 3) {
            _maxValueCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _maxValueCell.label.text = @"MaxValue";

            status = _currentAirQualityIntfController->GetMaxValue();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetMaxValue");
            }

            return _maxValueCell;
        }
        if(indexPath.row == 4) {
            _precisionCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _precisionCell.label.text = @"Precision";

            status = _currentAirQualityIntfController->GetPrecision();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetPrecision");
            }

            return _precisionCell;
        }
        if(indexPath.row == 5) {
            _updateMinTimeCell  = [tableView dequeueReusableCellWithIdentifier:READ_ONLY_TABLE_VIEW_CELL];
            _updateMinTimeCell.label.text = @"UpdateMinTime";

            status = _currentAirQualityIntfController->GetUpdateMinTime();
            if(status != ER_OK) {
                NSLog(@"Failed to get GetUpdateMinTime");
            }

            return _updateMinTimeCell;
        }
    }     
    return nil;
}





@end