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
#include "org_alljoyn_SmartSpaces_Environment_WindDirection.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<WindDirectionInterface::AutoMode>(const WindDirectionInterface::AutoMode& value)
{
    QString result;

    switch (value)
    {
    case WindDirectionInterface::AUTO_MODE_OFF:
        result = "Off";
        break;

    case WindDirectionInterface::AUTO_MODE_ON:
        result = "On";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<WindDirectionInterface::AutoMode>>(const std::vector<WindDirectionInterface::AutoMode>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">AutoMode</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == WindDirectionInterface::AUTO_MODE_OFF)
        {
            strm << "<tr><td>Off</td></tr>";
        }
        if (v == WindDirectionInterface::AUTO_MODE_ON)
        {
            strm << "<tr><td>On</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_WindDirection*>();

Q_DECLARE_METATYPE(ajn::services::WindDirectionInterface::AutoMode);
Q_DECLARE_METATYPE(std::vector<ajn::services::WindDirectionInterface::AutoMode>);
static const int auto_register_enum_AutoMode = qRegisterMetaType<ajn::services::WindDirectionInterface::AutoMode>("WindDirectionInterface::AutoMode");
static const int auto_register_enum_v_AutoMode = qRegisterMetaType<std::vector<ajn::services::WindDirectionInterface::AutoMode>>("std::vector<WindDirectionInterface::AutoMode>");



org_alljoyn_SmartSpaces_Environment_WindDirection::org_alljoyn_SmartSpaces_Environment_WindDirection(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>HorizontalDirection</b>"));
    // Create the editing widget for HorizontalDirection
    edit_HorizontalDirection = new QLineEdit();
    edit_HorizontalDirection->setToolTip("Horizontal wind direction of a device.");
    QObject::connect(edit_HorizontalDirection, SIGNAL(returnPressed()), this, SLOT(slotSetHorizontalDirection()));

    layout->addWidget(edit_HorizontalDirection);
    layout->addWidget(new QLabel("<b>HorizontalMax</b>"));
    // Create the editing widget for HorizontalMax
    edit_HorizontalMax = new QLabel();

    layout->addWidget(edit_HorizontalMax);
    layout->addWidget(new QLabel("<b>HorizontalAutoMode</b>"));
    // Create the editing widget for HorizontalAutoMode
    edit_HorizontalAutoMode = new QComboBox();
    edit_HorizontalAutoMode->setEditable(false);
    edit_HorizontalAutoMode->addItem("Off");
    edit_HorizontalAutoMode->addItem("On");
    edit_HorizontalAutoMode->setEnabled(true);
    QObject::connect(edit_HorizontalAutoMode, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSetHorizontalAutoMode()));

    layout->addWidget(edit_HorizontalAutoMode);
    layout->addWidget(new QLabel("<b>VerticalDirection</b>"));
    // Create the editing widget for VerticalDirection
    edit_VerticalDirection = new QLineEdit();
    edit_VerticalDirection->setToolTip("Vertical wind direction of a device.");
    QObject::connect(edit_VerticalDirection, SIGNAL(returnPressed()), this, SLOT(slotSetVerticalDirection()));

    layout->addWidget(edit_VerticalDirection);
    layout->addWidget(new QLabel("<b>VerticalMax</b>"));
    // Create the editing widget for VerticalMax
    edit_VerticalMax = new QLabel();

    layout->addWidget(edit_VerticalMax);
    layout->addWidget(new QLabel("<b>VerticalAutoMode</b>"));
    // Create the editing widget for VerticalAutoMode
    edit_VerticalAutoMode = new QComboBox();
    edit_VerticalAutoMode->setEditable(false);
    edit_VerticalAutoMode->addItem("Off");
    edit_VerticalAutoMode->addItem("On");
    edit_VerticalAutoMode->setEnabled(true);
    QObject::connect(edit_VerticalAutoMode, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSetVerticalAutoMode()));

    layout->addWidget(edit_VerticalAutoMode);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<WindDirectionIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_WindDirection::~org_alljoyn_SmartSpaces_Environment_WindDirection()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "WindDirection getting properties";

        status = controller->GetHorizontalDirection();
        if (status != ER_OK)
        {
            qWarning() << "WindDirection::fetchProperties Failed to get HorizontalDirection" << QCC_StatusText(status);
        }

        status = controller->GetHorizontalMax();
        if (status != ER_OK)
        {
            qWarning() << "WindDirection::fetchProperties Failed to get HorizontalMax" << QCC_StatusText(status);
        }

        status = controller->GetHorizontalAutoMode();
        if (status != ER_OK)
        {
            qWarning() << "WindDirection::fetchProperties Failed to get HorizontalAutoMode" << QCC_StatusText(status);
        }

        status = controller->GetVerticalDirection();
        if (status != ER_OK)
        {
            qWarning() << "WindDirection::fetchProperties Failed to get VerticalDirection" << QCC_StatusText(status);
        }

        status = controller->GetVerticalMax();
        if (status != ER_OK)
        {
            qWarning() << "WindDirection::fetchProperties Failed to get VerticalMax" << QCC_StatusText(status);
        }

        status = controller->GetVerticalAutoMode();
        if (status != ER_OK)
        {
            qWarning() << "WindDirection::fetchProperties Failed to get VerticalAutoMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetHorizontalDirection(QStatus status, const uint16_t value)
{
    qWarning() << "WindDirection::slotOnResponseGetHorizontalDirection";

    edit_HorizontalDirection->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnHorizontalDirectionChanged(const uint16_t value)
{
    qWarning() << "WindDirection::slotOnHorizontalDirectionChanged";

    edit_HorizontalDirection->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetHorizontalDirection(QStatus status)
{
    qWarning() << "WindDirection::slotOnResponseSetHorizontalDirection";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set HorizontalDirection", status);
        qWarning() << "WindDirection::slotOnResponseSetHorizontalDirection Failed to set HorizontalDirection" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetHorizontalDirection()
{
    qWarning() << "WindDirection::slotSetHorizontalDirection";

    bool ok = false;
    uint16_t value;
    QString str = edit_HorizontalDirection->text();
    value = QStringTo<uint16_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "WindDirection::slotSetHorizontalDirection Failed to convert '" << str << "' to uint16_t";
    }

    if (ok)
    {
        QStatus status = controller->SetHorizontalDirection(value);

        if (status != ER_OK)
        {
            qWarning() << "WindDirection::slotSetHorizontalDirection Failed to get HorizontalDirection" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetHorizontalMax(QStatus status, const uint16_t value)
{
    qWarning() << "WindDirection::slotOnResponseGetHorizontalMax";

    edit_HorizontalMax->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnHorizontalMaxChanged(const uint16_t value)
{
    qWarning() << "WindDirection::slotOnHorizontalMaxChanged";

    edit_HorizontalMax->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetHorizontalAutoMode(QStatus status, const WindDirectionInterface::AutoMode value)
{
    qWarning() << "WindDirection::slotOnResponseGetHorizontalAutoMode";

    switch (value)
    {
    case WindDirectionInterface::AUTO_MODE_OFF:
        edit_HorizontalAutoMode->setCurrentText("Off");
        break;

    case WindDirectionInterface::AUTO_MODE_ON:
        edit_HorizontalAutoMode->setCurrentText("On");
        break;

    default:
        edit_HorizontalAutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnHorizontalAutoModeChanged(const WindDirectionInterface::AutoMode value)
{
    qWarning() << "WindDirection::slotOnHorizontalAutoModeChanged";

    switch (value)
    {
    case WindDirectionInterface::AUTO_MODE_OFF:
        edit_HorizontalAutoMode->setCurrentText("Off");
        break;

    case WindDirectionInterface::AUTO_MODE_ON:
        edit_HorizontalAutoMode->setCurrentText("On");
        break;

    default:
        edit_HorizontalAutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetHorizontalAutoMode(QStatus status)
{
    qWarning() << "WindDirection::slotOnResponseSetHorizontalAutoMode";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set HorizontalAutoMode", status);
        qWarning() << "WindDirection::slotOnResponseSetHorizontalAutoMode Failed to set HorizontalAutoMode" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetHorizontalAutoMode()
{
    qWarning() << "WindDirection::slotSetHorizontalAutoMode";

    bool ok = false;
    WindDirectionInterface::AutoMode value;
    QString str = edit_HorizontalAutoMode->currentText();
    if (str == "Off")
    {
        value = WindDirectionInterface::AUTO_MODE_OFF;
        ok = true;
    }
    else
    if (str == "On")
    {
        value = WindDirectionInterface::AUTO_MODE_ON;
        ok = true;
    }
    else
    if (!str.isEmpty())
    {
        qWarning() << "WindDirection::slotSetHorizontalAutoMode Failed to convert '" << str.constData() << "' to WindDirectionInterface::AutoMode";
    }

    if (ok)
    {
        QStatus status = controller->SetHorizontalAutoMode(value);

        if (status != ER_OK)
        {
            qWarning() << "WindDirection::slotSetHorizontalAutoMode Failed to get HorizontalAutoMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetVerticalDirection(QStatus status, const uint16_t value)
{
    qWarning() << "WindDirection::slotOnResponseGetVerticalDirection";

    edit_VerticalDirection->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnVerticalDirectionChanged(const uint16_t value)
{
    qWarning() << "WindDirection::slotOnVerticalDirectionChanged";

    edit_VerticalDirection->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetVerticalDirection(QStatus status)
{
    qWarning() << "WindDirection::slotOnResponseSetVerticalDirection";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set VerticalDirection", status);
        qWarning() << "WindDirection::slotOnResponseSetVerticalDirection Failed to set VerticalDirection" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetVerticalDirection()
{
    qWarning() << "WindDirection::slotSetVerticalDirection";

    bool ok = false;
    uint16_t value;
    QString str = edit_VerticalDirection->text();
    value = QStringTo<uint16_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "WindDirection::slotSetVerticalDirection Failed to convert '" << str << "' to uint16_t";
    }

    if (ok)
    {
        QStatus status = controller->SetVerticalDirection(value);

        if (status != ER_OK)
        {
            qWarning() << "WindDirection::slotSetVerticalDirection Failed to get VerticalDirection" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetVerticalMax(QStatus status, const uint16_t value)
{
    qWarning() << "WindDirection::slotOnResponseGetVerticalMax";

    edit_VerticalMax->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnVerticalMaxChanged(const uint16_t value)
{
    qWarning() << "WindDirection::slotOnVerticalMaxChanged";

    edit_VerticalMax->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseGetVerticalAutoMode(QStatus status, const WindDirectionInterface::AutoMode value)
{
    qWarning() << "WindDirection::slotOnResponseGetVerticalAutoMode";

    switch (value)
    {
    case WindDirectionInterface::AUTO_MODE_OFF:
        edit_VerticalAutoMode->setCurrentText("Off");
        break;

    case WindDirectionInterface::AUTO_MODE_ON:
        edit_VerticalAutoMode->setCurrentText("On");
        break;

    default:
        edit_VerticalAutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnVerticalAutoModeChanged(const WindDirectionInterface::AutoMode value)
{
    qWarning() << "WindDirection::slotOnVerticalAutoModeChanged";

    switch (value)
    {
    case WindDirectionInterface::AUTO_MODE_OFF:
        edit_VerticalAutoMode->setCurrentText("Off");
        break;

    case WindDirectionInterface::AUTO_MODE_ON:
        edit_VerticalAutoMode->setCurrentText("On");
        break;

    default:
        edit_VerticalAutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotOnResponseSetVerticalAutoMode(QStatus status)
{
    qWarning() << "WindDirection::slotOnResponseSetVerticalAutoMode";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set VerticalAutoMode", status);
        qWarning() << "WindDirection::slotOnResponseSetVerticalAutoMode Failed to set VerticalAutoMode" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Environment_WindDirection::slotSetVerticalAutoMode()
{
    qWarning() << "WindDirection::slotSetVerticalAutoMode";

    bool ok = false;
    WindDirectionInterface::AutoMode value;
    QString str = edit_VerticalAutoMode->currentText();
    if (str == "Off")
    {
        value = WindDirectionInterface::AUTO_MODE_OFF;
        ok = true;
    }
    else
    if (str == "On")
    {
        value = WindDirectionInterface::AUTO_MODE_ON;
        ok = true;
    }
    else
    if (!str.isEmpty())
    {
        qWarning() << "WindDirection::slotSetVerticalAutoMode Failed to convert '" << str.constData() << "' to WindDirectionInterface::AutoMode";
    }

    if (ok)
    {
        QStatus status = controller->SetVerticalAutoMode(value);

        if (status != ER_OK)
        {
            qWarning() << "WindDirection::slotSetVerticalAutoMode Failed to get VerticalAutoMode" << QCC_StatusText(status);
        }
    }
}
