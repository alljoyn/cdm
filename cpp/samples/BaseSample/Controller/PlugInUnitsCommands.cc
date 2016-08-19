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

#include "PlugInUnitsCommands.h"
#include "ControllerSample.h"

PlugInUnitsListener::PlugInUnitsListener()
{
}

PlugInUnitsListener::~PlugInUnitsListener()
{
}

void PlugInUnitsListener::OnResponseGetPlugInUnits(QStatus status, const qcc::String& objectPath, const PlugInUnitsInterface::PlugInUnits& units, void* context)
{
    cout << __func__ << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# PlugInUnits" << endl;
    for (size_t i = 0; i < units.size(); i++)
    {
        cout << "Unit " << i << endl;
        cout << "  object path: " << units[i].objectPath << endl;
        cout << "  device id: " << units[i].deviceId << endl;
        cout << "  plugged in: " << units[i].pluggedIn << endl;
    }
}

void PlugInUnitsListener::OnPlugInUnitsPropertyChanged(const qcc::String& objectPath, const PlugInUnitsInterface::PlugInUnits& units)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# PlugInUnits" << endl;
    for (size_t i = 0; i < units.size(); i++)
    {
        cout << "Unit " << i << endl;
        cout << "  object path: " << units[i].objectPath << endl;
        cout << "  device id: " << units[i].deviceId << endl;
        cout << "  plugged in: " << units[i].pluggedIn << endl;
    }
}

 PlugInUnitsCommands::PlugInUnitsCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

PlugInUnitsCommands::~PlugInUnitsCommands()
{

}

void PlugInUnitsCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(PLUG_IN_UNITS_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<PlugInUnitsIntfController*>(cdmInterface);
    }

    RegisterCommand(&PlugInUnitsCommands::OnCmdGetPlugInUnits, "gpu", "get plug in units");
    PrintCommands();
}

void PlugInUnitsCommands::OnCmdGetPlugInUnits(Commands* commands, std::string& cmd)
{
    PlugInUnitsIntfController* intfController = static_cast<PlugInUnitsCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetPlugInUnits();
}
