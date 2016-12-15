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

#include "org_alljoyn_SmartSpaces_Operation_Color.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Color*>();


org_alljoyn_SmartSpaces_Operation_Color::org_alljoyn_SmartSpaces_Operation_Color(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("Hue"));
    // Create line edit for Hue
    edit_Hue = new QLineEdit();
    edit_Hue->setToolTip("Hue of the device.");
    edit_Hue->setReadOnly(false);
    QObject::connect(edit_Hue, SIGNAL(returnPressed()), this, SLOT(slotSetHue()));
    layout->addWidget(edit_Hue);
    layout->addWidget(new QLabel("Saturation"));
    // Create line edit for Saturation
    edit_Saturation = new QLineEdit();
    edit_Saturation->setToolTip("Saturation of the device.");
    edit_Saturation->setReadOnly(false);
    QObject::connect(edit_Saturation, SIGNAL(returnPressed()), this, SLOT(slotSetSaturation()));
    layout->addWidget(edit_Saturation);

    if (iface)
    {
        controller = iface->CreateInterface<ColorIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_Color::~org_alljoyn_SmartSpaces_Operation_Color()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_Color::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_SmartSpaces_Operation_Color getting properties";

        status = controller->GetHue();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Hue" << QCC_StatusText(status);
        }

        status = controller->GetSaturation();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Saturation" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseGetHue(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Hue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Color::slotOnHueChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Hue->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseSetHue(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_Color::slotSetHue()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Hue->text();
    double value = QStringTo<double>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetHue(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Hue" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to double";
    }
}




void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseGetSaturation(QStatus status, const double value)
{
    qWarning() << __FUNCTION__;
    edit_Saturation->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Color::slotOnSaturationChanged(const double value)
{
    qWarning() << __FUNCTION__;
    edit_Saturation->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseSetSaturation(QStatus status)
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_Color::slotSetSaturation()
{
    qWarning() << __FUNCTION__;

    bool ok = false;
    QString str = edit_Saturation->text();
    double value = QStringTo<double>(str, &ok);
    if (ok)
    {
        QStatus status = controller->SetSaturation(value);
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get Saturation" << QCC_StatusText(status);
        }
    }
    else
    {
        qWarning() << __FUNCTION__ << "Failed to convert '" << str << "' to double";
    }
}
