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

#include "ResourceSavingListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus ResourceSavingListener::OnSetResourceSavingMode(const bool& mode)
{
    cout << "ResourceSavingListener::OnSetResourceSavingMode() - ResourceSavingMode : " << mode << endl;
    return ER_OK;
}

QStatus ResourceSavingListener::OnGetResourceSavingMode(bool& mode)
{
    cout << "ResourceSavingListener::OnGetResourceSavingMode() - ResourceSavingMode : " << mode << endl;
    return ER_OK;
}
///////////////////////////////////////////////////////////////////////////////////

ControlleeCommands* ResourceSavingCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new ResourceSavingCommands(sample, objectPath);
}

ResourceSavingCommands::ResourceSavingCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

ResourceSavingCommands::~ResourceSavingCommands()
{
}

void ResourceSavingCommands::Init()
{
    if (!m_intfControllee) {
        HaeInterface* haeInterface = m_sample->CreateInterface(RESOURCE_SAVING_INTERFACE, m_objectPath, m_listener);
        if (!haeInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<ResourceSavingIntfControllee*>(haeInterface);

        RegisterCommand(&ResourceSavingCommands::OnCmdGetResourceSavingMode, "grm", "get resource saving mode");
        RegisterCommand(&ResourceSavingCommands::OnCmdSetResourceSavingMode, "srm", "set resource saving mode(use 'srm <0/1>'");

    } else {
        PrintCommands();
    }
}

void ResourceSavingCommands::OnCmdGetResourceSavingMode(Commands* commands, std::string& cmd)
{
    ResourceSavingIntfControllee* intfControllee = static_cast<ResourceSavingCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << intfControllee->GetResourceSavingMode() << endl;
}

void ResourceSavingCommands::OnCmdSetResourceSavingMode(Commands* commands, std::string& cmd)
{
    ResourceSavingIntfControllee* intfControllee = static_cast<ResourceSavingCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    int mode = strtol(cmd.c_str(), NULL, 10);
    if (mode == 0 || mode == 1) {
        intfControllee->SetResourceSavingMode(mode);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}
