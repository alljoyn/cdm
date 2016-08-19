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
#ifndef VIRTUALDEVICE_H_
#define VIRTUALDEVICE_H_

#include "ControlleeSample.h"
#include "ConfigLoader.h"

namespace ajn {

class BusAttachment;

namespace services {

class VirtualDevice : public ControlleeSample
{
private:
    InterfaceList* m_interfaceList;

public:
    VirtualDevice(BusAttachment* bus, CdmAboutData* aboutData, InterfaceList* list);
    virtual ~VirtualDevice();

    void InitSample();
    void CreateInterfaces();
    void SetInitialProperty();
    InterfaceList* GetInterfaceList();
};

}
}

#endif  // VIRTUALDEVICE_H_
