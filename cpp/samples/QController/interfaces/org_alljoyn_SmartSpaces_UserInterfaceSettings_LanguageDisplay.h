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

#ifndef org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay_H_
#define org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/userinterfacesettings/LanguageDisplayInterface.h>
#include <interfaces/controller/userinterfacesettings/LanguageDisplayIntfController.h>
#include <interfaces/controller/userinterfacesettings/LanguageDisplayIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetDisplayLanguage(QStatus status, const qcc::String& value);
    void slotOnDisplayLanguageChanged(const qcc::String& value);
    void slotOnResponseSetDisplayLanguage(QStatus status);
    void slotSetDisplayLanguage();
    void slotOnResponseGetSupportedDisplayLanguages(QStatus status, const std::vector<qcc::String>& value);
    void slotOnSupportedDisplayLanguagesChanged(const std::vector<qcc::String>& value);

public:
    // ajn::services::LanguageDisplayIntfControllerListener
    class Listener: public ajn::services::LanguageDisplayIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetDisplayLanguage(QStatus status, const qcc::String& objectPath, const qcc::String& value, void* context) override
        {
            qWarning() << "LanguageDisplay::OnResponseGetDisplayLanguage";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetDisplayLanguage", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnDisplayLanguageChanged(const qcc::String& objectPath, const qcc::String& value) override
        {
            qWarning() << "LanguageDisplay::OnDisplayLanguageChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnDisplayLanguageChanged", Qt::QueuedConnection,
                              Q_ARG(qcc::String, value)
                              );
        }
        virtual void OnResponseSetDisplayLanguage(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << "LanguageDisplay::OnResponseSetDisplayLanguage";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetDisplayLanguage", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSupportedDisplayLanguages(QStatus status, const qcc::String& objectPath, const std::vector<qcc::String>& value, void* context) override
        {
            qWarning() << "LanguageDisplay::OnResponseGetSupportedDisplayLanguages";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedDisplayLanguages", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<qcc::String>, value)
                              );
        }
        virtual void OnSupportedDisplayLanguagesChanged(const qcc::String& objectPath, const std::vector<qcc::String>& value) override
        {
            qWarning() << "LanguageDisplay::OnSupportedDisplayLanguagesChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedDisplayLanguagesChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<qcc::String>, value)
                              );
        }
    };

private:
    Ref<ajn::services::LanguageDisplayIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_DisplayLanguage;
    QLabel* edit_SupportedDisplayLanguages;

    QLabel* messages_;
    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay_H_ */
