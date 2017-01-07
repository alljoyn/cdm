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

#ifndef org_alljoyn_Input_Hid_H_
#define org_alljoyn_Input_Hid_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/input/HidInterface.h>
#include <interfaces/controller/input/HidIntfController.h>
#include <interfaces/controller/input/HidIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_Input_Hid : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_Input_Hid(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_Input_Hid();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickInjectEvents();

    void slotOnResponseGetSupportedEvents(QStatus status, const std::vector<HidInterface::SupportedInputEvent>& value);
    void slotOnSupportedEventsChanged(const std::vector<HidInterface::SupportedInputEvent>& value);
    void slotOnResponseMethodInjectEvents(QStatus status, const QString& errorName);

public:
    // ajn::services::HidIntfControllerListener
    class Listener: public ajn::services::HidIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetSupportedEvents(QStatus status, const qcc::String& objectPath, const std::vector<HidInterface::SupportedInputEvent>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedEvents", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<HidInterface::SupportedInputEvent>, value)
                              );
        }
        virtual void OnSupportedEventsChanged(const qcc::String& objectPath, const std::vector<HidInterface::SupportedInputEvent>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedEventsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<HidInterface::SupportedInputEvent>, value)
                              );
        }
        virtual void OnResponseInjectEvents(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodInjectEvents", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(QString, QString(errorName))
                              );
        }
    };

private:
    Ref<ajn::services::HidIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_InjectEvents;

    QLineEdit* edit_SupportedEvents;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_Input_Hid_H_ */
