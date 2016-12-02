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

#include <iostream>
#include "LanguageDisplayListener.h"
#include "ControlleeSample.h"

using namespace std;

QStatus LanguageDisplayListener::OnGetDisplayLanguage(qcc::String& temperatureUnit)
{
    cout << " LanguageDisplayListener::OnGetDisplayLanguage" << endl;
    return ER_OK;
}

QStatus LanguageDisplayListener::OnSetDisplayLanguage(const qcc::String& temperatureUnit)
{
    cout << " TemperatureDisplayListener::OnSetDisplayLanguage" << endl;
    return ER_OK;
}

QStatus LanguageDisplayListener::OnGetSupportedDisplayLanguages(std::vector<qcc::String>& supportedDisplayLanguages)
{
    cout << " TemperatureDisplayListener::OnGetSupportedDisplayLanguages" << endl;
    return ER_OK;
}


ControlleeCommands* LanguageDisplayCommands::CreateCommands(ControlleeSample* sample, const char* objectPath)
{
    return new LanguageDisplayCommands(sample, objectPath);
}

LanguageDisplayCommands::LanguageDisplayCommands(ControlleeSample* sample, const char* objectPath)
: InterfaceCommands(sample, objectPath)
, m_intfControllee(NULL)
{
}

LanguageDisplayCommands::~LanguageDisplayCommands()
{
}

void LanguageDisplayCommands::Init()
{
    if (!m_intfControllee) {
        CdmInterface* cdmInterface = m_sample->CreateInterface(LANGUAGE_DISPLAY_INTERFACE, m_objectPath, m_listener);
        if (!cdmInterface) {
            cout << "Interface creation failed." << endl;
            return;
        }

        m_intfControllee = static_cast<LanguageDisplayIntfControllee*>(cdmInterface);

        RegisterCommand(&LanguageDisplayCommands::OnCmdGetDisplayLanguage, "gdl", "get display language");
        RegisterCommand(&LanguageDisplayCommands::OnCmdSetDisplayLanguage, "sdl", "set display language(use 'sdl <lang>')");
        RegisterCommand(&LanguageDisplayCommands::OnCmdGetSupportedDisplayLanguages, "gsdl", "get supported display languages");
    } else {
        PrintCommands();
    }
}

void LanguageDisplayCommands::InitializeProperties()
{
    if (m_intfControllee) {
        qcc::String displayLanguage("en");
        std::vector<qcc::String> supportedDisplayLanguages;

        supportedDisplayLanguages.push_back(qcc::String("en"));
        supportedDisplayLanguages.push_back(qcc::String("es"));
        supportedDisplayLanguages.push_back(qcc::String("fr"));

        m_intfControllee->SetDisplayLanguage(displayLanguage);
        m_intfControllee->SetSupportedDisplayLanguages(supportedDisplayLanguages);
    }
}

void LanguageDisplayCommands::OnCmdGetDisplayLanguage(Commands* commands, std::string& cmd)
{
    cout << "LanguageDisplayCommands::OnCmdGetDisplayTimeFormat" << endl;
    LanguageDisplayIntfControllee* intfControllee = static_cast<LanguageDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }
    cout << intfControllee->GetDisplayLanguage().c_str() << endl;
}
void LanguageDisplayCommands::OnCmdSetDisplayLanguage(Commands* commands, std::string& cmd)
{
    cout << "LanguageDisplayCommands::OnCmdSetDisplayLanguage" << endl;
    LanguageDisplayIntfControllee* intfControllee = static_cast<LanguageDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    qcc::String displayLanguage(cmd);
    cout << "Language to set: " << displayLanguage.c_str() <<endl;
    intfControllee->SetDisplayLanguage(displayLanguage);
}

void LanguageDisplayCommands::OnCmdGetSupportedDisplayLanguages(Commands* commands, std::string& cmd)
{
    cout << "LanguageDisplayCommands::OnCmdGetSupportedDisplayLanguages" << endl;
    LanguageDisplayIntfControllee* intfControllee = static_cast<LanguageDisplayCommands*>(commands)->GetInterface();

    if (!intfControllee) {
        cout << "Interface is not exist." << endl;
        return;
    }

    const std::vector<qcc::String> supportedDisplayLanguages = intfControllee->GetSupportedDisplayLanguages();

    for(size_t i = 0; i < supportedDisplayLanguages.size(); i++)
        cout << supportedDisplayLanguages[i].c_str() << endl;
    cout << endl;
}