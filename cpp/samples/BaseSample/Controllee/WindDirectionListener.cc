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

#include "WindDirectionListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus WindDirectionListener::OnSetHorizontalDirection(const uint16_t& value)
{
    cout << "WindDirectionListener::OnSetHorizontalDirection() - HorizontalDirection : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetHorizontalDirection(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetHorizontalDirection() - HorizontalDirection : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetHorizontalMax(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetHorizontalMax() - HorizontalMax : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnSetHorizontalAutoMode(const uint8_t& value)
{
    cout << "WindDirectionListener::OnSetHorizontalAutoMode() - HorizontalAutoMode : " << (int)value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetHorizontalAutoMode(uint8_t& value)
{
    cout << "WindDirectionListener::OnGetHorizontalAutoMode()" << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnSetVerticalDirection(const uint16_t& value)
{
    cout << "WindDirectionListener::OnSetVerticalDirection() - VerticalDirection : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetVerticalDirection(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetVerticalDirection() - VerticalDirection : " << (int)value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetVerticalMax(uint16_t& value)
{
    cout << "WindDirectionListener::OnGetVerticalMax() - VerticalMax : " << value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnSetVerticalAutoMode(const uint8_t& value)
{
    cout << "WindDirectionListener::OnSetVerticalAutoMode() - VerticalAutoMode : " << (int)value << endl;
    return ER_OK;
}

QStatus WindDirectionListener::OnGetVerticalAutoMode(uint8_t& value)
{
    cout << "WindDirectionListener::OnGetVerticalAutoMode()" << endl;
    return ER_OK;
}

/////////////////////////////////////////////////////////////////////////////////
ControlleeCommands* WindDirectionCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new WindDirectionCommands(sample, objectPath);
}

WindDirectionCommands::WindDirectionCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

WindDirectionCommands::~WindDirectionCommands()
{
}

void WindDirectionCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(WIND_DIRECTION_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<WindDirectionIntfControllee*>(cdmInterface);

        RegisterCommand(&WindDirectionCommands::OnCmdGetHorizontalDirection, "ghd", "get horizontal direction");
        RegisterCommand(&WindDirectionCommands::OnCmdSetHorizontalDirection, "shd", "set horizontal direction (use 'shd <direction>'");

        RegisterCommand(&WindDirectionCommands::OnCmdGetHorizontalMax, "ghm", "get horizontal max");
        RegisterCommand(&WindDirectionCommands::OnCmdSetHorizontalMax, "shm", "set horizontal max(use 'shm <max>'");

        RegisterCommand(&WindDirectionCommands::OnCmdGetHorizontalAutoMode, "gha", "get horizontal auto mode");
        RegisterCommand(&WindDirectionCommands::OnCmdSetHorizontalAutoMode, "sha", "set horizontal auto mode(use 'sha <0/1>'");

        RegisterCommand(&WindDirectionCommands::OnCmdGetVerticalDirection, "gvd", "get vertical direction");
        RegisterCommand(&WindDirectionCommands::OnCmdSetVerticalDirection, "svd", "set vertical direction (use 'shd <direction>'");

        RegisterCommand(&WindDirectionCommands::OnCmdGetVerticalMax, "gvm", "get vertical max");
        RegisterCommand(&WindDirectionCommands::OnCmdSetVerticalMax, "svm", "set vertical max(use 'shm <max>'");

        RegisterCommand(&WindDirectionCommands::OnCmdGetVerticalAutoMode, "gva", "get vertical auto mode");
        RegisterCommand(&WindDirectionCommands::OnCmdSetVerticalAutoMode, "sva", "set vertical auto mode(use 'sha <0/1>'");

    } else {
        PrintCommands();
    }
}

void WindDirectionCommands::InitializeProperties()
{
    if (m_intfControllee) {
        uint8_t h_automode = 0;
        uint16_t h_direction = 0;
        uint8_t v_automode = 0;
        uint16_t V_direction = 0;

        m_intfControllee->SetHorizontalAutoMode(h_automode);
        m_intfControllee->SetHorizontalDirection(h_direction);
        m_intfControllee->SetVerticalAutoMode(v_automode);
        m_intfControllee->SetVerticalDirection(V_direction);
    }
}

void WindDirectionCommands::OnCmdGetHorizontalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetHorizontalDirection() << endl;
}

void WindDirectionCommands::OnCmdSetHorizontalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint16_t direction = strtol(cmd.c_str(), NULL, 10);
    uint16_t maxDirection = intfControllee->GetHorizontalMax();
    if (direction >= 0 && direction <= maxDirection) {
        intfControllee->SetHorizontalDirection(direction);
    } else {
        cout << "Input argument is wrong. (0 ~ " << maxDirection << ")" << endl;
        return;
    }
}

void WindDirectionCommands::OnCmdGetHorizontalMax(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetHorizontalMax() << endl;
}

void WindDirectionCommands::OnCmdSetHorizontalMax(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxDirection = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetHorizontalMax(maxDirection);
}

void WindDirectionCommands::OnCmdGetHorizontalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t result = intfControllee->GetHorizontalAutoMode();
    if (result == WindDirectionInterface::AUTO_MODE_ON) {
        cout << "ON" << endl;
    } else if (result  == WindDirectionInterface::AUTO_MODE_OFF) {
        cout << "OFF" << endl;
    } else if (result  == WindDirectionInterface::AUTO_MODE_NOT_SUPPORTED) {
        cout << "NOT_SUPPORTED" << endl;
    } else {
        cout << "UNKNOWN_VALUE : " << (int)result << endl;
    }
}

void WindDirectionCommands::OnCmdSetHorizontalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t autoMode = strtol(cmd.c_str(), NULL, 10);
    if (autoMode != WindDirectionInterface::AUTO_MODE_OFF &&
        autoMode != WindDirectionInterface::AUTO_MODE_ON &&
        autoMode != WindDirectionInterface::AUTO_MODE_NOT_SUPPORTED) {
        cout << "Input argument is wrong." << endl;
    } else {
        intfControllee->SetHorizontalAutoMode(autoMode);
    }
}

void WindDirectionCommands::OnCmdGetVerticalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetVerticalDirection() << endl;
}

void WindDirectionCommands::OnCmdSetVerticalDirection(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint16_t direction = strtol(cmd.c_str(), NULL, 10);
    uint16_t maxDirection = intfControllee->GetVerticalMax();
    if (direction >= 0 && direction <= maxDirection) {
        intfControllee->SetVerticalDirection(direction);
    } else {
        cout << "Input argument is wrong. (0 ~ " << maxDirection << ")" << endl;
        return;
    }
}

void WindDirectionCommands::OnCmdGetVerticalMax(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetVerticalMax() << endl;
}

void WindDirectionCommands::OnCmdSetVerticalMax(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t maxDirection = strtol(cmd.c_str(), NULL, 10);
    intfControllee->SetVerticalMax(maxDirection);
}

void WindDirectionCommands::OnCmdGetVerticalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t result = intfControllee->GetVerticalAutoMode();
    if (result == WindDirectionInterface::AUTO_MODE_ON) {
        cout << "ON" << endl;
    } else if (result  == WindDirectionInterface::AUTO_MODE_OFF) {
        cout << "OFF" << endl;
    } else if (result  == WindDirectionInterface::AUTO_MODE_NOT_SUPPORTED) {
        cout << "NOT_SUPPORTED" << endl;
    } else {
        cout << "UNKNOWN_VALUE : " << (int)result << endl;
    }
}

void WindDirectionCommands::OnCmdSetVerticalAutoMode(Commands* commands, std::string& cmd)
{
    WindDirectionIntfControllee* intfControllee = static_cast<WindDirectionCommands*>(commands)->GetInterface();
    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    uint8_t autoMode = strtol(cmd.c_str(), NULL, 10);
    if (autoMode != WindDirectionInterface::AUTO_MODE_OFF &&
        autoMode != WindDirectionInterface::AUTO_MODE_ON &&
        autoMode != WindDirectionInterface::AUTO_MODE_NOT_SUPPORTED) {
        cout << "Input argument is wrong." << endl;
    } else {
        intfControllee->SetVerticalAutoMode(autoMode);
    }
}
