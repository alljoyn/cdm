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

#include "org_alljoyn_Input_Hid.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>


template<>
QString
QStringFrom<HidInterface::InputEvent>(const HidInterface::InputEvent& value)
{
    std::ostringstream strm;
    strm << "{";
    strm << "type=" << value.type;
    strm << " ";
    strm << "code=" << value.code;
    strm << " ";
    strm << "value=" << value.value;
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<HidInterface::InputEvent>>(const std::vector<HidInterface::InputEvent>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<HidInterface::InputEvent>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}



template<>
QString
QStringFrom<HidInterface::SupportedInputEvent>(const HidInterface::SupportedInputEvent& value)
{
    std::ostringstream strm;
    strm << "{";
    strm << "type=" << value.type;
    strm << " ";
    strm << "code=" << value.code;
    strm << " ";
    strm << "min=" << value.min;
    strm << " ";
    strm << "max=" << value.max;
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<HidInterface::SupportedInputEvent>>(const std::vector<HidInterface::SupportedInputEvent>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<HidInterface::SupportedInputEvent>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}





using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_Input_Hid*>();


org_alljoyn_Input_Hid::org_alljoyn_Input_Hid(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for InjectEvents
    button_InjectEvents = new QPushButton("InjectEvents");
    button_InjectEvents->setToolTip("Inject the user input events for human interface devices");
    QObject::connect(button_InjectEvents, SIGNAL(clicked()), this, SLOT(slotClickInjectEvents()));
    layout->addWidget(button_InjectEvents);

    layout->addWidget(new QLabel("SupportedEvents"));
    // Create line edit for SupportedEvents
    edit_SupportedEvents = new QLineEdit();
    edit_SupportedEvents->setToolTip("List of supported input events by a device");
    edit_SupportedEvents->setReadOnly(true);
    layout->addWidget(edit_SupportedEvents);

    if (iface)
    {
        controller = iface->CreateInterface<HidIntfController>(m_listener);
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

org_alljoyn_Input_Hid::~org_alljoyn_Input_Hid()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_Input_Hid::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "org_alljoyn_Input_Hid getting properties";

        status = controller->GetSupportedEvents();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get SupportedEvents" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_Input_Hid::slotClickInjectEvents()
{
    qWarning() << __FUNCTION__;

    std::vector<HidInterface::InputEvent> inputEvents {};


    QStatus status = controller->InjectEvents(inputEvents, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call InjectEvents" << QCC_StatusText(status);
    }
}



void org_alljoyn_Input_Hid::slotOnResponseGetSupportedEvents(QStatus status, const std::vector<HidInterface::SupportedInputEvent>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedEvents->setText(QStringFrom(value));
}

void org_alljoyn_Input_Hid::slotOnSupportedEventsChanged(const std::vector<HidInterface::SupportedInputEvent>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedEvents->setText(QStringFrom(value));
}




void org_alljoyn_Input_Hid::slotOnResponseMethodInjectEvents(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Received response to method InjectEvents";
    }
    else
    {
        qWarning() << "Received an error from method InjectEvents, error = " << errorName;
    }
}