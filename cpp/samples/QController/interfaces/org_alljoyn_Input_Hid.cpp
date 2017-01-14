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
#include "org_alljoyn_Input_Hid.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<HidInterface::InputEvent>(const HidInterface::InputEvent& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>type</b>: " << value.type << "\n";
    strm << "<b>code</b>: " << value.code << "\n";
    strm << "<b>value</b>: " << value.value << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<HidInterface::InputEvent>>(const std::vector<HidInterface::InputEvent>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">type</th>";
    strm << "<th bgcolor=\"light blue\">code</th>";
    strm << "<th bgcolor=\"light blue\">value</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.type << "</td>";
        strm << "<td>" << v.code << "</td>";
        strm << "<td>" << v.value << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<HidInterface::SupportedInputEvent>(const HidInterface::SupportedInputEvent& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>type</b>: " << value.type << "\n";
    strm << "<b>code</b>: " << value.code << "\n";
    strm << "<b>min</b>: " << value.min << "\n";
    strm << "<b>max</b>: " << value.max << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<HidInterface::SupportedInputEvent>>(const std::vector<HidInterface::SupportedInputEvent>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">type</th>";
    strm << "<th bgcolor=\"light blue\">code</th>";
    strm << "<th bgcolor=\"light blue\">min</th>";
    strm << "<th bgcolor=\"light blue\">max</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.type << "</td>";
        strm << "<td>" << v.code << "</td>";
        strm << "<td>" << v.min << "</td>";
        strm << "<td>" << v.max << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_Input_Hid*>();

Q_DECLARE_METATYPE(ajn::services::HidInterface::InputEvent);
Q_DECLARE_METATYPE(std::vector<ajn::services::HidInterface::InputEvent>);
static const int auto_register_struct_InputEvent = qRegisterMetaType<ajn::services::HidInterface::InputEvent>("HidInterface::InputEvent");
static const int auto_register_struct_v_InputEvent = qRegisterMetaType<std::vector<ajn::services::HidInterface::InputEvent>>("std::vector<HidInterface::InputEvent>");

Q_DECLARE_METATYPE(ajn::services::HidInterface::SupportedInputEvent);
Q_DECLARE_METATYPE(std::vector<ajn::services::HidInterface::SupportedInputEvent>);
static const int auto_register_struct_SupportedInputEvent = qRegisterMetaType<ajn::services::HidInterface::SupportedInputEvent>("HidInterface::SupportedInputEvent");
static const int auto_register_struct_v_SupportedInputEvent = qRegisterMetaType<std::vector<ajn::services::HidInterface::SupportedInputEvent>>("std::vector<HidInterface::SupportedInputEvent>");



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

    layout->addWidget(new QLabel("<b>SupportedEvents</b>"));
    // Create the editing widget for SupportedEvents
    edit_SupportedEvents = new QLabel();

    layout->addWidget(edit_SupportedEvents);

    messages_ = new QLabel();
    layout->addWidget(messages_);

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
        qWarning() << "Hid getting properties";

        status = controller->GetSupportedEvents();
        if (status != ER_OK)
        {
            qWarning() << "Hid::fetchProperties Failed to get SupportedEvents" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_Input_Hid::slotClickInjectEvents()
{
    qWarning() << "Hid::slotClickInjectEvents";

    std::vector<HidInterface::InputEvent> inputEvents {};

    bool ok = true;

    if (ok)
    {
        QStatus status = controller->InjectEvents(inputEvents, NULL);
        if (status != ER_OK)
        {
            qWarning() << "Hid::slotClick Failed to call InjectEvents" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_Input_Hid::slotOnResponseGetSupportedEvents(QStatus status, const std::vector<HidInterface::SupportedInputEvent>& value)
{
    qWarning() << "Hid::slotOnResponseGetSupportedEvents";

    edit_SupportedEvents->setText(QStringFrom(value));
}



void org_alljoyn_Input_Hid::slotOnSupportedEventsChanged(const std::vector<HidInterface::SupportedInputEvent>& value)
{
    qWarning() << "Hid::slotOnSupportedEventsChanged";

    edit_SupportedEvents->setText(QStringFrom(value));
}






void org_alljoyn_Input_Hid::slotOnResponseMethodInjectEvents(QStatus status, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "Hid::slotOnResponseMethodInjectEvents";
    }
    else
    {
        qWarning() << "Hid::slotOnResponseMethodInjectEvents Received error = " << errorName;
    }
}
