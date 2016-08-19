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
#ifndef DEVICEEMULATOR_H_
#define DEVICEEMULATOR_H_

#include <iostream>
#include <qcc/Log.h>
#include <qcc/String.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>
#include <alljoyn/cdm/CdmAboutData.h>
#include "ConfigLoader.h"
#include "VirtualDevice.h"

using namespace std;
using namespace qcc;

namespace ajn {

class BusAttachment;

namespace services {

class DeviceEmulator
{
private:
    CdmAboutData m_aboutData;
    BusAttachment* m_bus;
    ConfigLoader m_configLoader;
    VirtualDevice* m_virtualDevice;
public:
    DeviceEmulator(const string& configPath);
    ~DeviceEmulator();

    void InitCommandsFactory();
    void Startup();
    void Shutdown();
};

}
}


#endif  //DEVICEEMULATOR_H_
