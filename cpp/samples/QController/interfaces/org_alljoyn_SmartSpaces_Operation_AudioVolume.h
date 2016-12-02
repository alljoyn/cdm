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

#ifndef org_alljoyn_SmartSpaces_Operation_AudioVolume_H_
#define org_alljoyn_SmartSpaces_Operation_AudioVolume_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/AudioVolumeInterface.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVolumeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_AudioVolume : public QWidget, public ajn::services::AudioVolumeIntfControllerListener
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
    void OnResponseGetVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetVolume", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnVolumeChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnVolumeChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseSetVolume(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetVolume", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetMaxVolume(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxVolume", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnMaxVolumeChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxVolumeChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetMute(QStatus status, const qcc::String& objectPath, const bool value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMute", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(bool, value)
                          );
    }
    void OnMuteChanged(const qcc::String& objectPath, const bool value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMuteChanged", Qt::QueuedConnection,
                          Q_ARG(bool, value)
                          );
    }
    void OnResponseSetMute(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetMute", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }

private:
    ajn::services::AudioVolumeIntfControllerPtr controller;


    QLineEdit* edit_Volume;
    QLineEdit* edit_MaxVolume;
    QLineEdit* edit_Mute;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_AudioVolume_H_ */
