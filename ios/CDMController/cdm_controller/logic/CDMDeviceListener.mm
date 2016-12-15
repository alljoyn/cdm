//
//  CDMDeviceListener.cpp
//  CDMController
//
//  Created by Jayden Ivanovic on 26/08/2016.
//  Copyright (c) Connectivity Foundation and AllJoyn Open Source Project Contributors and others.
//

#include "CDMDeviceListener.h"
#include "DeviceTypeDescription.h"
#import "Device.h"
#import "DeviceManager.h"
#import "CDMUtil.h"

namespace ajn{
namespace services{
    
CDMDeviceListener::CDMDeviceListener()
{
    
}
    
CDMDeviceListener::CDMDeviceListener(DeviceViewController *viewController):viewController(viewController)
{
        
}
 
CDMDeviceListener::~CDMDeviceListener()
{
    
}

void CDMDeviceListener::SetController(ajn::services::CdmController *controller)
{
    cdmController = controller;
}

    
void CDMDeviceListener::OnDeviceAdded(const char* busname, SessionPort port, const CdmAboutData& data,
                                      const AboutObjectDescription& description)
{
    NSLog(@"Device added called");
    
    DeviceTypeDescription *devTypeDesc = new DeviceTypeDescription();
    
    QStatus status;
    
    CdmAboutData &constlessData = const_cast<CdmAboutData&>(data);
    status = constlessData.GetDeviceTypeDescription(&devTypeDesc);
    
    if(status == ER_OK) {
        
        // Get DeviceName
        char *deviceName;
        status = constlessData.GetDeviceName(&deviceName);
        if(status != ER_OK){
            NSLog(@"Failed to get device name");
            return;
        }
        
        // Get AppId
        size_t appIDSize = 16;
        uint8_t *appID[appIDSize];
        status = constlessData.GetAppId(appID, &appIDSize);
        if(status != ER_OK){
            NSLog(@"Failed to get app id");
            return;
        }
        
        // Get Obj Path and Device Type
        const std::multimap<DeviceType, qcc::String> &descriptions = devTypeDesc->GetDescriptions();
        std::multimap<DeviceType, qcc::String>::const_iterator itr = descriptions.begin();
        std::multimap<DeviceType, qcc::String>::const_iterator end = descriptions.end();
        DeviceType type;
        qcc::String path;
        for (; itr != end; itr++) {
            type = itr->first;
            path = itr->second;
        }

        // Get Interfaces
        NSMutableArray *interfaceList = [[NSMutableArray alloc]init];
        size_t path_num = description.GetPaths(NULL, 0);
        const char** paths = new const char*[path_num];
        description.GetPaths(paths, path_num);
        
        for (size_t i = 0; i < path_num; ++i) {
            if (!strncmp(paths[i], "/About", strlen(paths[i]))) {
                continue;
            }
            size_t numInterfaces = description.GetInterfaces(paths[i], NULL, 0);
            const char** interfaces = new const char*[numInterfaces];
            description.GetInterfaces(paths[i], interfaces, numInterfaces);
            for (size_t j = 0; j < numInterfaces; ++j) {
                const char *interface = interfaces[j];
                [interfaceList addObject:[NSString stringWithCString:interface encoding:NSUTF8StringEncoding]];
            }
            delete[] interfaces;
        }
        delete[] paths;

        Device *announcedDevice = [[Device alloc] initWithName:[NSString stringWithCString:deviceName encoding:NSUTF8StringEncoding]
                                                     withAppID:[[NSUUID alloc] initWithUUIDBytes:*appID]
                                                   withObjPath:[NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding]
                                                withInterfaces:interfaceList];
        announcedDevice.type = type;
        announcedDevice.busName =[NSString stringWithCString:busname encoding:NSUTF8StringEncoding];
        [[DeviceManager sharedInstance] addDevice:announcedDevice];
        
        NSLog(@"DeviceManager devices count: %ld", (long)[[[DeviceManager sharedInstance] devices] count]);
        [viewController didReceiveStatusUpdateMessage:@"Device Added"];
        
        // Create session with device in order to determine when it drops from the network
        QStatus status = cdmController->JoinDevice(busname, port, data, const_cast<ajn::AboutObjectDescription&>(description));
        if(status != ER_OK) {
            NSLog(@"JoinDevice failed - %u", status);
        }
    }
}
    
void CDMDeviceListener::OnDeviceRemoved(const char* busname)
{
    NSLog(@"Device removed");
}
    
void CDMDeviceListener::OnDeviceSessionJoined(const DeviceInfoPtr& info)
{
    NSLog(@"Device session joined");
    NSString *busName = [NSString stringWithCString:info->GetBusName().c_str() encoding:NSUTF8StringEncoding];
    NSArray *devices = [[DeviceManager sharedInstance] getAllDevices];
    for (Device *device in devices) {
        if([device.busName compare:busName] == NSOrderedSame) {
            device.deviceInfo = info;
        }
    }
}
    
void CDMDeviceListener::OnDeviceSessionLost(SessionId sessionId)
{
    NSLog(@"Device session lost");
    [[DeviceManager sharedInstance] removeDeviceWithSessionId:sessionId];
    [viewController didReceiveStatusUpdateMessage:@"Device removed"];
    if(sessionId == viewController.selectedDevice.deviceInfo->GetSessionId()){
        viewController.selectedDevice = nil;
        dispatch_async(dispatch_get_main_queue(), ^{
            [[CDMUtil getNavigationController] popToViewController:viewController animated:YES];
        });
    }
}

}
}