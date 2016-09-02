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

#include "CurrentAirQualityLevelListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus CurrentAirQualityLevelListener::OnGetContaminantType(uint8_t& type)
{
    cout << __func__ << " - contaminant type : " << (int)type << endl;
    return ER_OK;
}

QStatus CurrentAirQualityLevelListener::OnGetCurrentLevel(uint8_t& value)
{
    cout << __func__ << " - current value : " << (int)value << endl;
    return ER_OK;
}

QStatus CurrentAirQualityLevelListener::OnGetMaxLevel(uint8_t& value)
{

    cout << __func__ << " - max value : " << (int)value << endl;
    return ER_OK;
}

////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* CurrentAirQualityLevelCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new CurrentAirQualityLevelCommands(sample, objectPath);
}

CurrentAirQualityLevelCommands::CurrentAirQualityLevelCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

CurrentAirQualityLevelCommands::~CurrentAirQualityLevelCommands()
{
}

void CurrentAirQualityLevelCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(CURRENT_AIR_QUALITY_LEVEL_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<CurrentAirQualityLevelIntfControllee*>(cdmInterface);

        RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdGetContaminantType, "gct", "get contaminant type");
        RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdSetContaminantType, "sct", "set contaminant type");
        RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdGetCurrentLevel, "gcv", "get current air quality");
        RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdSetCurrentLevel, "scv", "set current air quality");
        RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdGetMaxLevel, "gmax", "get maximum air quality");
        RegisterCommand(&CurrentAirQualityLevelCommands::OnCmdSetMaxLevel, "smax", "set maximum air quality");
   } else {
        PrintCommands();
    }
}

void CurrentAirQualityLevelCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t contaminatType = CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH2O;
        uint8_t maxLevel = 30;
        uint8_t minLevel = 10;
        uint8_t currentLevel = 15;

        m_intfControllee->SetContaminantType(contaminatType);
        m_intfControllee->SetMaxLevel(maxLevel);
        m_intfControllee->SetCurrentLevel(currentLevel);
    }
}

void CurrentAirQualityLevelCommands::OnCmdGetContaminantType(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfControllee* intfControllee = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetContaminantType() << endl;
}

void CurrentAirQualityLevelCommands::OnCmdSetContaminantType(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfControllee* intfControllee = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = (uint8_t)stoi(cmd.c_str());
    intfControllee->SetContaminantType(value);
}

void CurrentAirQualityLevelCommands::OnCmdGetCurrentLevel(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfControllee* intfControllee = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetCurrentLevel() << endl;
}

void CurrentAirQualityLevelCommands::OnCmdSetCurrentLevel(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfControllee* intfControllee = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxLevel = intfControllee->GetMaxLevel();
    uint8_t value = stoi(cmd.c_str());
    if (value > maxLevel) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetCurrentLevel(value);
}

void CurrentAirQualityLevelCommands::OnCmdGetMaxLevel(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfControllee* intfControllee = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMaxLevel() << endl;
}

void CurrentAirQualityLevelCommands::OnCmdSetMaxLevel(Commands* commands, std::string& cmd)
{
    CurrentAirQualityLevelIntfControllee* intfControllee = static_cast<CurrentAirQualityLevelCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = stoi(cmd.c_str());
    intfControllee->SetMaxLevel(value);
}
