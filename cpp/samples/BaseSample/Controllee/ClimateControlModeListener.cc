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
#include "ClimateControlModeListener.h"

using namespace std;

QStatus ClimateControlModeListener::OnSetMode(const uint16_t& mode)
{
    cout << "ClimateControlModeListener::OnSetMode() - Mode : " << mode << endl;
    return ER_OK;
}

QStatus ClimateControlModeListener::OnGetMode(uint16_t& mode)
{
    cout << "ClimateControlModeListener::OnGetMode() - Mode : " << mode << endl;
    return ER_OK;
}

QStatus ClimateControlModeListener::OnGetSupportedModes(SupportedModes& modes)
{
    cout << "ClimateControlModeListener::OnGetSupportedModes() - modes : ";

    for(size_t i=0 ; i < modes.size() ; i++)
    {
        cout << modes[i] << " ";
    }
    cout << endl;

    return ER_OK;
}

QStatus ClimateControlModeListener::OnGetOperationalState(uint16_t& operationalState)
{
    cout << "ClimateControlModeListener::OnGetOperationalState() - operationalState : " << operationalState << endl;
    return ER_OK;
}
