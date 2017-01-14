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
#include "org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay*>();



org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>DisplayLanguage</b>"));
    // Create the editing widget for DisplayLanguage
    edit_DisplayLanguage = new QLineEdit();
    edit_DisplayLanguage->setToolTip("The RFC 5646 tag of the current language being used by the device user interface");
    QObject::connect(edit_DisplayLanguage, SIGNAL(returnPressed()), this, SLOT(slotSetDisplayLanguage()));

    layout->addWidget(edit_DisplayLanguage);
    layout->addWidget(new QLabel("<b>SupportedDisplayLanguages</b>"));
    // Create the editing widget for SupportedDisplayLanguages
    edit_SupportedDisplayLanguages = new QLabel();

    layout->addWidget(edit_SupportedDisplayLanguages);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<LanguageDisplayIntfController>(m_listener);
        if (controller)
        {
            fetchProperties();
        }
        else
        {
            qWarning() << __FUNCTION__ << " No interface controller available!";
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << " No interface available!";
    }
}

org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::~org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "LanguageDisplay getting properties";

        status = controller->GetDisplayLanguage();
        if (status != ER_OK)
        {
            qWarning() << "LanguageDisplay::fetchProperties Failed to get DisplayLanguage" << QCC_StatusText(status);
        }

        status = controller->GetSupportedDisplayLanguages();
        if (status != ER_OK)
        {
            qWarning() << "LanguageDisplay::fetchProperties Failed to get SupportedDisplayLanguages" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnResponseGetDisplayLanguage(QStatus status, const qcc::String& value)
{
    qWarning() << "LanguageDisplay::slotOnResponseGetDisplayLanguage";

    edit_DisplayLanguage->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnDisplayLanguageChanged(const qcc::String& value)
{
    qWarning() << "LanguageDisplay::slotOnDisplayLanguageChanged";

    edit_DisplayLanguage->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnResponseSetDisplayLanguage(QStatus status)
{
    qWarning() << "LanguageDisplay::slotOnResponseSetDisplayLanguage";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set DisplayLanguage", status);
        qWarning() << "LanguageDisplay::slotOnResponseSetDisplayLanguage Failed to set DisplayLanguage" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotSetDisplayLanguage()
{
    qWarning() << "LanguageDisplay::slotSetDisplayLanguage";

    bool ok = false;
    qcc::String value;
    QString str = edit_DisplayLanguage->text();
    value = QStringTo<qcc::String>(str, &ok);
    if (!ok)
    {
        qWarning() << "LanguageDisplay::slotSetDisplayLanguage Failed to convert '" << str << "' to qcc::String";
    }

    if (ok)
    {
        QStatus status = controller->SetDisplayLanguage(value);

        if (status != ER_OK)
        {
            qWarning() << "LanguageDisplay::slotSetDisplayLanguage Failed to get DisplayLanguage" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnResponseGetSupportedDisplayLanguages(QStatus status, const std::vector<qcc::String>& value)
{
    qWarning() << "LanguageDisplay::slotOnResponseGetSupportedDisplayLanguages";

    edit_SupportedDisplayLanguages->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnSupportedDisplayLanguagesChanged(const std::vector<qcc::String>& value)
{
    qWarning() << "LanguageDisplay::slotOnSupportedDisplayLanguagesChanged";

    edit_SupportedDisplayLanguages->setText(QStringFrom(value));
}



