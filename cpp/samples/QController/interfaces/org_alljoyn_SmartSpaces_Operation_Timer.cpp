/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>




using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_Timer*>();


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

    layout->addWidget(new QLabel("ReferenceTimer"));
    // Create line edit for ReferenceTimer
    edit_ReferenceTimer = new QLineEdit();
    edit_ReferenceTimer->setToolTip("Time counter to be used as reference.");
    edit_ReferenceTimer->setReadOnly(true);
    layout->addWidget(edit_ReferenceTimer);
    layout->addWidget(new QLabel("TargetTimeToStart"));
    // Create line edit for TargetTimeToStart
    edit_TargetTimeToStart = new QLineEdit();
    edit_TargetTimeToStart->setToolTip("Time when the appliance is expected to start its operation.");
    edit_TargetTimeToStart->setReadOnly(true);
    layout->addWidget(edit_TargetTimeToStart);
    layout->addWidget(new QLabel("TargetTimeToStop"));
    // Create line edit for TargetTimeToStop
    edit_TargetTimeToStop = new QLineEdit();
    edit_TargetTimeToStop->setToolTip("Time when the appliance is expected to stop its operation.");
    edit_TargetTimeToStop->setReadOnly(true);
    layout->addWidget(edit_TargetTimeToStop);
    layout->addWidget(new QLabel("EstimatedTimeToEnd"));
    // Create line edit for EstimatedTimeToEnd
    edit_EstimatedTimeToEnd = new QLineEdit();
    edit_EstimatedTimeToEnd->setToolTip("Time to the end of appliance operation.");
    edit_EstimatedTimeToEnd->setReadOnly(true);
    layout->addWidget(edit_EstimatedTimeToEnd);
    layout->addWidget(new QLabel("RunningTime"));
    // Create line edit for RunningTime
    edit_RunningTime = new QLineEdit();
    edit_RunningTime->setToolTip("Time of current operation.");
    edit_RunningTime->setReadOnly(true);
    layout->addWidget(edit_RunningTime);
    layout->addWidget(new QLabel("TargetDuration"));
    // Create line edit for TargetDuration
    edit_TargetDuration = new QLineEdit();
    edit_TargetDuration->setToolTip("Time representing the target duration of the operation as per user selection.");
    edit_TargetDuration->setReadOnly(true);
    layout->addWidget(edit_TargetDuration);

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
        qWarning() << "org_alljoyn_SmartSpaces_Operation_Timer getting properties";

        status = controller->GetReferenceTimer();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get ReferenceTimer" << QCC_StatusText(status);
        }

        status = controller->GetTargetTimeToStart();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get TargetTimeToStart" << QCC_StatusText(status);
        }

        status = controller->GetTargetTimeToStop();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get TargetTimeToStop" << QCC_StatusText(status);
        }

        status = controller->GetEstimatedTimeToEnd();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get EstimatedTimeToEnd" << QCC_StatusText(status);
        }

        status = controller->GetRunningTime();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get RunningTime" << QCC_StatusText(status);
        }

        status = controller->GetTargetDuration();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get TargetDuration" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotClickSetTargetTimeToStart()
{
    qWarning() << __FUNCTION__;

    int32_t targetTimeToStart {};


    QStatus status = controller->SetTargetTimeToStart(targetTimeToStart, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call SetTargetTimeToStart" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotClickSetTargetTimeToStop()
{
    qWarning() << __FUNCTION__;

    int32_t targetTimeToStop {};


    QStatus status = controller->SetTargetTimeToStop(targetTimeToStop, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call SetTargetTimeToStop" << QCC_StatusText(status);
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetReferenceTimer(QStatus status, const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_ReferenceTimer->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Timer::slotOnReferenceTimerChanged(const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_ReferenceTimer->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetTargetTimeToStart(QStatus status, const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetTimeToStart->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Timer::slotOnTargetTimeToStartChanged(const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetTimeToStart->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetTargetTimeToStop(QStatus status, const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetTimeToStop->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Timer::slotOnTargetTimeToStopChanged(const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetTimeToStop->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetEstimatedTimeToEnd(QStatus status, const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_EstimatedTimeToEnd->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Timer::slotOnEstimatedTimeToEndChanged(const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_EstimatedTimeToEnd->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetRunningTime(QStatus status, const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_RunningTime->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Timer::slotOnRunningTimeChanged(const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_RunningTime->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseGetTargetDuration(QStatus status, const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetDuration->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_Timer::slotOnTargetDurationChanged(const int32_t value)
{
    qWarning() << __FUNCTION__;
    edit_TargetDuration->setText(QStringFrom(value));
}




void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseMethodSetTargetTimeToStart(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method SetTargetTimeToStart";
    }
    else
    {
        qWarning() << "Received an error from method SetTargetTimeToStart, error = " << errorName;
    }
}



void org_alljoyn_SmartSpaces_Operation_Timer::slotOnResponseMethodSetTargetTimeToStop(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method SetTargetTimeToStop";
    }
    else
    {
        qWarning() << "Received an error from method SetTargetTimeToStop, error = " << errorName;
    }
}