/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef org_alljoyn_SmartSpaces_Operation_Channel_H_
#define org_alljoyn_SmartSpaces_Operation_Channel_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/ChannelInterface.h>
#include <interfaces/controller/operation/ChannelIntfController.h>
#include <interfaces/controller/operation/ChannelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_Channel : public QWidget
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
    void slotOnResponseMethodGetChannelList(QStatus status, const QString& errorName);
    void slotOnSignalChannelListChanged();

public:
    // ajn::services::ChannelIntfControllerListener
    class Listener: public ajn::services::ChannelIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetChannelId(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetChannelId", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnChannelIdChanged(const qcc::String& objectPath, const qcc::String& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnChannelIdChanged", Qt::QueuedConnection,
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnResponseSetChannelId(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetChannelId", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetTotalNumberOfChannels(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTotalNumberOfChannels", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnTotalNumberOfChannelsChanged(const qcc::String& objectPath, const uint16_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnTotalNumberOfChannelsChanged", Qt::QueuedConnection,
                              Q_ARG(uint16_t, value)
                              );
        }
        virtual void OnResponseGetChannelList(QStatus status, const qcc::String& objectPath, const std::vector<ChannelInterface::ChannelInfoRecord>& listOfChannelInfoRecords, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodGetChannelList", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
        virtual void OnChannelListChanged(const qcc::String& objectPath) override
        {
            QMetaObject::invokeMethod(m_widget, "slotOnSignalChannelListChanged", Qt::QueuedConnection);
        }
    };

private:
    Ref<ajn::services::ChannelIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_GetChannelList;

    QLineEdit* edit_ChannelId;
    QLineEdit* edit_TotalNumberOfChannels;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_Channel_H_ */