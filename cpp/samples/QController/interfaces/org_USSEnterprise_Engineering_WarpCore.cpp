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
#include "org_USSEnterprise_Engineering_WarpCore.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_USSEnterprise_Engineering_WarpCore*>();



org_USSEnterprise_Engineering_WarpCore::org_USSEnterprise_Engineering_WarpCore(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for Engage
    button_Engage = new QPushButton("Engage");
    button_Engage->setToolTip("Engage the warp core and enter warp.");
    QObject::connect(button_Engage, SIGNAL(clicked()), this, SLOT(slotClickEngage()));
    layout->addWidget(button_Engage);
    // Create button for Disengage
    button_Disengage = new QPushButton("Disengage");
    button_Disengage->setToolTip("Return to impulse.");
    QObject::connect(button_Disengage, SIGNAL(clicked()), this, SLOT(slotClickDisengage()));
    layout->addWidget(button_Disengage);

    layout->addWidget(new QLabel("<b>WarpFactor</b>"));
    // Create the editing widget for WarpFactor
    edit_WarpFactor = new QLineEdit();
    edit_WarpFactor->setToolTip("The desired warp factor.");
    QObject::connect(edit_WarpFactor, SIGNAL(returnPressed()), this, SLOT(slotSetWarpFactor()));

    layout->addWidget(edit_WarpFactor);
    layout->addWidget(new QLabel("<b>CurrentWarpFactor</b>"));
    // Create the editing widget for CurrentWarpFactor
    edit_CurrentWarpFactor = new QLabel();

    layout->addWidget(edit_CurrentWarpFactor);
    layout->addWidget(new QLabel("<b>IsEngaged</b>"));
    // Create the editing widget for IsEngaged
    edit_IsEngaged = new QCheckBox();
    edit_IsEngaged->setEnabled(false);

    layout->addWidget(edit_IsEngaged);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<WarpCoreIntfController>(m_listener);
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

org_USSEnterprise_Engineering_WarpCore::~org_USSEnterprise_Engineering_WarpCore()
{
    qWarning() << __FUNCTION__;
}



void org_USSEnterprise_Engineering_WarpCore::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "WarpCore getting properties";

        status = controller->GetWarpFactor();
        if (status != ER_OK)
        {
            qWarning() << "WarpCore::fetchProperties Failed to get WarpFactor" << QCC_StatusText(status);
        }

        status = controller->GetCurrentWarpFactor();
        if (status != ER_OK)
        {
            qWarning() << "WarpCore::fetchProperties Failed to get CurrentWarpFactor" << QCC_StatusText(status);
        }

        status = controller->GetIsEngaged();
        if (status != ER_OK)
        {
            qWarning() << "WarpCore::fetchProperties Failed to get IsEngaged" << QCC_StatusText(status);
        }
    }
}



void org_USSEnterprise_Engineering_WarpCore::slotClickEngage()
{
    qWarning() << "WarpCore::slotClickEngage";


    bool ok = true;

    if (ok)
    {
        QStatus status = controller->Engage(NULL);
        if (status != ER_OK)
        {
            qWarning() << "WarpCore::slotClick Failed to call Engage" << QCC_StatusText(status);
        }
    }
}



void org_USSEnterprise_Engineering_WarpCore::slotClickDisengage()
{
    qWarning() << "WarpCore::slotClickDisengage";


    bool ok = true;

    if (ok)
    {
        QStatus status = controller->Disengage(NULL);
        if (status != ER_OK)
        {
            qWarning() << "WarpCore::slotClick Failed to call Disengage" << QCC_StatusText(status);
        }
    }
}



void org_USSEnterprise_Engineering_WarpCore::slotOnResponseGetWarpFactor(QStatus status, const double value)
{
    qWarning() << "WarpCore::slotOnResponseGetWarpFactor";

    edit_WarpFactor->setText(QStringFrom(value));
}



void org_USSEnterprise_Engineering_WarpCore::slotOnWarpFactorChanged(const double value)
{
    qWarning() << "WarpCore::slotOnWarpFactorChanged";

    edit_WarpFactor->setText(QStringFrom(value));
}



void org_USSEnterprise_Engineering_WarpCore::slotOnResponseSetWarpFactor(QStatus status)
{
    qWarning() << "WarpCore::slotOnResponseSetWarpFactor";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set WarpFactor", status);
        qWarning() << "WarpCore::slotOnResponseSetWarpFactor Failed to set WarpFactor" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_USSEnterprise_Engineering_WarpCore::slotSetWarpFactor()
{
    qWarning() << "WarpCore::slotSetWarpFactor";

    bool ok = false;
    double value;
    QString str = edit_WarpFactor->text();
    value = QStringTo<double>(str, &ok);
    if (!ok)
    {
        qWarning() << "WarpCore::slotSetWarpFactor Failed to convert '" << str << "' to double";
    }

    if (ok)
    {
        QStatus status = controller->SetWarpFactor(value);

        if (status != ER_OK)
        {
            qWarning() << "WarpCore::slotSetWarpFactor Failed to get WarpFactor" << QCC_StatusText(status);
        }
    }
}



void org_USSEnterprise_Engineering_WarpCore::slotOnResponseGetCurrentWarpFactor(QStatus status, const double value)
{
    qWarning() << "WarpCore::slotOnResponseGetCurrentWarpFactor";

    edit_CurrentWarpFactor->setText(QStringFrom(value));
}



void org_USSEnterprise_Engineering_WarpCore::slotOnCurrentWarpFactorChanged(const double value)
{
    qWarning() << "WarpCore::slotOnCurrentWarpFactorChanged";

    edit_CurrentWarpFactor->setText(QStringFrom(value));
}






void org_USSEnterprise_Engineering_WarpCore::slotOnResponseGetIsEngaged(QStatus status, const bool value)
{
    qWarning() << "WarpCore::slotOnResponseGetIsEngaged";

    edit_IsEngaged->setChecked(value);
}



void org_USSEnterprise_Engineering_WarpCore::slotOnIsEngagedChanged(const bool value)
{
    qWarning() << "WarpCore::slotOnIsEngagedChanged";

    edit_IsEngaged->setChecked(value);
}






void org_USSEnterprise_Engineering_WarpCore::slotOnResponseMethodEngage(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "WarpCore::slotOnResponseMethodEngage";
    }
    else
    {
        qWarning() << "WarpCore::slotOnResponseMethodEngage Received error = " << errorName;
    }
}



void org_USSEnterprise_Engineering_WarpCore::slotOnResponseMethodDisengage(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "WarpCore::slotOnResponseMethodDisengage";
    }
    else
    {
        qWarning() << "WarpCore::slotOnResponseMethodDisengage Received error = " << errorName;
    }
}
