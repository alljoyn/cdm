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

#ifndef CURRENTPOWERLISTENER_H_
#define CURRENTPOWERLISTENER_H_

#include <alljoyn/hae/interfaces/operation/CurrentPowerIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class CurrentPowerListener : public CurrentPowerIntfControlleeListener
{
  public:
    virtual QStatus OnSetCurrentPower(const double currentPower);
    virtual QStatus OnGetCurrentPower(double& currentPower);
    virtual QStatus OnSetPrecision(const double precision);
    virtual QStatus OnGetPrecision(double& precision);
    virtual QStatus OnSetUpdateMinTime(const uint16_t updateMinTime);
    virtual QStatus OnGetUpdateMinTime(uint16_t& updateMinTime);
};

#endif /* CURRENTPOWERLISTENER_H_ */
