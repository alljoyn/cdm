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

#import "DeviceViewController.h"
#import "../../cdm_controller/logic/DeviceManager.h"
#import "InterfaceListViewController.h"
#import "CDMDeviceListener.h"
#import "CDMController.h"
#import "alljoyn/BusAttachment.h"
#import "CDMUtil.h"
#import "DeviceTableViewCell.h"
#import "alljoyn/cdm/controller/CdmController.h"
#import "ECDHEKeyXListener.h"


static NSString * const DEVICE_TABLE_VIEW_CELL = @"DeviceTableViewCell";


@interface DeviceViewController ()

@property ajn::BusAttachment *bus;
@property ajn::services::CDMDeviceListener *deviceListener;
@property ajn::services::CdmController *cdmController;
@property ECDHEKeyXListener *authListener;

@end


@implementation DeviceViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = @"Devices";
    
    self.selectedDevice = nil;
    
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    [self.tableView registerClass:[DeviceTableViewCell class] forCellReuseIdentifier:DEVICE_TABLE_VIEW_CELL];
    
    [self.tableView setSeparatorInset:UIEdgeInsetsZero];
    
    _bus = new ajn::BusAttachment("CDM iOS Controller", true);
    
    QStatus status;
    
    status = _bus->Start();
    if(status != ER_OK) {
        NSLog(@"Failed to start bus");
        delete _bus;
        return;
    }
    
    status = _bus->Connect();
    if(status != ER_OK) {
        NSLog(@"Failed to conncet to bus");
        delete _bus;
        return;
    }
    
    _deviceListener = new ajn::services::CDMDeviceListener(self);
    _cdmController = new ajn::services::CdmController(*_bus, _deviceListener);
    _deviceListener->SetController(_cdmController);
    
    _authListener = new ECDHEKeyXListener();
    status = _cdmController->EnablePeerSecurity(ECDHE_KEYX, _authListener, "Library/.alljoyn_keystore/c_ecdhe.ks", true);
    if(status != ER_OK) {
        NSLog(@"EnablePeerSecurity failed");
    }
    
    status = _cdmController->Start();
    if(status != ER_OK) {
        NSLog(@"Failed to start the CdmController");
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)didReceiveStatusUpdateMessage:(NSString *)message
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"DeviceViewController: %@", message);
        [self.tableView reloadData];
    });
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [[[DeviceManager sharedInstance] devices] count];
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    DeviceTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:DEVICE_TABLE_VIEW_CELL];
    
    Device *device = [[[DeviceManager sharedInstance] getAllDevices] objectAtIndex:indexPath.row];
    
    NSString *imgLoc = [self imageForDeviceType:(ajn::services::DeviceType)device.type];
    if(imgLoc){
        NSString *imageName = [self imageForDeviceType:(ajn::services::DeviceType)device.type];
        UIImage *deviceImage = [[UIImage imageNamed:imageName] imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
        cell.logoView.image = deviceImage;
    }
    
    cell.descriptionView.text = device.name;
    
    return cell;
}

-(CGFloat) tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return DEVICE_CELL_HEIGHT;
}

-(void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    Device *device = [[DeviceManager sharedInstance] getAllDevices][indexPath.row];
    NSLog(@"Selected device: %@", device.name);
    UINavigationController *navController = [CDMUtil getNavigationController];
    self.selectedDevice = device;
    InterfaceListViewController *interfaceListViewController = [[InterfaceListViewController alloc] initWithDevice:device andController:_cdmController];
    [navController pushViewController:interfaceListViewController animated:YES];
}

-(NSString *)imageForDeviceType:(ajn::services::DeviceType)deviceType
{
    switch(deviceType) {
        case ajn::services::REFRIGERATOR:
            return @"icon_refrigerator.png";
        case ajn::services::FREEZER:
            return @"icon_freezer.png";
        case ajn::services::AIR_CONDITIONER:
            return @"icon_air_conditioner.png";
        case ajn::services::DISH_WASHER:
            return @"icon_dish_washer";
        case ajn::services::OVEN:
            return @"icon_oven.png";
        case ajn::services::COOKTOP:
            return @"icon_cooktop.png";
        case ajn::services::TELEVISION:
            return @"icon_tv.png";
        case ajn::services::SET_TOP_BOX:
            return @"icon_set_top_box.png";
        default :
            return @"alljoyn_logo.png";
    }
}

- (void)terminate
{
    QStatus status = _cdmController->Stop();
    if(status != ER_OK) {
        NSLog(@"Failed to stop the CdmController");
    }
    delete _cdmController;
    delete _deviceListener;
    delete _authListener;
}

@end
