////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#import "InterfaceListViewController.h"
#import "Device.h"
#import "CDMUtil.h"
#import "InterfaceTableViewCell.h"

#import "CurrentAirQualityLevelViewController.h"
#import "CurrentHumidityViewController.h"
#import "CurrentTemperatureViewController.h"
#import "TargetHumidityViewController.h"
#import "TargetTemperatureLevelViewController.h"
#import "TargetTemperatureViewController.h"
#import "WaterLevelViewController.h"
#import "WindDirectionViewController.h"
#import "CurrentAirQualityViewController.h"

#import "LanguageDisplayListener.h"
#import "TemperatureDisplayListener.h"
#import "TimeDisplayListener.h"

#import "AirRecirculationModeViewController.h"
#import "AlertsViewController.h"
#import "AudioVideoInputViewController.h"
#import "AudioVolumeViewController.h"
#import "BatteryStatusViewController.h"
#import "ChannelViewController.h"
#import "ClimateControlModeViewController.h"
#import "ClosedStatusViewController.h"
#import "CurrentPowerViewController.h"
#import "CycleControlViewController.h"
#import "DishWashingCyclePhaseViewController.h"
#import "EnergyUsageViewController.h"
#import "FanSpeedLevelViewController.h"
#import "FilterStatusViewController.h"
#import "HeatingZoneViewController.h"
#import "HvacFanModeViewController.h"
#import "LaundryCyclePhaseViewController.h"
#import "MoistureOutputLevelViewController.h"
#import "OffControlViewController.h"
#import "OnControlViewController.h"
#import "OnOffStatusViewController.h"
#import "OvenCyclePhaseViewController.h"
#import "PlugInUnitsViewController.h"
#import "RapidModeViewController.h"
#import "RapidModeTimedViewController.h"
#import "RemoteControllabilityViewController.h"
#import "RepeatModeViewController.h"
#import "ResourceSavingViewController.h"
#import "RobotCleaningCyclePhaseViewController.h"
#import "SoilLevelViewController.h"
#import "SpinSpeedLevelViewController.h"
#import "TimerViewController.h"

#import "BrightnessViewController.h"
#import "ColorViewController.h"
#import "ColorTemperatureViewController.h"
#import "LockControlViewController.h"
#import "LockedStatusViewController.h"
#import "TriggerSensorViewController.h"
#import "UnlockControlViewController.h"


static NSString * const INTERFACE_TABLE_VIEW_CELL = @"InterfaceTableViewCell";
static NSString * const DEVICE_DISPLAY_CELL = @"DeviceDisplayTableViewCell";
static NSUInteger DEVICE_DISPLAY_CELL_NUM = 1;
static NSUInteger DEVICE_DISPLAY_CELL_INDEX = 0;
static NSString * const VIEW_TITLE = @"Interfaces";

@interface InterfaceListViewController ()
    @property(nonatomic, strong) Device *device;
    @property ajn::services::CdmController *cdmController;
@end

@implementation InterfaceListViewController

- (instancetype) initWithDevice:(Device *)device
{
    self = [self init];
    if(self){
        _device = device;
    }
    return self;
}

- (instancetype) initWithDevice:(Device *)device andController:(ajn::services::CdmController *)cdmController
{
    self = [self initWithDevice:device];
    if(self){
        _cdmController = cdmController;
    }
    return self;
}

- (void)viewDidLoad
{
    NSLog(@"num of device interfaces: %lu", (unsigned long)[self.device.interfaces count]);
    
    [super viewDidLoad];
    
    self.title = VIEW_TITLE;
    
    CGRect tableViewFrame = self.view.bounds;
    self.tableView = [[UITableView alloc]initWithFrame:tableViewFrame style:UITableViewStylePlain];
    
    [self.tableView registerClass:[InterfaceTableViewCell class] forCellReuseIdentifier:INTERFACE_TABLE_VIEW_CELL];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:DEVICE_DISPLAY_CELL];
    
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    [self.tableView setSeparatorInset:UIEdgeInsetsZero];
    
    [self.view addSubview:self.tableView];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.device.interfaces count] + DEVICE_DISPLAY_CELL_NUM;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(indexPath.row == DEVICE_DISPLAY_CELL_INDEX) {
        UITableViewCell *cell;
        
        cell = [tableView dequeueReusableCellWithIdentifier:DEVICE_DISPLAY_CELL];
        cell.textLabel.text = _device.name;
        cell.userInteractionEnabled = false;
        
        [CDMUtil removeCellInset:cell];
        
        return cell;
    } else {
        InterfaceTableViewCell *cell;
        
        cell = [tableView dequeueReusableCellWithIdentifier:INTERFACE_TABLE_VIEW_CELL];
        
        UIImage *alljoynLogo = [UIImage imageNamed:@"alljoyn_logo.png"];
        cell.logoView.image = alljoynLogo;
        
        NSArray *splitInterface = [self.device.interfaces[indexPath.row - DEVICE_DISPLAY_CELL_NUM] componentsSeparatedByString:@"."];
        cell.descriptionView.text = splitInterface[[splitInterface count] - 1];
        
        return cell;
    }
}

-(CGFloat) tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return INTERFACE_CELL_HEIGHT;
}

-(void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(indexPath.row != DEVICE_DISPLAY_CELL_INDEX) {
        NSString *interfaceName = self.device.interfaces[indexPath.row - DEVICE_DISPLAY_CELL_NUM];
        
        NSLog(@"Selected interface: %@", interfaceName);
        
        UINavigationController *navController = [CDMUtil getNavigationController];
        
        UIViewController *viewController;
        
        NSArray *splitString = [interfaceName componentsSeparatedByString:@"."];
        NSString *simpleInterfaceName = splitString[[splitString count] - 1];
        
        Class viewControllerClass = NSClassFromString([NSString stringWithFormat:@"%@ViewController", simpleInterfaceName]);
        if(viewControllerClass) {
            viewController = [[viewControllerClass alloc] initWithDevice:_device andController:_cdmController];
        }
        
        if(viewController){
            [navController pushViewController:viewController animated:YES];
        } else {
            UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Error"
                                                                                     message:@"Unable to open interface"
                                                                              preferredStyle:UIAlertControllerStyleAlert];
            [alertController addAction:[UIAlertAction actionWithTitle:@"Ok"
                                                                style:UIAlertActionStyleDefault
                                                              handler:nil]];
            [self presentViewController:alertController animated:YES completion:nil];
        }
    }
}

@end