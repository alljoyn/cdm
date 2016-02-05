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

#include <cstdlib>
#include <alljoyn/hae/interfaces/HaeInterfaceTypes.h>
#include "ResourceSavingCommands.h"
#include "ControllerSample.h"

ResourceSavingListener::ResourceSavingListener()
{
}

ResourceSavingListener::~ResourceSavingListener()
{
}

void ResourceSavingListener::OnResponseSetResourceSavingMode(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
}

void ResourceSavingListener::OnResponseGetResourceSavingMode(QStatus status, const qcc::String& objectPath, const bool value, void* context)
{
    cout << __func__ << endl;
    cout << "status: " << QCC_StatusText(status) << endl;
    cout << "path: " << objectPath << endl;
    cout << "ResoucrceSavingMode: " << value << endl;
}

void ResourceSavingListener::OnResourceSavingModeChanged(const qcc::String& objectPath, const bool value)
{
    cout << __func__ << endl;
    cout << "path: " << objectPath << endl;
    cout << "ResoucrceSavingMode: " << value << endl;
}

ResourceSavingCommands::ResourceSavingCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

ResourceSavingCommands::~ResourceSavingCommands()
{
}

void ResourceSavingCommands::Init()
{
    if (!m_intfController) {
        HaeInterface* haeInterface = m_sample->CreateInterface(RESOURCE_SAVING_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<ResourceSavingIntfController*>(haeInterface);
    }

    RegisterCommand(&ResourceSavingCommands::OnCmdGetResourceSavingMode, "getrs", "Get ResoucrceSavingMode");
    RegisterCommand(&ResourceSavingCommands::OnCmdSetResourceSavingMode, "setrs", "Set ResoucrceSavingMode");

    PrintCommands();
}


void ResourceSavingCommands::OnCmdGetResourceSavingMode(Commands* commands, std::string& cmd)
{
    ResourceSavingIntfController* intfController = static_cast<ResourceSavingCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetResourceSavingMode();
}

void ResourceSavingCommands::OnCmdSetResourceSavingMode(Commands* commands, std::string& cmd)
{
    ResourceSavingIntfController* intfController = static_cast<ResourceSavingCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode < 0 || mode >= 2) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfController->SetResourceSavingMode(mode);
}

