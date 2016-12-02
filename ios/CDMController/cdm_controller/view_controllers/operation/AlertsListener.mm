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

#import "AlertsListener.h"
#import "AlertsViewController.h"
#import "CDMUtil.h"

AlertsListener::AlertsListener(AlertsViewController *viewController):viewController(viewController)
{
    
}

AlertsListener::~AlertsListener()
{
    
}

void AlertsListener::UpdateAlerts(const std::vector<AlertRecord>& value)
{
    NSString *valueArrayAsString = @"";
    std::vector<AlertRecord>::const_iterator it = value.begin();
    while(it != value.end()) {
        valueArrayAsString = [valueArrayAsString stringByAppendingString:[NSString stringWithFormat:@"%u:%hu:%@\n", it->severity, it->alertCode, [CDMUtil boolToNSString:it->needAcknowledgement]]];
        ++it;
    }
    NSLog(@"Got Alerts: %@", valueArrayAsString);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.alertsCell.value.text = [NSString stringWithFormat:@"%@", valueArrayAsString];
    });
}

void AlertsListener::OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const std::vector<AlertRecord>& value, void* context)
{
    UpdateAlerts(value);
}

void AlertsListener::OnAlertsChanged(const qcc::String& objectPath, const std::vector<AlertRecord>& value)
{
    UpdateAlerts(value);
}


void AlertsListener::OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const std::vector<AlertCodesDescriptor>& description, void* context, const char* errorName, const char* errorMessage)
{
    if(status == ER_OK) {
        NSLog(@"GetAlertCodesDescription succeeded");
        NSString *builtArgResponseStr = @"";
        std::vector<AlertCodesDescriptor>::const_iterator it;
        for(it = description.begin(); it != description.end(); ++it) {
            NSString *line = [NSString stringWithFormat:@"Alert Code:%u, Description:%s", it->alertCode, it->description.c_str()];
            builtArgResponseStr = [builtArgResponseStr stringByAppendingString:line];
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            viewController.getAlertCodesDescriptionOutputCell.output.text = builtArgResponseStr;
        });
    } else {
        NSLog(@"GetChannelList failed");
    }
}

void AlertsListener::OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"AcknowledgeAlert succeeded");
    } else {
        NSLog(@"AcknowledgeAlert failed");
    }
}

void AlertsListener::OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"AcknowledgeAllAlerts succeeded");
    } else {
        NSLog(@"AcknowledgeAllAlerts failed");
    }
}

