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

#include "LanguageDisplayCommands.h"
#include "ControllerSample.h"

LanguageDisplayListener::LanguageDisplayListener()
{
}

LanguageDisplayListener::~LanguageDisplayListener()
{
}

void LanguageDisplayListener::GetDisplayLanguagePropertyCallback(QStatus status, const qcc::String& objectPath, const qcc::String displayLanguage, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayLanguage: " << displayLanguage.c_str() << endl;
}
void LanguageDisplayListener::SetDisplayLanguagePropertyCallback(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
}
void LanguageDisplayListener::GetSupportedDisplayLanguagesPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# supported temperature units: " << endl;
    for (size_t i = 0; i < supportedDisplayLanguages.size(); ++i) {
        cout << supportedDisplayLanguages[i].c_str() << endl;
    }
}
void LanguageDisplayListener::DisplayLanguagePropertyChanged(const qcc::String& objectPath, const qcc::String displayLanguage)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayLanguage: " << displayLanguage.c_str() << endl;

}
void LanguageDisplayListener::SupportedDisplayLanguagesPropertyChanged(const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# supported temperature units: " << endl;
    for (size_t i = 0; i < supportedDisplayLanguages.size(); ++i) {
        cout << supportedDisplayLanguages[i].c_str() << endl;
    }
}

LanguageDisplayCommands::LanguageDisplayCommands(ControllerSample* sample, DeviceInfoPtr& info, const char* objectPath)
: InterfaceCommands(sample, info, objectPath),
  m_intfController(NULL)
{
}

LanguageDisplayCommands::~LanguageDisplayCommands()
{

}

void LanguageDisplayCommands::Init()
{
    if (!m_intfController) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(LANGUAGE_DISPLAY_INTERFACE, m_deviceInfo->GetBusName(), m_objectPath, m_deviceInfo->GetSessionId(), m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfController = static_cast<LanguageDisplayIntfController*>(cdmInterface);
    }

    RegisterCommand(&LanguageDisplayCommands::OnCmdGetDisplayLanguage, "gdl", "get display language");
    RegisterCommand(&LanguageDisplayCommands::OnCmdSetDisplayLanguage, "sdl", "set display language (use 'sdl <lang>')");
    RegisterCommand(&LanguageDisplayCommands::OnCmdGetSupportedDisplayLanguages, "gsdl", "get supported display languages");
    PrintCommands();
}


void LanguageDisplayCommands::OnCmdGetDisplayLanguage(Commands* commands, std::string& cmd)
{
    LanguageDisplayIntfController* intfController = static_cast<LanguageDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    intfController->GetDisplayLanguage();
}

void LanguageDisplayCommands::OnCmdGetSupportedDisplayLanguages(Commands* commands, std::string& cmd)
{
    LanguageDisplayIntfController* intfController = static_cast<LanguageDisplayCommands*>(commands)->GetInterface();
    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }

    intfController->GetSupportedDisplayLanguages();
}
void LanguageDisplayCommands::OnCmdSetDisplayLanguage(Commands* commands, std::string& cmd)
{
    LanguageDisplayIntfController* intfController = static_cast<LanguageDisplayCommands*>(commands)->GetInterface();

    if (!intfController) {
        cout << "Interface is not exist." << endl;
        return;
    }
    qcc::String displayLanguage(cmd.c_str());

    intfController->SetDisplayLanguage(displayLanguage);
}
