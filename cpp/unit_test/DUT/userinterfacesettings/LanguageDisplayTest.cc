/******************************************************************************
 * 
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 * 
 *    SPDX-License-Identifier: Apache-2.0
 * 
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 * 
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 * 
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "CdmTest.h"
#include <algorithm>

#include <interfaces/controller/userinterfacesettings/LanguageDisplayIntfController.h>
#include <interfaces/controller/userinterfacesettings/LanguageDisplayIntfControllerListener.h>

class LanguageDisplayListener : public LanguageDisplayIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;

    qcc::String m_displayLanguage;
    qcc::String m_displayLanguageSignal;

    qcc::String m_errorName;
    qcc::String m_errorMessage;

    std::vector<qcc::String> m_supportedDisplayLanguages;
    std::vector<qcc::String> m_supportedDisplayLanguagesSignal;

    virtual void OnResponseGetDisplayLanguage(QStatus status, const qcc::String& objectPath, const qcc::String& displayLanguage, void* context) override
    {
        m_displayLanguage = displayLanguage;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseSetDisplayLanguage(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedDisplayLanguages(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages, void* context) override
    {
        m_supportedDisplayLanguages = supportedDisplayLanguages;
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnDisplayLanguageChanged(const qcc::String& objectPath, const qcc::String& displayLanguage) override
    {
        m_displayLanguageSignal = displayLanguage;
        m_eventSignal.SetEvent();
    }

    virtual void OnSupportedDisplayLanguagesChanged(const qcc::String& objectPath, const std::vector<qcc::String>& supportedDisplayLanguages) override
    {
        m_supportedDisplayLanguagesSignal = supportedDisplayLanguages;
        m_eventSignal.SetEvent();
    }

    // QStatus GetUnselectableLevel(uint8_t& unselectableLevel)
    // {
    //     for(uint8_t i = 0; i <= m_maxLevel; i++)
    //     {
    //         std::vector<uint8_t>::iterator it;
    //         it = std::find(m_selectableLevels.begin(),m_selectableLevels.end(), i);
    //         if(it == m_selectableLevels.end())
    //         {
    //             unselectableLevel = i;
    //             return ER_OK;
    //         }
    //     }
    //     return ER_FAIL;
    // }
};

TEST_F(CDMTest, CDM_v1_LanguageDisplay)
{
    WaitForControllee(LANGUAGE_DISPLAY_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<LanguageDisplayListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay", m_interfaces[i].busName, qcc::String(m_interfaces[i].objectPath.c_str()),
                                                                m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<LanguageDisplayIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the DisplayLanguage property.");
            status = controller->GetDisplayLanguage();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve SupportedDisplayLanguages property.");
            status = controller->GetSupportedDisplayLanguages();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
        }

        const qcc::String initDisplayLanguage = listener->m_supportedDisplayLanguages[0];
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Set the DisplayLanguage property to the 1st item of the SupportedDisplayLanguages.");
            if (listener->m_displayLanguage != initDisplayLanguage) {
                status = controller->SetDisplayLanguage(initDisplayLanguage);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_displayLanguageSignal, initDisplayLanguage);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("Set the DisplayLanguage property to \"unknown\" value.");
            qcc::String unsupportedDisplayLanguage("unknown");
            if(status == ER_OK)
            {
                status = controller->SetDisplayLanguage(unsupportedDisplayLanguage);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_NE(listener->m_status, ER_OK);

                TEST_LOG_2("Get the DisplayLanguage property.");
                status = controller->GetDisplayLanguage();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_displayLanguage, initDisplayLanguage);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("If SupportedDisplayLanguages > 1, set the DisplayLanguage property to the 2nd item of the SupportedDisplayLanguages.");
            if (listener->m_supportedDisplayLanguages.size() > 1) {
                const qcc::String validDisplayLanguage = listener->m_supportedDisplayLanguages[1];
                status = controller->SetDisplayLanguage(validDisplayLanguage);

                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the TargetLevel property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT)) << "property changed signal is missing";
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_displayLanguageSignal, validDisplayLanguage);

                TEST_LOG_3("Get the DisplayLanguage property.");
                status = controller->GetDisplayLanguage();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_displayLanguage, validDisplayLanguage);
            }
        }
    }
}
