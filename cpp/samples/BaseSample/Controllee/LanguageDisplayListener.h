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

#ifndef LANGUAGEDISPLAYLISTENER_H_
#define LANGUAGEDISPLAYLISTENER_H_

#include "InterfaceCommands.h"
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControllee.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControlleeListener.h>

using namespace ajn;
using namespace services;

class LanguageDisplayListener : public LanguageDisplayIntfControlleeListener
{
  public:

    virtual QStatus OnSetDisplayLanguage(const qcc::String& displayLanguage);

    virtual QStatus OnGetDisplayLanguage(qcc::String& displayLanguage);

    virtual QStatus OnGetSupportedDisplayLanguages(std::vector<qcc::String>& supportedDisplayLanguages);

};

class LanguageDisplayCommands : public InterfaceCommands
{
  public:
    static ControlleeCommands* CreateCommands(ControlleeSample* sample, const char* objectPath);

    LanguageDisplayCommands(ControlleeSample* sample, const char* objectPath);
    virtual ~LanguageDisplayCommands();

    virtual void Init();
    virtual void InitializeProperties();

    LanguageDisplayIntfControllee* GetInterface() { return m_intfControllee; }
    static void OnCmdGetDisplayLanguage(Commands* commands, std::string& cmd);
    static void OnCmdSetDisplayLanguage(Commands* commands, std::string& cmd);

    static void OnCmdGetSupportedDisplayLanguages(Commands* commands, std::string& cmd);

  private:
    LanguageDisplayIntfControllee* m_intfControllee;
    LanguageDisplayListener m_listener;
};




#endif /* LANGUAGEDISPLAYLISTENER_H_ */