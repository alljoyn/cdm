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
#include "TargetTemperatureListener.h"

using namespace std;

QStatus TargetTemperatureListener::OnSetTargetValue(const double& value)
{
    cout << "TargetTemperatureListener::OnSetTargetValue() - TargetValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetTargetValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetTargetValue() - TargetValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetMinValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetMinValue() - MinValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetMaxValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetMaxValue() - MaxValue : " << value << endl;
    return ER_OK;
}

QStatus TargetTemperatureListener::OnGetStepValue(double& value)
{
    cout << "TargetTemperatureListener::OnGetStepValue() - StepValue : " << value << endl;
    return ER_OK;
}
