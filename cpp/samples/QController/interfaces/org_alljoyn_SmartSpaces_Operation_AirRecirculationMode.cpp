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
#include "org_alljoyn_SmartSpaces_Operation_AirRecirculationMode.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_AirRecirculationMode*>();



org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::org_alljoyn_SmartSpaces_Operation_AirRecirculationMode(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>IsRecirculating</b>"));
    // Create the editing widget for IsRecirculating
    edit_IsRecirculating = new QCheckBox();
    edit_IsRecirculating->setEnabled(true);
    QObject::connect(edit_IsRecirculating, SIGNAL(stateChanged(int)), this, SLOT(slotSetIsRecirculating()));

    layout->addWidget(edit_IsRecirculating);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<AirRecirculationModeIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::~org_alljoyn_SmartSpaces_Operation_AirRecirculationMode()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "AirRecirculationMode getting properties";

        status = controller->GetIsRecirculating();
        if (status != ER_OK)
        {
            qWarning() << "AirRecirculationMode::fetchProperties Failed to get IsRecirculating" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::slotOnResponseGetIsRecirculating(QStatus status, const bool value)
{
    qWarning() << "AirRecirculationMode::slotOnResponseGetIsRecirculating";

    edit_IsRecirculating->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::slotOnIsRecirculatingChanged(const bool value)
{
    qWarning() << "AirRecirculationMode::slotOnIsRecirculatingChanged";

    edit_IsRecirculating->setChecked(value);
}



void org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::slotOnResponseSetIsRecirculating(QStatus status)
{
    qWarning() << "AirRecirculationMode::slotOnResponseSetIsRecirculating";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set IsRecirculating", status);
        qWarning() << "AirRecirculationMode::slotOnResponseSetIsRecirculating Failed to set IsRecirculating" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_AirRecirculationMode::slotSetIsRecirculating()
{
    qWarning() << "AirRecirculationMode::slotSetIsRecirculating";

    bool ok = false;
    bool value;
    value = edit_IsRecirculating->isChecked();
    ok = true;

    if (ok)
    {
        QStatus status = controller->SetIsRecirculating(value);

        if (status != ER_OK)
        {
            qWarning() << "AirRecirculationMode::slotSetIsRecirculating Failed to get IsRecirculating" << QCC_StatusText(status);
        }
    }
}
