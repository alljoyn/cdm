/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
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

#include <interfaces/controller/operation/AudioVideoInputIntfController.h>
#include <interfaces/controller/operation/AudioVideoInputIntfControllerListener.h>

class AudioVideoInputListener : public AudioVideoInputIntfControllerListener
{
public:
    CdmSemaphore m_event;
    CdmSemaphore m_eventSignal;
    QStatus m_status;
    AudioVideoInputInterface::SourceType m_inputSourceId;
    std::vector<AudioVideoInputInterface::InputSource> m_supportedInputSources;
    uint16_t m_inputSourceIdSignal;
    std::vector<AudioVideoInputInterface::InputSource> m_supportedInputSourcesSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetInputSourceId(QStatus status, const qcc::String& objectPath, void* context) override
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetInputSourceId(QStatus status, const qcc::String& objectPath, const AudioVideoInputInterface::SourceType inputSourceId, void* context) override
    {
        m_status = status;
        m_inputSourceId = inputSourceId;
        m_event.SetEvent();
    }

    virtual void OnResponseGetSupportedInputSources(QStatus status, const qcc::String& objectPath,
                                                    const std::vector<AudioVideoInputInterface::InputSource>& supportedInputSources, void* context) override
    {
        m_status = status;
        m_supportedInputSources = supportedInputSources;
        m_event.SetEvent();
    }

    virtual void OnInputSourceIdChanged(const qcc::String& objectPath, const AudioVideoInputInterface::SourceType inputSourceId) override
    {
        m_inputSourceIdSignal = inputSourceId;
        m_eventSignal.SetEvent();
    }

    virtual void OnSupportedInputSourcesChanged(const qcc::String& objectPath, const std::vector<AudioVideoInputInterface::InputSource>& supportedInputSources) override
    {
        m_supportedInputSourcesSignal = supportedInputSources;
        m_eventSignal.SetEvent();
    }
};


static bool hasSourceId(AudioVideoInputInterface::SourceType id, const std::vector<AudioVideoInputInterface::InputSource>& supportedInputSources)
{
    for (size_t i = 0; i < supportedInputSources.size(); ++i) {
        if (supportedInputSources[i].sourceType == id) {
            return true;
        }
    }
    return false;
}


static AudioVideoInputInterface::SourceType findInvalidInputSourceId(const std::vector<AudioVideoInputInterface::InputSource>& supportedInputSources)
{
    // Find an id that isn't in the supported list
    uint16_t invalidInputSourceId = 0;

    while (invalidInputSourceId != (uint16_t) -1) {
        if (!hasSourceId((AudioVideoInputInterface::SourceType)invalidInputSourceId, supportedInputSources)) {
            return (AudioVideoInputInterface::SourceType)invalidInputSourceId;
        }
        invalidInputSourceId++;
    }
    return (AudioVideoInputInterface::SourceType) -1;
}



TEST_F(CDMTest, CDM_v1_AudioVideoInput)
{
    WaitForControllee(AUDIO_VIDEO_INPUT_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        auto listener = mkRef<AudioVideoInputListener>();
        auto interface = m_controller->CreateInterface("org.alljoyn.SmartSpaces.Operation.AudioVideoInput", m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        auto controller = std::dynamic_pointer_cast<AudioVideoInputIntfController>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties.");
        {
            TEST_LOG_2("Retrieve the InputSourceId property.");
            status = controller->GetInputSourceId();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);

            TEST_LOG_2("Retrieve the SupportedInputSources property.");
            status = controller->GetSupportedInputSources();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            ASSERT_NE((int)listener->m_supportedInputSources.size(), 0);
        }

        std::vector<AudioVideoInputInterface::SourceType> sourceIds;
        auto itr = listener->m_supportedInputSources.begin();
        auto end = listener->m_supportedInputSources.end();
        while (itr != end) {
            sourceIds.push_back(itr->sourceType);
            itr++;
        }

        auto initSourceId = sourceIds[0];
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the InputSourceId property to the 1st item of the SupportedInputSources");
            if (listener->m_inputSourceId != initSourceId) {
                status = controller->SetInputSourceId(initSourceId);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT));
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_inputSourceIdSignal, initSourceId);
            }
        }

        TEST_LOG_1("Set properties to invalid value");
        {
            TEST_LOG_2("Set the InputSourceId property to an invalid value.");
            auto invalidInputSourceId = findInvalidInputSourceId(listener->m_supportedInputSources);
            status = controller->SetInputSourceId(invalidInputSourceId);
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_NE(listener->m_status, ER_OK);

            TEST_LOG_2("Get the InputSourceId property");
            status = controller->GetInputSourceId();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
            listener->m_event.ResetEvent();
            EXPECT_EQ(listener->m_status, ER_OK);
            EXPECT_EQ(listener->m_inputSourceId, initSourceId);
        }

        TEST_LOG_1("Set properties to valid value");
        {
            TEST_LOG_2("If size of the SupportedInputSources is not 1, set InputSourceId property to 2nd item of SupportedInputSources.");
            if (listener->m_supportedInputSources.size() > 1) {
                auto secondSourceId = sourceIds[1];
                status = controller->SetInputSourceId(secondSourceId);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the InputSourceId property.");
                EXPECT_EQ(true, listener->m_eventSignal.Wait(TIMEOUT));
                listener->m_eventSignal.ResetEvent();
                EXPECT_EQ(listener->m_inputSourceIdSignal, secondSourceId);

                TEST_LOG_3("Get the InputSourceId property");
                status = controller->GetInputSourceId();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(true, listener->m_event.Wait(TIMEOUT));
                listener->m_event.ResetEvent();
                EXPECT_EQ(listener->m_status, ER_OK);
                EXPECT_EQ(listener->m_inputSourceId, secondSourceId);
            }
        }
    }
}