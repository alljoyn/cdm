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
#include "FanSpeedLevelListener.h"

using namespace std;

QStatus FanSpeedLevelListener::OnSetFanSpeedLevel(const uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnSetFanSpeedLevel() - FanSpeedLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnGetFanSpeedLevel(uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnGetFanSpeedLevel() - FanSpeedLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnGetMaxFanSpeedLevel(uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnGetMaxFanSpeedLevel() - MaxFanSpeedLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnSetAutoMode(const uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnSetAutoMode() - AutoMode : " << (int)value << endl;
    return ER_OK;
}

QStatus FanSpeedLevelListener::OnGetAutoMode(uint8_t& value)
{
    cout << "FanSpeedLevelListener::OnGetAutoMode() - AutoMode : " << (int)value << endl;
    return ER_OK;
}

