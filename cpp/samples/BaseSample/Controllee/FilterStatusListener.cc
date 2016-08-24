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

#include "FilterStatusListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus FilterStatusListener::OnGetExpectedLifeInDays(uint16_t& value)
{
    cout << "FilterStatusListener::OnGetExpectedLifeInDays()" << endl;
    return ER_OK;
}

QStatus FilterStatusListener::OnGetIsCleanable(bool& isCleanable)
{
    cout << "FilterStatusListener::OnGetIsCleanable()" << endl;
    return ER_OK;
}

QStatus FilterStatusListener::OnGetOrderPercentage(uint8_t& value)
{
    cout << "FilterStatusListener::OnGetOrderPercentage()" << endl;
    return ER_OK;
}

QStatus FilterStatusListener::OnGetManufacturer(qcc::String& manufacturer)
{
    cout << "FilterStatusListener::OnGetManufacturer()" << endl;
    return ER_OK;
}

QStatus FilterStatusListener::OnGetPartNumber(qcc::String& partNumber)
{
    cout << "FilterStatusListener::OnGetPartNumber()" << endl;
    return ER_OK;
}

QStatus FilterStatusListener::OnGetUrl(qcc::String& url)
{
    cout << "FilterStatusListener::OnGetUrl()" << endl;
    return ER_OK;
}

QStatus FilterStatusListener::OnGetLifeRemaining(uint8_t& value)
{
    cout << "FilterStatusListener::OnGetLifeRemaining()" << endl;
    return ER_OK;
}

/////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* FilterStatusCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new FilterStatusCommands(sample, objectPath);
}

FilterStatusCommands::FilterStatusCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

FilterStatusCommands::~FilterStatusCommands()
{
}

void FilterStatusCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(FILTER_STATUS_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<FilterStatusIntfControllee*>(cdmInterface);

        RegisterCommand(&FilterStatusCommands::OnCmdGetExpectedLifeInDays, "gelid", "get expected life in days");
        RegisterCommand(&FilterStatusCommands::OnCmdSetExpectedLifeInDays, "selid", "set expected life in days (use 'selid <value>'");
        RegisterCommand(&FilterStatusCommands::OnCmdGetIsCleanable, "gica", "get is cleanable");
        RegisterCommand(&FilterStatusCommands::OnCmdSetIsCleanable, "sica", "set is cleanable (use 'sica <0/1>'");
        RegisterCommand(&FilterStatusCommands::OnCmdGetOrderPercentage, "gop", "get order percentage");
        RegisterCommand(&FilterStatusCommands::OnCmdSetOrderPercentage, "sop", "set order percentage (use 'sop <value>'");
        RegisterCommand(&FilterStatusCommands::OnCmdGetManufacturer, "gmanu", "get manufacturer");
        RegisterCommand(&FilterStatusCommands::OnCmdGetPartNumber, "gpn", "get part number");
        RegisterCommand(&FilterStatusCommands::OnCmdGetUrl, "gurl", "get url");
        RegisterCommand(&FilterStatusCommands::OnCmdGetLifeRemaining, "glr", "get life remaining");
        RegisterCommand(&FilterStatusCommands::OnCmdSetLifeRemaining, "slr", "set life remaining (use 'slr <value>'");
    } else {
        PrintCommands();
    }
}

void FilterStatusCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint16_t expectedLifeInDays = 30;
        bool isCleanable = true;
        uint8_t orderPercentage = 0;
        qcc::String manufacturer = "CDM";
        uint8_t lifeRemaining = 100;

        m_intfControllee->SetExpectedLifeInDays(expectedLifeInDays);
        m_intfControllee->SetIsCleanable(isCleanable);
        m_intfControllee->SetOrderPercentage(orderPercentage);
        m_intfControllee->SetManufacturer(manufacturer);
        m_intfControllee->SetLifeRemaining(lifeRemaining);
    }
}

void FilterStatusCommands::OnCmdGetExpectedLifeInDays(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetExpectedLifeInDays() << endl;
}

void FilterStatusCommands::OnCmdSetExpectedLifeInDays(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint16_t expectedLifeInDays = strtol(cmd.c_str(), NULL, 10);
    if (expectedLifeInDays >= 0) {
        intfControllee->SetExpectedLifeInDays(expectedLifeInDays);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}

void FilterStatusCommands::OnCmdGetIsCleanable(Commands* commands, std::string& cmd)
{
	FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetIsCleanable() << endl;
}

void FilterStatusCommands::OnCmdSetIsCleanable(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t isCleanable = strtol(cmd.c_str(), NULL, 10);
    if (isCleanable == 0 || isCleanable == 1) {
        intfControllee->SetIsCleanable(isCleanable);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}

void FilterStatusCommands::OnCmdGetOrderPercentage(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetOrderPercentage() << endl;
}

void FilterStatusCommands::OnCmdSetOrderPercentage(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t orderPercentage = strtol(cmd.c_str(), NULL, 10);
    if ((orderPercentage >= 0 && orderPercentage <= 100) || orderPercentage == 255) {
        intfControllee->SetOrderPercentage(orderPercentage);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}

void FilterStatusCommands::OnCmdGetManufacturer(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetManufacturer() << endl;
}

void FilterStatusCommands::OnCmdGetPartNumber(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetPartNumber() << endl;
}

void FilterStatusCommands::OnCmdGetUrl(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetUrl() << endl;
}

void FilterStatusCommands::OnCmdGetLifeRemaining(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << (int)intfControllee->GetLifeRemaining() << endl;
}

void FilterStatusCommands::OnCmdSetLifeRemaining(Commands* commands, std::string& cmd)
{
    FilterStatusIntfControllee* intfControllee = static_cast<FilterStatusCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t lifeRemaining = strtol(cmd.c_str(), NULL, 10);
    if (lifeRemaining >= 0 && lifeRemaining <= 100) {
        intfControllee->SetLifeRemaining(lifeRemaining);
    } else {
        cout << "Input argument is wrong." << endl;
        return;
    }
}
