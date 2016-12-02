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

#include "CdmTest.h"

#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllerListener.h>

class AudioVolumeListener : public AudioVolumeIntfControllerListener
{
public:
    qcc::Event m_event;
    qcc::Event m_eventSignal;
    QStatus m_status;
    uint8_t m_volume;
    uint8_t m_maxVolume;
    bool m_mute;
    uint8_t m_volumeSignal;
    uint8_t m_maxVolumeSignal;
    bool m_muteSignal;
    qcc::String m_errorName;
    qcc::String m_errorMessage;

    virtual void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t volume, void* context)
    {
        m_status = status;
        m_volume = volume;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t maxVolume, void* context)
    {
        m_status = status;
        m_maxVolume = maxVolume;
        m_event.SetEvent();
    }

    virtual void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context)
    {
        m_status = status;
        m_event.SetEvent();
    }

    virtual void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool mute, void* context)
    {
        m_status = status;
        m_mute = mute;
        m_event.SetEvent();
    }

    virtual void OnVolumeChanged(const qcc::String& objectPath, const uint8_t volume)
    {
        m_volumeSignal = volume;
        m_eventSignal.SetEvent();
    }

    virtual void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t maxVolume)
    {
        m_maxVolumeSignal = maxVolume;
        m_eventSignal.SetEvent();
    }

    virtual void OnMuteChanged(const qcc::String& objectPath, const bool mute)
    {
        m_muteSignal = mute;
        m_eventSignal.SetEvent();
    }
};

TEST_F(CDMTest, CDM_v1_AudioVolume)
{
    WaitForControllee(AUDIO_VOLUME_INTERFACE);
    for (size_t i = 0; i < m_interfaces.size(); i++) {
        TEST_LOG_OBJECT_PATH(m_interfaces[i].objectPath);

        AudioVolumeListener listener;
        CdmInterface* interface = m_controller->CreateInterface(AUDIO_VOLUME_INTERFACE, m_interfaces[i].busName,
                                                                qcc::String(m_interfaces[i].objectPath.c_str()), m_interfaces[i].sessionId, listener);
        AudioVolumeIntfController* controller = static_cast<AudioVolumeIntfController*>(interface);
        QStatus status = ER_FAIL;

        TEST_LOG_1("Get initial values for all properties");
        {
            TEST_LOG_2("Retieve the Volume property.");
            status = controller->GetVolume();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retieve the MaxVolume property.");
            status = controller->GetMaxVolume();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);

            TEST_LOG_2("Retieve the Mute property.");
            status = controller->GetMute();
            EXPECT_EQ(status, ER_OK);
            EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
            listener.m_event.ResetEvent();
            EXPECT_EQ(listener.m_status, ER_OK);
        }

        const uint8_t initVolume = 0;
        const bool initMute = false;
        TEST_LOG_1("Initialize all read-write properties.");
        {
            TEST_LOG_2("Initialize the Volume property to 0.");
            if (listener.m_volume != initVolume) {
                status = controller->SetVolume(initVolume);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_volumeSignal, initVolume);
            }

            TEST_LOG_2("Initialize the Mute property to false.");
            if (listener.m_mute != initMute) {
                status = controller->SetMute(initMute);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_muteSignal, initMute);
            }
        }

        TEST_LOG_1("Set properties to valid value.");
        {
            TEST_LOG_2("Set the Volume property to value 1.");
            {
                const uint8_t validValue = 1;
                status = controller->SetVolume(validValue);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Volume property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_volumeSignal, validValue);

                TEST_LOG_3("Get the Volume property.");
                status = controller->GetVolume();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_volume, validValue);
            }

            TEST_LOG_2("Set the Mute property to true.");
            {
                const bool validMute = true;
                status = controller->SetMute(validMute);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Mute property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_muteSignal, validMute);

                TEST_LOG_3("Get the Mute property.");
                status = controller->GetMute();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_mute, validMute);
            }
        }

        TEST_LOG_1("Set properties to invalid value.");
        {
            TEST_LOG_2("If MaxVolume != UINT8_MAX, Set the Volume property to MaxVolume + 1.");
            if (listener.m_maxVolume != UINT8_MAX) {
                const uint16_t invalidVolume = listener.m_maxVolume + 1;
                status = controller->SetVolume(invalidVolume);
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);

                TEST_LOG_3("Wait the PropertiesChanged signal for the Volume property.");
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_eventSignal, TIMEOUT));
                listener.m_eventSignal.ResetEvent();
                EXPECT_EQ(listener.m_volumeSignal, listener.m_maxVolume);

                TEST_LOG_3("Get the Volume property.");
                status = controller->GetVolume();
                EXPECT_EQ(status, ER_OK);
                EXPECT_EQ(ER_OK, qcc::Event::Wait(listener.m_event, TIMEOUT));
                listener.m_event.ResetEvent();
                EXPECT_EQ(listener.m_status, ER_OK);
                EXPECT_EQ(listener.m_volume, listener.m_maxVolume);
            }
        }
    }
}