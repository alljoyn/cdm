/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay*>();


org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("DisplayLanguage"));
    // Create line edit for DisplayLanguage
    edit_DisplayLanguage = new QLineEdit();
    edit_DisplayLanguage->setToolTip("The RFC 5646 tag of the current language being used by the device user interface");
    edit_DisplayLanguage->setReadOnly(false);
    QObject::connect(edit_DisplayLanguage, SIGNAL(returnPressed()), this, SLOT(slotSetDisplayLanguage()));
    layout->addWidget(edit_DisplayLanguage);
    layout->addWidget(new QLabel("SupportedDisplayLanguages"));
    // Create line edit for SupportedDisplayLanguages
    edit_SupportedDisplayLanguages = new QLineEdit();
    edit_SupportedDisplayLanguages->setToolTip("The list of supported languages using RFC 5646 tags");
    edit_SupportedDisplayLanguages->setReadOnly(true);
    layout->addWidget(edit_SupportedDisplayLanguages);

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
        qWarning() << "org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay getting properties";

        status = controller->GetDisplayLanguage();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get DisplayLanguage" << QCC_StatusText(status);
        }

        status = controller->GetSupportedDisplayLanguages();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get SupportedDisplayLanguages" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnResponseGetDisplayLanguage(QStatus status, const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_DisplayLanguage->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnDisplayLanguageChanged(const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_DisplayLanguage->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnResponseSetDisplayLanguage(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotSetDisplayLanguage()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_DisplayLanguage->text();
    qcc::String value = QStringTo<qcc::String>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetDisplayLanguage(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get DisplayLanguage" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to qcc::String";
    }
}




void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnResponseGetSupportedDisplayLanguages(QStatus status, const std::vector<qcc::String>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedDisplayLanguages->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_UserInterfaceSettings_LanguageDisplay::slotOnSupportedDisplayLanguagesChanged(const std::vector<qcc::String>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedDisplayLanguages->setText(QStringFrom(value));
}
