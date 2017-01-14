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
#include "org_alljoyn_SmartSpaces_Operation_Timer.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Timer*>();


#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <alljoyn/cdm/common/LogModule.h>
#include <sstream>


org_alljoyn_SmartSpaces_Operation_Timer_GetTime::org_alljoyn_SmartSpaces_Operation_Timer_GetTime(QWidget* parent, const char* label, int32_t time)
{
    time_ = time;
    label_ = label;

    dialog_ = new QDialog(parent);
    auto* dlgLayout_ = new QVBoxLayout(dialog_);

    dlgLayout_->addWidget(new QLabel(label_));
    timeSpin_ = new QSpinBox();
    dlgLayout_->addWidget(timeSpin_);
    timeSpin_->setValue(time_);
    QObject::connect(timeSpin_, SIGNAL(valueChanged(int)), this, SLOT(changed()));

    auto* buttons = new QDialogButtonBox();
    dlgLayout_->addWidget(buttons);

    auto* cancel = buttons->addButton(QDialogButtonBox::Cancel);
    QObject::connect(cancel, SIGNAL(clicked(bool)), dialog_, SLOT(reject()));

    auto* ok = buttons->addButton(QDialogButtonBox::Ok);
    QObject::connect(ok, SIGNAL(clicked(bool)), dialog_, SLOT(accept()));
}



org_alljoyn_SmartSpaces_Operation_Timer_GetTime::~org_alljoyn_SmartSpaces_Operation_Timer_GetTime()
{
    delete dialog_;
}



int org_alljoyn_SmartSpaces_Operation_Timer_GetTime::run()
{
    // This is always modal
    return dialog_->exec();
}



void org_alljoyn_SmartSpaces_Operation_Timer_GetTime::changed()
{
    time_ = timeSpin_->value();
}



static bool DialogGetTime(QWidget* parent, const char* label, int32_t& time)
{
    auto* dialog = new org_alljoyn_SmartSpaces_Operation_Timer_GetTime(parent, label, time);
    auto code = dialog->run();
    bool ok = code == QDialog::Accepted;

    if (ok)
    {
        time = dialog->time_;
    }

    delete dialog;
    return ok;
}




org_alljoyn_SmartSpaces_Operation_Timer::org_alljoyn_SmartSpaces_Operation_Timer(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for SetTargetTimeToStart
    button_SetTargetTimeToStart = new QPushButton("SetTargetTimeToStart");
    QObject::connect(button_SetTargetTimeToStart, SIGNAL(clicked()), this, SLOT(slotClickSetTargetTimeToStart()));
    layout->addWidget(button_SetTargetTimeToStart);
    // Create button for SetTargetTimeToStop
    button_SetTargetTimeToStop = new QPushButton("SetTargetTimeToStop");
    QObject::connect(button_SetTargetTimeToStop, SIGNAL(clicked()), this, SLOT(slotClickSetTargetTimeToStop()));
    layout->addWidget(button_SetTargetTimeToStop);

    layout->addWidget(new QLabel("<b>ReferenceTimer</b>"));
    // Create the editing widget for ReferenceTimer
    edit_ReferenceTimer = new QLabel();

    layout->addWidget(edit_ReferenceTimer);
    layout->addWidget(new QLabel("<b>TargetTimeToStart</b>"));
    // Create the editing widget for TargetTimeToStart
    edit_TargetTimeToStart = new QLabel();

    layout->addWidget(edit_TargetTimeToStart);
    layout->addWidget(new QLabel("<b>TargetTimeToStop</b>"));
    // Create the editing widget for TargetTimeToStop
    edit_TargetTimeToStop = new QLabel();

    layout->addWidget(edit_TargetTimeToStop);
    layout->addWidget(new QLabel("<b>EstimatedTimeToEnd</b>"));
    // Create the editing widget for EstimatedTimeToEnd
    edit_EstimatedTimeToEnd = new QLabel();

    layout->addWidget(edit_EstimatedTimeToEnd);
    layout->addWidget(new QLabel("<b>RunningTime</b>"));
    // Create the editing widget for RunningTime
    edit_RunningTime = new QLabel();

    layout->addWidget(edit_RunningTime);
    layout->addWidget(new QLabel("<b>TargetDuration</b>"));
    // Create the editing widget for TargetDuration
    edit_TargetDuration = new QLabel();

    layout->addWidget(edit_TargetDuration);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<TimerIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_Timer::~org_alljoyn_SmartSpaces_Operation_Timer()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_Timer::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "Timer getting properties";

        status = controller->GetReferenceTimer();
        if (status != ER_OK)
        {
            qWarning() << "Timer::fetchProperties Failed to get ReferenceTimer" << QCC_StatusText(status);
        }

        status = controller->GetTargetTimeToStart();
        if (status != ER_OK)
        {
            qWarning() << "Timer::fetchProperties Failed to get TargetTimeToStart" << QCC_StatusText(status);
        }

        status = controller->GetTargetTimeToStop();
        if (status != ER_OK)
        {
            qWarning() << "Timer::fetchProperties Failed to get TargetTimeToStop" << QCC_StatusText(status);
        }

        status = controller->GetEstimatedTimeToEnd();
        if (status != ER_OK)
        {
            qWarning() << "Timer::fetchProperties Failed to get EstimatedTimeToEnd" << QCC_StatusText(status);
        }

        status = controller->GetRunningTime();
        if (status != ER_OK)
        {
            qWarning() << "Timer::fetchProperties Failed to get RunningTime" << QCC_StatusText(status);
        }

        status = controller->GetTargetDuration();
        if (status != ER_OK)
        {
            qWarning() << "Timer::fetchProperties Failed to get TargetDuration" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotClickSetTargetTimeToStart()
{
    qWarning() << "Timer::slotClickSetTargetTimeToStart";

    int32_t targetTimeToStart {};

    bool ok = true;
    targetTimeToStart = 0;
    ok = DialogGetTime(this, "Time to Start", targetTimeToStart);

    if (ok)
    {
        QStatus status = controller->SetTargetTimeToStart(targetTimeToStart, NULL);
        if (status != ER_OK)
        {
            qWarning() << "Timer::slotClick Failed to call SetTargetTimeToStart" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotClickSetTargetTimeToStop()
{
    qWarning() << "Timer::slotClickSetTargetTimeToStop";

    int32_t targetTimeToStop {};

    bool ok = true;
    targetTimeToStop = 0;
    ok = DialogGetTime(this, "Time to Stop", targetTimeToStop);

    if (ok)
    {
        QStatus status = controller->SetTargetTimeToStop(targetTimeToStop, NULL);
        if (status != ER_OK)
        {
            qWarning() << "Timer::slotClick Failed to call SetTargetTimeToStop" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetReferenceTimer(QStatus status, const int32_t value)
{
    qWarning() << "Timer::slotOnResponseGetReferenceTimer";

    edit_ReferenceTimer->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnReferenceTimerChanged(const int32_t value)
{
    qWarning() << "Timer::slotOnReferenceTimerChanged";

    edit_ReferenceTimer->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetTargetTimeToStart(QStatus status, const int32_t value)
{
    qWarning() << "Timer::slotOnResponseGetTargetTimeToStart";

    edit_TargetTimeToStart->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnTargetTimeToStartChanged(const int32_t value)
{
    qWarning() << "Timer::slotOnTargetTimeToStartChanged";

    edit_TargetTimeToStart->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetTargetTimeToStop(QStatus status, const int32_t value)
{
    qWarning() << "Timer::slotOnResponseGetTargetTimeToStop";

    edit_TargetTimeToStop->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnTargetTimeToStopChanged(const int32_t value)
{
    qWarning() << "Timer::slotOnTargetTimeToStopChanged";

    edit_TargetTimeToStop->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetEstimatedTimeToEnd(QStatus status, const int32_t value)
{
    qWarning() << "Timer::slotOnResponseGetEstimatedTimeToEnd";

    edit_EstimatedTimeToEnd->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnEstimatedTimeToEndChanged(const int32_t value)
{
    qWarning() << "Timer::slotOnEstimatedTimeToEndChanged";

    edit_EstimatedTimeToEnd->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetRunningTime(QStatus status, const int32_t value)
{
    qWarning() << "Timer::slotOnResponseGetRunningTime";

    edit_RunningTime->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnRunningTimeChanged(const int32_t value)
{
    qWarning() << "Timer::slotOnRunningTimeChanged";

    edit_RunningTime->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetTargetDuration(QStatus status, const int32_t value)
{
    qWarning() << "Timer::slotOnResponseGetTargetDuration";

    edit_TargetDuration->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnTargetDurationChanged(const int32_t value)
{
    qWarning() << "Timer::slotOnTargetDurationChanged";

    edit_TargetDuration->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseMethodSetTargetTimeToStart(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Timer::slotOnResponseMethodSetTargetTimeToStart";
    }
    else
    {
        qWarning() << "Timer::slotOnResponseMethodSetTargetTimeToStart Received error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseMethodSetTargetTimeToStop(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Timer::slotOnResponseMethodSetTargetTimeToStop";
    }
    else
    {
        qWarning() << "Timer::slotOnResponseMethodSetTargetTimeToStop Received error = " << errorName;
    }
}
