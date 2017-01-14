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
#include "org_alljoyn_SmartSpaces_Operation_Color.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Color*>();



org_alljoyn_SmartSpaces_Operation_Color::org_alljoyn_SmartSpaces_Operation_Color(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>Hue</b>"));
    // Create the editing widget for Hue
    edit_Hue = new QLineEdit();
    edit_Hue->setToolTip("Hue of the device.");
    QObject::connect(edit_Hue, SIGNAL(returnPressed()), this, SLOT(slotSetHue()));

    layout->addWidget(edit_Hue);
    layout->addWidget(new QLabel("<b>Saturation</b>"));
    // Create the editing widget for Saturation
    edit_Saturation = new QLineEdit();
    edit_Saturation->setToolTip("Saturation of the device.");
    QObject::connect(edit_Saturation, SIGNAL(returnPressed()), this, SLOT(slotSetSaturation()));

    layout->addWidget(edit_Saturation);

    messages_ = new QLabel();
    layout->addWidget(messages_);

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
        qWarning() << "Color getting properties";

        status = controller->GetHue();
        if (status != ER_OK)
        {
            qWarning() << "Color::fetchProperties Failed to get Hue" << QCC_StatusText(status);
        }

        status = controller->GetSaturation();
        if (status != ER_OK)
        {
            qWarning() << "Color::fetchProperties Failed to get Saturation" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseGetHue(QStatus status, const double value)
{
    qWarning() << "Color::slotOnResponseGetHue";

    edit_Hue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnHueChanged(const double value)
{
    qWarning() << "Color::slotOnHueChanged";

    edit_Hue->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseSetHue(QStatus status)
{
    qWarning() << "Color::slotOnResponseSetHue";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set Hue", status);
        qWarning() << "Color::slotOnResponseSetHue Failed to set Hue" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_Color::slotSetHue()
{
    qWarning() << "Color::slotSetHue";

    bool ok = false;
    double value;
    QString str = edit_Hue->text();
    value = QStringTo<double>(str, &ok);
    if (!ok)
    {
        qWarning() << "Color::slotSetHue Failed to convert '" << str << "' to double";
    }

    if (ok)
    {
        QStatus status = controller->SetHue(value);

        if (status != ER_OK)
        {
            qWarning() << "Color::slotSetHue Failed to get Hue" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseGetSaturation(QStatus status, const double value)
{
    qWarning() << "Color::slotOnResponseGetSaturation";

    edit_Saturation->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnSaturationChanged(const double value)
{
    qWarning() << "Color::slotOnSaturationChanged";

    edit_Saturation->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Color::slotOnResponseSetSaturation(QStatus status)
{
    qWarning() << "Color::slotOnResponseSetSaturation";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set Saturation", status);
        qWarning() << "Color::slotOnResponseSetSaturation Failed to set Saturation" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_Color::slotSetSaturation()
{
    qWarning() << "Color::slotSetSaturation";

    bool ok = false;
    double value;
    QString str = edit_Saturation->text();
    value = QStringTo<double>(str, &ok);
    if (!ok)
    {
        qWarning() << "Color::slotSetSaturation Failed to convert '" << str << "' to double";
    }

    if (ok)
    {
        QStatus status = controller->SetSaturation(value);

        if (status != ER_OK)
        {
            qWarning() << "Color::slotSetSaturation Failed to get Saturation" << QCC_StatusText(status);
        }
    }
}
