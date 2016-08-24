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

#include "TargetTemperatureLevelListener.h"
#include "ControlleeSample.h"

#include <sstream>

using namespace std;

QStatus TargetTemperatureLevelListener::OnSetTargetLevel(const uint8_t value)
{
    cout << "TargetTemperatureLevelListener::OnSetTargetLevel() - TargetLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetTemperatureLevelListener::OnGetTargetLevel(uint8_t& value)
{
    cout << "TargetTemperatureLevelListener::OnGetTargetLevel() - TargetLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetTemperatureLevelListener::OnGetMaxLevel(uint8_t& value)
{
    cout << "TargetTemperatureLevelListener::OnGetMaxLevel() - MaxLevel : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetTemperatureLevelListener::OnGetSelectableTemperatureLevels(TargetTemperatureLevelInterface::TemperatureLevels& value)
{
    cout << "TargetTemperatureLevelListener::OnGetSelectableTemperatureLevels() - sizeof value : " << value.size() << endl;
    return ER_OK;
}

////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* TargetTemperatureLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new TargetTemperatureLevelCommands(sample, objectPath);
}

TargetTemperatureLevelCommands::TargetTemperatureLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

TargetTemperatureLevelCommands::~TargetTemperatureLevelCommands()
{
}

void TargetTemperatureLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TARGET_TEMPERATURE_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<TargetTemperatureLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&TargetTemperatureLevelCommands::OnCmdGetTargetLevel, "gtl", "get target level");
        RegisterCommand(&TargetTemperatureLevelCommands::OnCmdSetTargetLevel, "stl", "set target level (use 'stv <value>'");
        RegisterCommand(&TargetTemperatureLevelCommands::OnCmdGetMaxLevel, "gmx", "get max level");
        RegisterCommand(&TargetTemperatureLevelCommands::OnCmdSetMaxLevel, "smx", "set max level (use 'smx <value>'");
        RegisterCommand(&TargetTemperatureLevelCommands::OnCmdGetSelectableTemperatureLevels, "gshl", "get selectable temperature levels");
        RegisterCommand(&TargetTemperatureLevelCommands::OnCmdSetSelectableTemperatureLevels, "sshl", "set selectable temperature levels (use 'ssv <value>, ...'");
    } else {
        PrintCommands();
    }
}

void TargetTemperatureLevelCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t maxvalue = 90;
        uint8_t targetvalue = 20;
        TargetTemperatureLevelInterface::TemperatureLevels levels = {10, 20, 30, 35, 40, 50, 60, 70, 80, 85 };

        m_intfControllee->SetMaxLevel(maxvalue);
        m_intfControllee->SetTargetLevel(targetvalue);
        m_intfControllee->SetSelectableTemperatureLevels(levels);
    }
}

void TargetTemperatureLevelCommands::OnCmdGetTargetLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfControllee* intfControllee = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetTargetLevel() << endl;
}

void TargetTemperatureLevelCommands::OnCmdSetTargetLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfControllee* intfControllee = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxValue = intfControllee->GetMaxLevel();
    uint8_t value = atoi(cmd.c_str());
    intfControllee->SetTargetLevel(value);
}

void TargetTemperatureLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfControllee* intfControllee = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMaxLevel() << endl;
}

void TargetTemperatureLevelCommands::OnCmdSetMaxLevel(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfControllee* intfControllee = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = atoi(cmd.c_str());
    intfControllee->SetMaxLevel(value);
}

void TargetTemperatureLevelCommands::OnCmdGetSelectableTemperatureLevels(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfControllee* intfControllee = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    TargetTemperatureLevelInterface::TemperatureLevels value = intfControllee->GetSelectableTemperatureLevels();
    for (size_t i = 0; i < value.size(); i++) {
        cout << (int)value[i] << ", ";
    }
    cout << endl;
}

static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void TargetTemperatureLevelCommands::OnCmdSetSelectableTemperatureLevels(Commands* commands, std::string& cmd)
{
    TargetTemperatureLevelIntfControllee* intfControllee = static_cast<TargetTemperatureLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    TargetTemperatureLevelInterface::TemperatureLevels value;
    vector<string> values = split(cmd, ',');
    for (size_t i = 0; i < values.size(); ++i) {
        value.push_back(atoi(values[i].c_str()));
    }
    intfControllee->SetSelectableTemperatureLevels(value);
}
