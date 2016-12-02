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

#include "LanguageDisplayCommands.h"
#include "ControllerSample.h"

LanguageDisplayListener::LanguageDisplayListener()
{
}

LanguageDisplayListener::~LanguageDisplayListener()
{
}

void LanguageDisplayListener::OnResponseGetDisplayLanguage(QStatus status, const qcc::String& objectPath, const qcc::String displayLanguage, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayLanguage: " << displayLanguage.c_str() << endl;
}
void LanguageDisplayListener::OnResponseSetDisplayLanguage(QStatus status, const qcc::String& objectPath, void* context)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# status: " << QCC_StatusText(status) << endl;
}
void LanguageDisplayListener::OnResponseGetSupportedDisplayLanguages(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages, void* context)
{
    cout << "# "<< __func__ << endl;
    cout << "# objectPath: " << objectPath << endl;
    cout << "# supported temperature units: " << endl;
    for (size_t i = 0; i < supportedDisplayLanguages.size(); ++i) {
        cout << supportedDisplayLanguages[i].c_str() << endl;
    }
}
void LanguageDisplayListener::OnDisplayLanguageChanged(const qcc::String& objectPath, const qcc::String& displayLanguage)
{
    cout << __func__ << endl;
    cout << "# path: " << objectPath << endl;
    cout << "# DisplayLanguage: " << displayLanguage.c_str() << endl;

}
void LanguageDisplayListener::OnSupportedDisplayLanguagesChanged(const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages)
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

