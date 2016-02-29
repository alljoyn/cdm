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
#include "CurrentPowerListener.h"

using namespace std;

QStatus CurrentPowerListener::OnSetCurrentPower(const double currentPower)
{
    cout << "CurrentPowerListener::OnSetCurrentPower() - CurrentPower : " << currentPower << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnGetCurrentPower(double& currentPower)
{
    cout << "CurrentPowerListener::OnGetCurrentPower() - CurrentPower : " << currentPower << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnSetPrecision(const double precision)
{
    cout << "CurrentPowerListener::OnSetPrecision() - precision : " << precision << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnGetPrecision(double& precision)
{
    cout << "CurrentPowerListener::OnGetPrecision() - precision : " << precision << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnSetUpdateMinTime(const uint16_t updateMinTime)
{
    cout << "CurrentPowerListener::OnSetUpdateMinTime() - updateMinTime) : " << updateMinTime << endl;
    return ER_OK;
}

QStatus CurrentPowerListener::OnGetUpdateMinTime(uint16_t& updateMinTime)
{
    cout << "CurrentPowerListener::OnGetUpdateMinTime() - updateMinTime : " << updateMinTime << endl;
    return ER_OK;
}

