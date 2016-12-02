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

#import "TimerListener.h"
#import "TimerViewController.h"
#import "CDMUtil.h"

TimerListener::TimerListener(TimerViewController *viewController):viewController(viewController)
{
    
}

TimerListener::~TimerListener()
{
    
}

void TimerListener::UpdateReferenceTimer(const int32_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%d", value];
    NSLog(@"Got ReferenceTimer: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.referenceTimerCell.value.text = valueAsStr;
    });
}

void TimerListener::OnResponseGetReferenceTimer(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
{
    UpdateReferenceTimer(value);
}



void TimerListener::UpdateTargetTimeToStart(const int32_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%d", value];
    NSLog(@"Got TargetTimeToStart: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.targetTimeToStartCell.value.text = valueAsStr;
    });
}

void TimerListener::OnResponseGetTargetTimeToStart(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
{
    UpdateTargetTimeToStart(value);
}

void TimerListener::OnTargetTimeToStartChanged(const qcc::String& objectPath, const int32_t value)
{
    UpdateTargetTimeToStart(value);
}


void TimerListener::UpdateTargetTimeToStop(const int32_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%d", value];
    NSLog(@"Got TargetTimeToStop: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.targetTimeToStopCell.value.text = valueAsStr;
    });
}

void TimerListener::OnResponseGetTargetTimeToStop(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
{
    UpdateTargetTimeToStop(value);
}

void TimerListener::OnTargetTimeToStopChanged(const qcc::String& objectPath, const int32_t value)
{
    UpdateTargetTimeToStop(value);
}


void TimerListener::UpdateEstimatedTimeToEnd(const int32_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%d", value];
    NSLog(@"Got EstimatedTimeToEnd: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.estimatedTimeToEndCell.value.text = valueAsStr;
    });
}

void TimerListener::OnResponseGetEstimatedTimeToEnd(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
{
    UpdateEstimatedTimeToEnd(value);
}



void TimerListener::UpdateRunningTime(const int32_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%d", value];
    NSLog(@"Got RunningTime: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.runningTimeCell.value.text = valueAsStr;
    });
}

void TimerListener::OnResponseGetRunningTime(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
{
    UpdateRunningTime(value);
}



void TimerListener::UpdateTargetDuration(const int32_t value)
{
    NSString *valueAsStr = [NSString stringWithFormat:@"%d", value];
    NSLog(@"Got TargetDuration: %@", valueAsStr);
    dispatch_async(dispatch_get_main_queue(), ^{
        viewController.targetDurationCell.value.text = valueAsStr;
    });
}

void TimerListener::OnResponseGetTargetDuration(QStatus status, const qcc::String& objectPath, const int32_t value, void* context)
{
    UpdateTargetDuration(value);
}

void TimerListener::OnTargetDurationChanged(const qcc::String& objectPath, const int32_t value)
{
    UpdateTargetDuration(value);
}


void TimerListener::OnResponseSetTargetTimeToStart(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"SetTargetTimeToStart succeeded");
    } else {
        NSLog(@"SetTargetTimeToStart failed");
    }
}

void TimerListener::OnResponseSetTargetTimeToStop(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage)
{
    if (status == ER_OK) {
        NSLog(@"SetTargetTimeToStop succeeded");
    } else {
        NSLog(@"SetTargetTimeToStop failed");
    }
}

