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

#ifndef org_alljoyn_SmartSpaces_Operation_Channel_H_
#define org_alljoyn_SmartSpaces_Operation_Channel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/ChannelInterface.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfController.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Channel : public QWidget, public ajn::services::ChannelIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_Channel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_Channel();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickGetChannelList();

    void slotOnResponseGetChannelId(QStatus status, const qcc::String& value);
    void slotOnChannelIdChanged(const qcc::String& value);
    void slotOnResponseSetChannelId(QStatus status);
    void slotSetChannelId();
    void slotOnResponseGetTotalNumberOfChannels(QStatus status, const uint16_t value);
    void slotOnTotalNumberOfChannelsChanged(const uint16_t value);

public:
    // ajn::services::ChannelIntfControllerListener
    void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetChannelId", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnChannelIdChanged", Qt::QueuedConnection,
                          Q_ARG(qcc::String, value)
                          );
    }
    void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseSetChannelId", Qt::QueuedConnection,
                          Q_ARG(QStatus, status)
                          );
    }
    void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetTotalNumberOfChannels", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint16_t, value)
                          );
    }
    void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnTotalNumberOfChannelsChanged", Qt::QueuedConnection,
                          Q_ARG(uint16_t, value)
                          );
    }

private:
    ajn::services::ChannelIntfControllerPtr controller;

    QPushButton* button_GetChannelList;

    QLineEdit* edit_ChannelId;
    QLineEdit* edit_TotalNumberOfChannels;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Channel_H_ */
