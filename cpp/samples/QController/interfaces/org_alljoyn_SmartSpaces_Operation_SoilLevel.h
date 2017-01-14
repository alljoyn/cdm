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

#ifndef org_alljoyn_SmartSpaces_Operation_SoilLevel_H_
#define org_alljoyn_SmartSpaces_Operation_SoilLevel_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/SoilLevelInterface.h>
#include <interfaces/controller/operation/SoilLevelIntfController.h>
#include <interfaces/controller/operation/SoilLevelIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_SoilLevel : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_SoilLevel(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_SoilLevel();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMaxLevel(QStatus status, const uint8_t value);
    void slotOnMaxLevelChanged(const uint8_t value);
    void slotOnResponseGetTargetLevel(QStatus status, const uint8_t value);
    void slotOnTargetLevelChanged(const uint8_t value);
    void slotOnResponseSetTargetLevel(QStatus status);
    void slotSetTargetLevel();
    void slotOnResponseGetSelectableLevels(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSelectableLevelsChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::SoilLevelIntfControllerListener
    class Listener: public ajn::services::SoilLevelIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << "SoilLevel::OnResponseGetMaxLevel";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMaxLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << "SoilLevel::OnMaxLevelChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnMaxLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << "SoilLevel::OnResponseGetTargetLevel";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetTargetLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << "SoilLevel::OnTargetLevelChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnTargetLevelChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "SoilLevel::OnResponseSetTargetLevel";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetTargetLevel", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSelectableLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) override
        {
            qWarning() << "SoilLevel::OnResponseGetSelectableLevels";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSelectableLevels", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
        virtual void OnSelectableLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) override
        {
            qWarning() << "SoilLevel::OnSelectableLevelsChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnSelectableLevelsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
    };

private:
    Ref<ajn::services::SoilLevelIntfController> controller;
    Ref<Listener> m_listener;


    QLabel* edit_MaxLevel;
    QLineEdit* edit_TargetLevel;
    QLabel* edit_SelectableLevels;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_SoilLevel_H_ */
