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

#ifndef org_alljoyn_SmartSpaces_Operation_ResourceSaving_H_
#define org_alljoyn_SmartSpaces_Operation_ResourceSaving_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/ResourceSavingInterface.h>
#include <interfaces/controller/operation/ResourceSavingIntfController.h>
#include <interfaces/controller/operation/ResourceSavingIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_ResourceSaving : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_ResourceSaving(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_ResourceSaving();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetResourceSavingMode(QStatus status, const bool value);
    void slotOnResourceSavingModeChanged(const bool value);
    void slotOnResponseSetResourceSavingMode(QStatus status);
    void slotSetResourceSavingMode();

public:
    // ajn::services::ResourceSavingIntfControllerListener
    class Listener: public ajn::services::ResourceSavingIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetResourceSavingMode(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetResourceSavingMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnResourceSavingModeChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResourceSavingModeChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnResponseSetResourceSavingMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetResourceSavingMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
    };

private:
    Ref<ajn::services::ResourceSavingIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_ResourceSavingMode;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_ResourceSaving_H_ */