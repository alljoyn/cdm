/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>

#include "TimerListener.h"

using namespace std;

QStatus TimerListener::GetReferenceTimer(int32_t& time)
{
    return ER_OK;
}

QStatus TimerListener::GetTargetTimeToStart(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetTargetTimeToStop(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetEstimatedTimeToEnd(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetRunningTime(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::GetTargetDuration(int32_t& time)
{
    return ER_OK;

}

QStatus TimerListener::OnSetTargetTimeToStart(int32_t time, ErrorCode& errorCode)
{
    cout << "TimerListener::OnSetTargetTimeToStart" <<endl;
    cout << "time: " << (int)time << endl;
    return ER_OK;
}

QStatus TimerListener::OnSetTargetTimeToStop(int32_t time, ErrorCode& errorCode)
{
    cout << "TimerListener::OnSetTargetTimeToStop" <<endl;
    cout << "time: " << (int)time << endl;
    return ER_OK;
}
