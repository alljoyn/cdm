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
#include "org_alljoyn_SmartSpaces_Operation_FanSpeedLevel.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<FanSpeedLevelInterface::AutoMode>(const FanSpeedLevelInterface::AutoMode& value)
{
    QString result;

    switch (value)
    {
    case FanSpeedLevelInterface::AUTO_MODE_OFF:
        result = "Off";
        break;

    case FanSpeedLevelInterface::AUTO_MODE_ON:
        result = "On";
        break;

    case FanSpeedLevelInterface::AUTO_MODE_NOT_SUPPORTED:
        result = "NotSupported";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<FanSpeedLevelInterface::AutoMode>>(const std::vector<FanSpeedLevelInterface::AutoMode>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">AutoMode</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == FanSpeedLevelInterface::AUTO_MODE_OFF)
        {
            strm << "<tr><td>Off</td></tr>";
        }
        if (v == FanSpeedLevelInterface::AUTO_MODE_ON)
        {
            strm << "<tr><td>On</td></tr>";
        }
        if (v == FanSpeedLevelInterface::AUTO_MODE_NOT_SUPPORTED)
        {
            strm << "<tr><td>NotSupported</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_FanSpeedLevel*>();

Q_DECLARE_METATYPE(ajn::services::FanSpeedLevelInterface::AutoMode);
Q_DECLARE_METATYPE(std::vector<ajn::services::FanSpeedLevelInterface::AutoMode>);
static const int auto_register_enum_AutoMode = qRegisterMetaType<ajn::services::FanSpeedLevelInterface::AutoMode>("FanSpeedLevelInterface::AutoMode");
static const int auto_register_enum_v_AutoMode = qRegisterMetaType<std::vector<ajn::services::FanSpeedLevelInterface::AutoMode>>("std::vector<FanSpeedLevelInterface::AutoMode>");



org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::org_alljoyn_SmartSpaces_Operation_FanSpeedLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>FanSpeedLevel</b>"));
    // Create the editing widget for FanSpeedLevel
    edit_FanSpeedLevel = new QLineEdit();
    edit_FanSpeedLevel->setToolTip("Fan speed level of a device. Special value: 0x00 - Fan operation is turned off and controller shall not set 0x00. Turning on/off shall be operated by a different interface (OnOff).");
    QObject::connect(edit_FanSpeedLevel, SIGNAL(returnPressed()), this, SLOT(slotSetFanSpeedLevel()));

    layout->addWidget(edit_FanSpeedLevel);
    layout->addWidget(new QLabel("<b>MaxFanSpeedLevel</b>"));
    // Create the editing widget for MaxFanSpeedLevel
    edit_MaxFanSpeedLevel = new QLabel();

    layout->addWidget(edit_MaxFanSpeedLevel);
    layout->addWidget(new QLabel("<b>AutoMode</b>"));
    // Create the editing widget for AutoMode
    edit_AutoMode = new QComboBox();
    edit_AutoMode->setEditable(false);
    edit_AutoMode->addItem("Off");
    edit_AutoMode->addItem("On");
    edit_AutoMode->addItem("NotSupported");
    edit_AutoMode->setEnabled(true);
    QObject::connect(edit_AutoMode, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSetAutoMode()));

    layout->addWidget(edit_AutoMode);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<FanSpeedLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::~org_alljoyn_SmartSpaces_Operation_FanSpeedLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "FanSpeedLevel getting properties";

        status = controller->GetFanSpeedLevel();
        if (status != ER_OK)
        {
            qWarning() << "FanSpeedLevel::fetchProperties Failed to get FanSpeedLevel" << QCC_StatusText(status);
        }

        status = controller->GetMaxFanSpeedLevel();
        if (status != ER_OK)
        {
            qWarning() << "FanSpeedLevel::fetchProperties Failed to get MaxFanSpeedLevel" << QCC_StatusText(status);
        }

        status = controller->GetAutoMode();
        if (status != ER_OK)
        {
            qWarning() << "FanSpeedLevel::fetchProperties Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseGetFanSpeedLevel(QStatus status, const uint8_t value)
{
    qWarning() << "FanSpeedLevel::slotOnResponseGetFanSpeedLevel";

    edit_FanSpeedLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnFanSpeedLevelChanged(const uint8_t value)
{
    qWarning() << "FanSpeedLevel::slotOnFanSpeedLevelChanged";

    edit_FanSpeedLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseSetFanSpeedLevel(QStatus status)
{
    qWarning() << "FanSpeedLevel::slotOnResponseSetFanSpeedLevel";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set FanSpeedLevel", status);
        qWarning() << "FanSpeedLevel::slotOnResponseSetFanSpeedLevel Failed to set FanSpeedLevel" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotSetFanSpeedLevel()
{
    qWarning() << "FanSpeedLevel::slotSetFanSpeedLevel";

    bool ok = false;
    uint8_t value;
    QString str = edit_FanSpeedLevel->text();
    value = QStringTo<uint8_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "FanSpeedLevel::slotSetFanSpeedLevel Failed to convert '" << str << "' to uint8_t";
    }

    if (ok)
    {
        QStatus status = controller->SetFanSpeedLevel(value);

        if (status != ER_OK)
        {
            qWarning() << "FanSpeedLevel::slotSetFanSpeedLevel Failed to get FanSpeedLevel" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseGetMaxFanSpeedLevel(QStatus status, const uint8_t value)
{
    qWarning() << "FanSpeedLevel::slotOnResponseGetMaxFanSpeedLevel";

    edit_MaxFanSpeedLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnMaxFanSpeedLevelChanged(const uint8_t value)
{
    qWarning() << "FanSpeedLevel::slotOnMaxFanSpeedLevelChanged";

    edit_MaxFanSpeedLevel->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseGetAutoMode(QStatus status, const FanSpeedLevelInterface::AutoMode value)
{
    qWarning() << "FanSpeedLevel::slotOnResponseGetAutoMode";

    switch (value)
    {
    case FanSpeedLevelInterface::AUTO_MODE_OFF:
        edit_AutoMode->setCurrentText("Off");
        break;

    case FanSpeedLevelInterface::AUTO_MODE_ON:
        edit_AutoMode->setCurrentText("On");
        break;

    case FanSpeedLevelInterface::AUTO_MODE_NOT_SUPPORTED:
        edit_AutoMode->setCurrentText("NotSupported");
        break;

    default:
        edit_AutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnAutoModeChanged(const FanSpeedLevelInterface::AutoMode value)
{
    qWarning() << "FanSpeedLevel::slotOnAutoModeChanged";

    switch (value)
    {
    case FanSpeedLevelInterface::AUTO_MODE_OFF:
        edit_AutoMode->setCurrentText("Off");
        break;

    case FanSpeedLevelInterface::AUTO_MODE_ON:
        edit_AutoMode->setCurrentText("On");
        break;

    case FanSpeedLevelInterface::AUTO_MODE_NOT_SUPPORTED:
        edit_AutoMode->setCurrentText("NotSupported");
        break;

    default:
        edit_AutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotOnResponseSetAutoMode(QStatus status)
{
    qWarning() << "FanSpeedLevel::slotOnResponseSetAutoMode";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set AutoMode", status);
        qWarning() << "FanSpeedLevel::slotOnResponseSetAutoMode Failed to set AutoMode" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_FanSpeedLevel::slotSetAutoMode()
{
    qWarning() << "FanSpeedLevel::slotSetAutoMode";

    bool ok = false;
    FanSpeedLevelInterface::AutoMode value;
    QString str = edit_AutoMode->currentText();
    if (str == "Off")
    {
        value = FanSpeedLevelInterface::AUTO_MODE_OFF;
        ok = true;
    }
    else
    if (str == "On")
    {
        value = FanSpeedLevelInterface::AUTO_MODE_ON;
        ok = true;
    }
    else
    if (str == "NotSupported")
    {
        value = FanSpeedLevelInterface::AUTO_MODE_NOT_SUPPORTED;
        ok = true;
    }
    else
    if (!str.isEmpty())
    {
        qWarning() << "FanSpeedLevel::slotSetAutoMode Failed to convert '" << str.constData() << "' to FanSpeedLevelInterface::AutoMode";
    }

    if (ok)
    {
        QStatus status = controller->SetAutoMode(value);

        if (status != ER_OK)
        {
            qWarning() << "FanSpeedLevel::slotSetAutoMode Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
}
