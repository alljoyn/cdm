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

#include "TargetHumidityListener.h"
#include "ControlleeSample.h"

#include <sstream>

using namespace std;

QStatus TargetHumidityListener::OnSetTargetValue(const uint8_t value)
{
    cout << "TargetHumidityListener::OnSetTargetValue() - TargetValue : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetHumidityListener::OnGetTargetValue(uint8_t& value)
{
    cout << "TargetHumidityListener::OnGetTargetValue() - TargetValue : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetHumidityListener::OnGetMinValue(uint8_t& value)
{
    cout << "TargetHumidityListener::OnGetMinValue() - MinValue : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetHumidityListener::OnGetMaxValue(uint8_t& value)
{
    cout << "TargetHumidityListener::OnGetMaxValue() - MaxValue : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetHumidityListener::OnGetStepValue(uint8_t& value)
{
    cout << "TargetHumidityListener::OnGetStepValue() - StepValue : " << (int)value << endl;
    return ER_OK;
}

QStatus TargetHumidityListener::OnGetSelectableHumidityLevels(TargetHumidityInterface::HumidityLevels& value)
{
    cout << "TargetHumidityListener::OnGetSelectableHumidityLevels() - sizeof value : " << value.size() << endl;
    return ER_OK;
}

////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* TargetHumidityCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new TargetHumidityCommands(sample, objectPath);
}

TargetHumidityCommands::TargetHumidityCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

TargetHumidityCommands::~TargetHumidityCommands()
{
}

void TargetHumidityCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TARGET_HUMIDITY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<TargetHumidityIntfControllee*>(cdmInterface);

        RegisterCommand(&TargetHumidityCommands::OnCmdGetTargetValue, "gtv", "get target value");
        RegisterCommand(&TargetHumidityCommands::OnCmdSetTargetValue, "stv", "set target value (use 'stv <value>'");
        RegisterCommand(&TargetHumidityCommands::OnCmdGetMinValue, "gmn", "get min value");
        RegisterCommand(&TargetHumidityCommands::OnCmdSetMinValue, "smn", "set min value (use 'smn <value>'");
        RegisterCommand(&TargetHumidityCommands::OnCmdGetMaxValue, "gmx", "get max value");
        RegisterCommand(&TargetHumidityCommands::OnCmdSetMaxValue, "smx", "set max value (use 'smx <value>'");
        RegisterCommand(&TargetHumidityCommands::OnCmdGetStepValue, "gsv", "get step value");
        RegisterCommand(&TargetHumidityCommands::OnCmdSetStepValue, "ssv", "set step value (use 'ssv <value>'");
        RegisterCommand(&TargetHumidityCommands::OnCmdGetSelectableHumidityLevels, "gshl", "get selectable humidity levels");
        RegisterCommand(&TargetHumidityCommands::OnCmdSetSelectableHumidityLevels, "sshl", "set selectable humidity levels (use 'ssv <value>, ...'");
    } else {
        PrintCommands();
    }
}

void TargetHumidityCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t maxvalue = 90;
        uint8_t minvalue = 10;
        uint8_t targetvalue = 20;
        uint8_t stepvalue = 5;
        TargetHumidityInterface::HumidityLevels levels = {10, 20, 30, 35, 40, 50, 60, 70, 80, 85 };

        m_intfControllee->SetMaxValue(maxvalue);
        m_intfControllee->SetMinValue(minvalue);
        m_intfControllee->SetTargetValue(targetvalue);
        m_intfControllee->SetStepValue(stepvalue);
        m_intfControllee->SetSelectableHumidityLevels(levels);
        m_intfControllee->SetStrategyOfAdjustingTargetValue(TargetHumidityIntfControllee::ROUNDING_TO_NEAREST_VALUE);
    }
}

void TargetHumidityCommands::OnCmdGetTargetValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetTargetValue() << endl;
}

void TargetHumidityCommands::OnCmdSetTargetValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t minValue = intfControllee->GetMinValue();
    uint8_t maxValue = intfControllee->GetMaxValue();
    uint8_t value = atoi(cmd.c_str());
    if (value < minValue || value > maxValue) {
        cout << "Input argument is wrong." << endl;
        return;
    }
    intfControllee->SetTargetValue(value);
}

void TargetHumidityCommands::OnCmdGetMinValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMinValue() << endl;
}

void TargetHumidityCommands::OnCmdSetMinValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = atoi(cmd.c_str());
    intfControllee->SetMinValue(value);
}

void TargetHumidityCommands::OnCmdGetMaxValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetMaxValue() << endl;
}

void TargetHumidityCommands::OnCmdSetMaxValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = atoi(cmd.c_str());
    intfControllee->SetMaxValue(value);
}

void TargetHumidityCommands::OnCmdGetStepValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    cout << (int)intfControllee->GetStepValue() << endl;
}

void TargetHumidityCommands::OnCmdSetStepValue(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t value = atoi(cmd.c_str());
    intfControllee->SetStepValue(value);
}

void TargetHumidityCommands::OnCmdGetSelectableHumidityLevels(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    TargetHumidityInterface::HumidityLevels value = intfControllee->GetSelectableHumidityLevels();
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

void TargetHumidityCommands::OnCmdSetSelectableHumidityLevels(Commands* commands, std::string& cmd)
{
    TargetHumidityIntfControllee* intfControllee = static_cast<TargetHumidityCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    TargetHumidityInterface::HumidityLevels value;
    vector<string> values = split(cmd, ',');
    for (size_t i = 0; i < values.size(); ++i) {
        value.push_back(atoi(values[i].c_str()));
    }
    intfControllee->SetSelectableHumidityLevels(value);
}
