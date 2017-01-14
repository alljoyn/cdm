/******************************************************************************
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

#ifndef org_alljoyn_SmartSpaces_Operation_AudioVolume_H_
#define org_alljoyn_SmartSpaces_Operation_AudioVolume_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/AudioVolumeInterface.h>
#include <interfaces/controller/operation/AudioVolumeIntfController.h>
#include <interfaces/controller/operation/AudioVolumeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_AudioVolume : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_AudioVolume(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_AudioVolume();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetVolume(QStatus status, const uint8_t value);
    void slotOnVolumeChanged(const uint8_t value);
    void slotOnResponseSetVolume(QStatus status);
    void slotSetVolume();
    void slotOnResponseGetMaxVolume(QStatus status, const uint8_t value);
    void slotOnMaxVolumeChanged(const uint8_t value);
    void slotOnResponseGetMute(QStatus status, const bool value);
    void slotOnMuteChanged(const bool value);
    void slotOnResponseSetMute(QStatus status);
    void slotSetMute();

public:
    // ajn::services::AudioVolumeIntfControllerListener
    class Listener: public ajn::services::AudioVolumeIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << "AudioVolume::OnResponseGetVolume";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetVolume", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnVolumeChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << "AudioVolume::OnVolumeChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnVolumeChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "AudioVolume::OnResponseSetVolume";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetVolume", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << "AudioVolume::OnResponseGetMaxVolume";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxVolume", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << "AudioVolume::OnMaxVolumeChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnMaxVolumeChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << "AudioVolume::OnResponseGetMute";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMute", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnMuteChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << "AudioVolume::OnMuteChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnMuteChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "AudioVolume::OnResponseSetMute";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetMute", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::AudioVolumeIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_Volume;
    QLabel* edit_MaxVolume;
    QCheckBox* edit_Mute;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_AudioVolume_H_ */
