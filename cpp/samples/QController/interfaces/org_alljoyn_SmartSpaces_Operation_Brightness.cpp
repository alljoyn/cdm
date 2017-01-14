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
#include "org_alljoyn_SmartSpaces_Operation_Brightness.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Brightness*>();



org_alljoyn_SmartSpaces_Operation_Brightness::org_alljoyn_SmartSpaces_Operation_Brightness(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>Brightness</b>"));
    // Create the editing widget for Brightness
    edit_Brightness = new QLineEdit();
    edit_Brightness->setToolTip("Brightness of the device.");
    QObject::connect(edit_Brightness, SIGNAL(returnPressed()), this, SLOT(slotSetBrightness()));

    layout->addWidget(edit_Brightness);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<BrightnessIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_Brightness::~org_alljoyn_SmartSpaces_Operation_Brightness()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_Brightness::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "Brightness getting properties";

        status = controller->GetBrightness();
        if (status != ER_OK)
        {
            qWarning() << "Brightness::fetchProperties Failed to get Brightness" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Brightness::slotOnResponseGetBrightness(QStatus status, const double value)
{
    qWarning() << "Brightness::slotOnResponseGetBrightness";

    edit_Brightness->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Brightness::slotOnBrightnessChanged(const double value)
{
    qWarning() << "Brightness::slotOnBrightnessChanged";

    edit_Brightness->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Brightness::slotOnResponseSetBrightness(QStatus status)
{
    qWarning() << "Brightness::slotOnResponseSetBrightness";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set Brightness", status);
        qWarning() << "Brightness::slotOnResponseSetBrightness Failed to set Brightness" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_Brightness::slotSetBrightness()
{
    qWarning() << "Brightness::slotSetBrightness";

    bool ok = false;
    double value;
    QString str = edit_Brightness->text();
    value = QStringTo<double>(str, &ok);
    if (!ok)
    {
        qWarning() << "Brightness::slotSetBrightness Failed to convert '" << str << "' to double";
    }

    if (ok)
    {
        QStatus status = controller->SetBrightness(value);

        if (status != ER_OK)
        {
            qWarning() << "Brightness::slotSetBrightness Failed to get Brightness" << QCC_StatusText(status);
        }
    }
}
