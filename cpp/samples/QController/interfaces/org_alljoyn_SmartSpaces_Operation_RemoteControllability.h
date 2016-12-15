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

#ifndef org_alljoyn_SmartSpaces_Operation_RemoteControllability_H_
#define org_alljoyn_SmartSpaces_Operation_RemoteControllability_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/RemoteControllabilityInterface.h>
#include <interfaces/controller/operation/RemoteControllabilityIntfController.h>
#include <interfaces/controller/operation/RemoteControllabilityIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_RemoteControllability : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_RemoteControllability(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_RemoteControllability();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetIsControllable(QStatus status, const bool value);
    void slotOnIsControllableChanged(const bool value);

public:
    // ajn::services::RemoteControllabilityIntfControllerListener
    class Listener: public ajn::services::RemoteControllabilityIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetIsControllable(QStatus status, const qcc::String& objectPath, const bool value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetIsControllable", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(bool, value)
                              );
        }
        virtual void OnIsControllableChanged(const qcc::String& objectPath, const bool value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnIsControllableChanged", Qt::QueuedConnection,
                              Q_ARG(bool, value)
                              );
        }
    };

private:
    Ref<ajn::services::RemoteControllabilityIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_IsControllable;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_RemoteControllability_H_ */