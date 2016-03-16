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
#include "HidListener.h"

// Integration of UInput functionalities
// Default activation status = OFF
// To activate it : scons BINDINGS=... UINPUT=on
#ifdef UINPUT
#include "UInput.h"
#endif

using namespace std;

void HidListener::OnInjectEvents(HidInterface::InputEvents& inputEvents)
{
#ifdef UINPUT
    // we use UInput to inject each event in linux kernel
    for (HidInterface::InputEvents::iterator it = inputEvents.begin() ; it != inputEvents.end(); ++it) {
        HidInterface::InputEvent iev = *it;
        if(UInput::Instance().InjectEvent(iev.type, iev.code, iev.value) < 0) {
            cout << "event injection >> [type : " << iev.type << "] [code : " << iev.code << "] [value :" << iev.value << "] >> FAILURE" << endl;
            break;
        }
        else {
            cout << "event injection >> [type : " << iev.type << "] [code : " << iev.code << "] [value :" << iev.value << "] >> INJECTED" << endl;
        }
    }
#else
    cout << "HidListener::OnInjectEvents - inputEvents size : " << inputEvents.size() << endl;
#endif
}

QStatus HidListener::OnGetSupportedEvents(HidInterface::SupportedInputEvents& supportedEvents)
{
    cout << "HidListener::OnGetSupportedEvents()" << endl;
    return ER_OK;
}
