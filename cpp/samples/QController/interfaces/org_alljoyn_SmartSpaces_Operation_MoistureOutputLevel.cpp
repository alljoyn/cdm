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
#include "org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<MoistureOutputLevelInterface::AutoMode>(const MoistureOutputLevelInterface::AutoMode& value)
{
    QString result;

    switch (value)
    {
    case MoistureOutputLevelInterface::AUTO_MODE_OFF:
        result = "Off";
        break;

    case MoistureOutputLevelInterface::AUTO_MODE_ON:
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
QStringFrom<std::vector<MoistureOutputLevelInterface::AutoMode>>(const std::vector<MoistureOutputLevelInterface::AutoMode>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">AutoMode</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == MoistureOutputLevelInterface::AUTO_MODE_OFF)
        {
            strm << "<tr><td>Off</td></tr>";
        }
        if (v == MoistureOutputLevelInterface::AUTO_MODE_ON)
        {
            strm << "<tr><td>On</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel*>();

Q_DECLARE_METATYPE(ajn::services::MoistureOutputLevelInterface::AutoMode);
Q_DECLARE_METATYPE(std::vector<ajn::services::MoistureOutputLevelInterface::AutoMode>);
static const int auto_register_enum_AutoMode = qRegisterMetaType<ajn::services::MoistureOutputLevelInterface::AutoMode>("MoistureOutputLevelInterface::AutoMode");
static const int auto_register_enum_v_AutoMode = qRegisterMetaType<std::vector<ajn::services::MoistureOutputLevelInterface::AutoMode>>("std::vector<MoistureOutputLevelInterface::AutoMode>");



org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>MoistureOutputLevel</b>"));
    // Create the editing widget for MoistureOutputLevel
    edit_MoistureOutputLevel = new QLineEdit();
    edit_MoistureOutputLevel->setToolTip("Current level of moisture output.");
    QObject::connect(edit_MoistureOutputLevel, SIGNAL(returnPressed()), this, SLOT(slotSetMoistureOutputLevel()));

    layout->addWidget(edit_MoistureOutputLevel);
    layout->addWidget(new QLabel("<b>MaxMoistureOutputLevel</b>"));
    // Create the editing widget for MaxMoistureOutputLevel
    edit_MaxMoistureOutputLevel = new QLabel();

    layout->addWidget(edit_MaxMoistureOutputLevel);
    layout->addWidget(new QLabel("<b>AutoMode</b>"));
    // Create the editing widget for AutoMode
    edit_AutoMode = new QComboBox();
    edit_AutoMode->setEditable(false);
    edit_AutoMode->addItem("Off");
    edit_AutoMode->addItem("On");
    edit_AutoMode->setEnabled(true);
    QObject::connect(edit_AutoMode, SIGNAL(currentTextChanged(const QString &)), this, SLOT(slotSetAutoMode()));

    layout->addWidget(edit_AutoMode);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<MoistureOutputLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::~org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "MoistureOutputLevel getting properties";

        status = controller->GetMoistureOutputLevel();
        if (status != ER_OK)
        {
            qWarning() << "MoistureOutputLevel::fetchProperties Failed to get MoistureOutputLevel" << QCC_StatusText(status);
        }

        status = controller->GetMaxMoistureOutputLevel();
        if (status != ER_OK)
        {
            qWarning() << "MoistureOutputLevel::fetchProperties Failed to get MaxMoistureOutputLevel" << QCC_StatusText(status);
        }

        status = controller->GetAutoMode();
        if (status != ER_OK)
        {
            qWarning() << "MoistureOutputLevel::fetchProperties Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseGetMoistureOutputLevel(QStatus status, const uint8_t value)
{
    qWarning() << "MoistureOutputLevel::slotOnResponseGetMoistureOutputLevel";

    edit_MoistureOutputLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnMoistureOutputLevelChanged(const uint8_t value)
{
    qWarning() << "MoistureOutputLevel::slotOnMoistureOutputLevelChanged";

    edit_MoistureOutputLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseSetMoistureOutputLevel(QStatus status)
{
    qWarning() << "MoistureOutputLevel::slotOnResponseSetMoistureOutputLevel";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set MoistureOutputLevel", status);
        qWarning() << "MoistureOutputLevel::slotOnResponseSetMoistureOutputLevel Failed to set MoistureOutputLevel" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotSetMoistureOutputLevel()
{
    qWarning() << "MoistureOutputLevel::slotSetMoistureOutputLevel";

    bool ok = false;
    uint8_t value;
    QString str = edit_MoistureOutputLevel->text();
    value = QStringTo<uint8_t>(str, &ok);
    if (!ok)
    {
        qWarning() << "MoistureOutputLevel::slotSetMoistureOutputLevel Failed to convert '" << str << "' to uint8_t";
    }

    if (ok)
    {
        QStatus status = controller->SetMoistureOutputLevel(value);

        if (status != ER_OK)
        {
            qWarning() << "MoistureOutputLevel::slotSetMoistureOutputLevel Failed to get MoistureOutputLevel" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseGetMaxMoistureOutputLevel(QStatus status, const uint8_t value)
{
    qWarning() << "MoistureOutputLevel::slotOnResponseGetMaxMoistureOutputLevel";

    edit_MaxMoistureOutputLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnMaxMoistureOutputLevelChanged(const uint8_t value)
{
    qWarning() << "MoistureOutputLevel::slotOnMaxMoistureOutputLevelChanged";

    edit_MaxMoistureOutputLevel->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseGetAutoMode(QStatus status, const MoistureOutputLevelInterface::AutoMode value)
{
    qWarning() << "MoistureOutputLevel::slotOnResponseGetAutoMode";

    switch (value)
    {
    case MoistureOutputLevelInterface::AUTO_MODE_OFF:
        edit_AutoMode->setCurrentText("Off");
        break;

    case MoistureOutputLevelInterface::AUTO_MODE_ON:
        edit_AutoMode->setCurrentText("On");
        break;

    default:
        edit_AutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnAutoModeChanged(const MoistureOutputLevelInterface::AutoMode value)
{
    qWarning() << "MoistureOutputLevel::slotOnAutoModeChanged";

    switch (value)
    {
    case MoistureOutputLevelInterface::AUTO_MODE_OFF:
        edit_AutoMode->setCurrentText("Off");
        break;

    case MoistureOutputLevelInterface::AUTO_MODE_ON:
        edit_AutoMode->setCurrentText("On");
        break;

    default:
        edit_AutoMode->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotOnResponseSetAutoMode(QStatus status)
{
    qWarning() << "MoistureOutputLevel::slotOnResponseSetAutoMode";

    if (status != ER_OK)
    {
        qcShowStatus(this, "Failed to set AutoMode", status);
        qWarning() << "MoistureOutputLevel::slotOnResponseSetAutoMode Failed to set AutoMode" << QCC_StatusText(status);
        fetchProperties();      // restore the display of properties
    }
}



void org_alljoyn_SmartSpaces_Operation_MoistureOutputLevel::slotSetAutoMode()
{
    qWarning() << "MoistureOutputLevel::slotSetAutoMode";

    bool ok = false;
    MoistureOutputLevelInterface::AutoMode value;
    QString str = edit_AutoMode->currentText();
    if (str == "Off")
    {
        value = MoistureOutputLevelInterface::AUTO_MODE_OFF;
        ok = true;
    }
    else
    if (str == "On")
    {
        value = MoistureOutputLevelInterface::AUTO_MODE_ON;
        ok = true;
    }
    else
    if (!str.isEmpty())
    {
        qWarning() << "MoistureOutputLevel::slotSetAutoMode Failed to convert '" << str.constData() << "' to MoistureOutputLevelInterface::AutoMode";
    }

    if (ok)
    {
        QStatus status = controller->SetAutoMode(value);

        if (status != ER_OK)
        {
            qWarning() << "MoistureOutputLevel::slotSetAutoMode Failed to get AutoMode" << QCC_StatusText(status);
        }
    }
}
