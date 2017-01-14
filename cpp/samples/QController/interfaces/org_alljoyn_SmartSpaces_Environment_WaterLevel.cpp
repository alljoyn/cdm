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
#include "org_alljoyn_SmartSpaces_Environment_WaterLevel.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<WaterLevelInterface::SupplySource>(const WaterLevelInterface::SupplySource& value)
{
    QString result;

    switch (value)
    {
    case WaterLevelInterface::SUPPLY_SOURCE_TANK:
        result = "Tank";
        break;

    case WaterLevelInterface::SUPPLY_SOURCE_PIPE:
        result = "Pipe";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<WaterLevelInterface::SupplySource>>(const std::vector<WaterLevelInterface::SupplySource>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">SupplySource</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == WaterLevelInterface::SUPPLY_SOURCE_TANK)
        {
            strm << "<tr><td>Tank</td></tr>";
        }
        if (v == WaterLevelInterface::SUPPLY_SOURCE_PIPE)
        {
            strm << "<tr><td>Pipe</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_WaterLevel*>();

Q_DECLARE_METATYPE(ajn::services::WaterLevelInterface::SupplySource);
Q_DECLARE_METATYPE(std::vector<ajn::services::WaterLevelInterface::SupplySource>);
static const int auto_register_enum_SupplySource = qRegisterMetaType<ajn::services::WaterLevelInterface::SupplySource>("WaterLevelInterface::SupplySource");
static const int auto_register_enum_v_SupplySource = qRegisterMetaType<std::vector<ajn::services::WaterLevelInterface::SupplySource>>("std::vector<WaterLevelInterface::SupplySource>");



org_alljoyn_SmartSpaces_Environment_WaterLevel::org_alljoyn_SmartSpaces_Environment_WaterLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>SupplySource</b>"));
    // Create the editing widget for SupplySource
    edit_SupplySource = new QComboBox();
    edit_SupplySource->setEditable(false);
    edit_SupplySource->addItem("Tank");
    edit_SupplySource->addItem("Pipe");
    edit_SupplySource->setEnabled(false);

    layout->addWidget(edit_SupplySource);
    layout->addWidget(new QLabel("<b>CurrentLevel</b>"));
    // Create the editing widget for CurrentLevel
    edit_CurrentLevel = new QLabel();

    layout->addWidget(edit_CurrentLevel);
    layout->addWidget(new QLabel("<b>MaxLevel</b>"));
    // Create the editing widget for MaxLevel
    edit_MaxLevel = new QLabel();

    layout->addWidget(edit_MaxLevel);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<WaterLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_WaterLevel::~org_alljoyn_SmartSpaces_Environment_WaterLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_WaterLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "WaterLevel getting properties";

        status = controller->GetSupplySource();
        if (status != ER_OK)
        {
            qWarning() << "WaterLevel::fetchProperties Failed to get SupplySource" << QCC_StatusText(status);
        }

        status = controller->GetCurrentLevel();
        if (status != ER_OK)
        {
            qWarning() << "WaterLevel::fetchProperties Failed to get CurrentLevel" << QCC_StatusText(status);
        }

        status = controller->GetMaxLevel();
        if (status != ER_OK)
        {
            qWarning() << "WaterLevel::fetchProperties Failed to get MaxLevel" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnResponseGetSupplySource(QStatus status, const WaterLevelInterface::SupplySource value)
{
    qWarning() << "WaterLevel::slotOnResponseGetSupplySource";

    switch (value)
    {
    case WaterLevelInterface::SUPPLY_SOURCE_TANK:
        edit_SupplySource->setCurrentText("Tank");
        break;

    case WaterLevelInterface::SUPPLY_SOURCE_PIPE:
        edit_SupplySource->setCurrentText("Pipe");
        break;

    default:
        edit_SupplySource->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnSupplySourceChanged(const WaterLevelInterface::SupplySource value)
{
    qWarning() << "WaterLevel::slotOnSupplySourceChanged";

    switch (value)
    {
    case WaterLevelInterface::SUPPLY_SOURCE_TANK:
        edit_SupplySource->setCurrentText("Tank");
        break;

    case WaterLevelInterface::SUPPLY_SOURCE_PIPE:
        edit_SupplySource->setCurrentText("Pipe");
        break;

    default:
        edit_SupplySource->setCurrentText("");
        break;
    }
}






void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnResponseGetCurrentLevel(QStatus status, const uint8_t value)
{
    qWarning() << "WaterLevel::slotOnResponseGetCurrentLevel";

    edit_CurrentLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnCurrentLevelChanged(const uint8_t value)
{
    qWarning() << "WaterLevel::slotOnCurrentLevelChanged";

    edit_CurrentLevel->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnResponseGetMaxLevel(QStatus status, const uint8_t value)
{
    qWarning() << "WaterLevel::slotOnResponseGetMaxLevel";

    edit_MaxLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_WaterLevel::slotOnMaxLevelChanged(const uint8_t value)
{
    qWarning() << "WaterLevel::slotOnMaxLevelChanged";

    edit_MaxLevel->setText(QStringFrom(value));
}



