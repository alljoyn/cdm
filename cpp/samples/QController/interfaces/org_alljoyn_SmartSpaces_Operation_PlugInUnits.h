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

#ifndef org_alljoyn_SmartSpaces_Operation_PlugInUnits_H_
#define org_alljoyn_SmartSpaces_Operation_PlugInUnits_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/PlugInUnitsInterface.h>
#include <interfaces/controller/operation/PlugInUnitsIntfController.h>
#include <interfaces/controller/operation/PlugInUnitsIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_PlugInUnits : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_PlugInUnits(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_PlugInUnits();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetPlugInUnits(QStatus status, const std::vector<PlugInUnitsInterface::PlugInInfo>& value);
    void slotOnPlugInUnitsChanged(const std::vector<PlugInUnitsInterface::PlugInInfo>& value);

public:
    // ajn::services::PlugInUnitsIntfControllerListener
    class Listener: public ajn::services::PlugInUnitsIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetPlugInUnits(QStatus status, const qcc::String& objectPath, const std::vector<PlugInUnitsInterface::PlugInInfo>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetPlugInUnits", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<PlugInUnitsInterface::PlugInInfo>, value)
                              );
        }
        virtual void OnPlugInUnitsChanged(const qcc::String& objectPath, const std::vector<PlugInUnitsInterface::PlugInInfo>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnPlugInUnitsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<PlugInUnitsInterface::PlugInInfo>, value)
                              );
        }
    };

private:
    Ref<ajn::services::PlugInUnitsIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_PlugInUnits;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_PlugInUnits_H_ */