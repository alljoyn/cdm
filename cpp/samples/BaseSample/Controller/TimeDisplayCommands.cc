/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#include "TimeDisplayCommands.h"
#include "ControllerSample.h"

TimeDisplayListener::TimeDisplayListener()
{
}

TimeDisplayListener::~TimeDisplayListener()
{
}


void TimeDisplayListener::GetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t timeformat, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayTimeFormat: " << (int)timeformat << endl;

}

void TimeDisplayListener::SetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
}

void TimeDisplayListener::GetSupportedDisplayTimeFormatsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# supported display time formats: " << endl;
    for (size_t i = 0; i < supportedTimeFormats.size(); ++i) {
        cout << (int)supportedTimeFormats[i] << endl;
    }
}

void TimeDisplayListener::DisplayTimeFormatPropertyChanged(const qcc::String& objectPath, const uint8_t timeformat)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayTimeFormat: " << (int)timeformat << endl;

}

void TimeDisplayListener::SupportedDisplayTimeFormatsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    for (size_t i = 0; i < supportedTimeFormats.size(); ++i) {
        cout << (int)supportedTimeFormats[i] << endl;
    }
}



TimeDisplayCommands::TimeDisplayCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

TimeDisplayCommands::~TimeDisplayCommands()
{

}

void TimeDisplayCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(TIME_DISPLAY_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<TimeDisplayIntfController*>(cdmInterface);
    }

    RegisterCommand(&TimeDisplayCommands::OnCmdGetDisplayTimeFormat, "gdtf", "get display time format");
    RegisterCommand(&TimeDisplayCommands::OnCmdSetDisplayTimeFormat, "sdtf", "set display time format (use 'sdtf <0 - 12 h format / 1 -24 h format>')");
    RegisterCommand(&TimeDisplayCommands::OnCmdGetSupportedDisplayTimeFormats, "gsdtf", "get supported display time formats");
    PrintCommands();
}


void TimeDisplayCommands::OnCmdGetDisplayTimeFormat(Commands* commands, std::string& cmd)
{
    TimeDisplayIntfController* intfController = static_cast<TimeDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetDisplayTimeFormat();
}

void TimeDisplayCommands::OnCmdGetSupportedDisplayTimeFormats(Commands* commands, std::string& cmd)
{
    TimeDisplayIntfController* intfController = static_cast<TimeDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedDisplayTimeFormats();
}
void TimeDisplayCommands::OnCmdSetDisplayTimeFormat(Commands* commands, std::string& cmd)
{
    TimeDisplayIntfController* intfController = static_cast<TimeDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    int timeFormat = strtol(cmd.c_str(), NULL, 10);

    intfController->SetDisplayTimeFormat(timeFormat);
}
