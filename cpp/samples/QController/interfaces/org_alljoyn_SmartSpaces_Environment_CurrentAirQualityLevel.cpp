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
#include "org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<CurrentAirQualityLevelInterface::ContaminantType>(const CurrentAirQualityLevelInterface::ContaminantType& value)
{
    QString result;

    switch (value)
    {
    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH2O:
        result = "CH2O";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO2:
        result = "CO2";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO:
        result = "CO";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM2_5:
        result = "PM2_5";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM10:
        result = "PM10";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_VOC:
        result = "VOC";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_SMOKE:
        result = "Smoke";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_ODOR:
        result = "Odor";
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_AIR_POLLUTION:
        result = "AirPollution";
        break;

    default:
        result = "Unknown";
        break;
    }

    return result;
}



template<>
QString
QStringFrom<std::vector<CurrentAirQualityLevelInterface::ContaminantType>>(const std::vector<CurrentAirQualityLevelInterface::ContaminantType>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">ContaminantType</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH2O)
        {
            strm << "<tr><td>CH2O</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO2)
        {
            strm << "<tr><td>CO2</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO)
        {
            strm << "<tr><td>CO</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM2_5)
        {
            strm << "<tr><td>PM2_5</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM10)
        {
            strm << "<tr><td>PM10</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_VOC)
        {
            strm << "<tr><td>VOC</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_SMOKE)
        {
            strm << "<tr><td>Smoke</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_ODOR)
        {
            strm << "<tr><td>Odor</td></tr>";
        }
        if (v == CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_AIR_POLLUTION)
        {
            strm << "<tr><td>AirPollution</td></tr>";
        }
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel*>();

Q_DECLARE_METATYPE(ajn::services::CurrentAirQualityLevelInterface::ContaminantType);
Q_DECLARE_METATYPE(std::vector<ajn::services::CurrentAirQualityLevelInterface::ContaminantType>);
static const int auto_register_enum_ContaminantType = qRegisterMetaType<ajn::services::CurrentAirQualityLevelInterface::ContaminantType>("CurrentAirQualityLevelInterface::ContaminantType");
static const int auto_register_enum_v_ContaminantType = qRegisterMetaType<std::vector<ajn::services::CurrentAirQualityLevelInterface::ContaminantType>>("std::vector<CurrentAirQualityLevelInterface::ContaminantType>");



org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>ContaminantType</b>"));
    // Create the editing widget for ContaminantType
    edit_ContaminantType = new QComboBox();
    edit_ContaminantType->setEditable(false);
    edit_ContaminantType->addItem("CH2O");
    edit_ContaminantType->addItem("CO2");
    edit_ContaminantType->addItem("CO");
    edit_ContaminantType->addItem("PM2_5");
    edit_ContaminantType->addItem("PM10");
    edit_ContaminantType->addItem("VOC");
    edit_ContaminantType->addItem("Smoke");
    edit_ContaminantType->addItem("Odor");
    edit_ContaminantType->addItem("AirPollution");
    edit_ContaminantType->setEnabled(false);

    layout->addWidget(edit_ContaminantType);
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
        controller = iface->CreateInterface<CurrentAirQualityLevelIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::~org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "CurrentAirQualityLevel getting properties";

        status = controller->GetContaminantType();
        if (status != ER_OK)
        {
            qWarning() << "CurrentAirQualityLevel::fetchProperties Failed to get ContaminantType" << QCC_StatusText(status);
        }

        status = controller->GetCurrentLevel();
        if (status != ER_OK)
        {
            qWarning() << "CurrentAirQualityLevel::fetchProperties Failed to get CurrentLevel" << QCC_StatusText(status);
        }

        status = controller->GetMaxLevel();
        if (status != ER_OK)
        {
            qWarning() << "CurrentAirQualityLevel::fetchProperties Failed to get MaxLevel" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnResponseGetContaminantType(QStatus status, const CurrentAirQualityLevelInterface::ContaminantType value)
{
    qWarning() << "CurrentAirQualityLevel::slotOnResponseGetContaminantType";

    switch (value)
    {
    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH2O:
        edit_ContaminantType->setCurrentText("CH2O");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO2:
        edit_ContaminantType->setCurrentText("CO2");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO:
        edit_ContaminantType->setCurrentText("CO");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM2_5:
        edit_ContaminantType->setCurrentText("PM2_5");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM10:
        edit_ContaminantType->setCurrentText("PM10");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_VOC:
        edit_ContaminantType->setCurrentText("VOC");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_SMOKE:
        edit_ContaminantType->setCurrentText("Smoke");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_ODOR:
        edit_ContaminantType->setCurrentText("Odor");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_AIR_POLLUTION:
        edit_ContaminantType->setCurrentText("AirPollution");
        break;

    default:
        edit_ContaminantType->setCurrentText("");
        break;
    }
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnContaminantTypeChanged(const CurrentAirQualityLevelInterface::ContaminantType value)
{
    qWarning() << "CurrentAirQualityLevel::slotOnContaminantTypeChanged";

    switch (value)
    {
    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CH2O:
        edit_ContaminantType->setCurrentText("CH2O");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO2:
        edit_ContaminantType->setCurrentText("CO2");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_CO:
        edit_ContaminantType->setCurrentText("CO");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM2_5:
        edit_ContaminantType->setCurrentText("PM2_5");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_PM10:
        edit_ContaminantType->setCurrentText("PM10");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_VOC:
        edit_ContaminantType->setCurrentText("VOC");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_SMOKE:
        edit_ContaminantType->setCurrentText("Smoke");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_ODOR:
        edit_ContaminantType->setCurrentText("Odor");
        break;

    case CurrentAirQualityLevelInterface::CONTAMINANT_TYPE_AIR_POLLUTION:
        edit_ContaminantType->setCurrentText("AirPollution");
        break;

    default:
        edit_ContaminantType->setCurrentText("");
        break;
    }
}






void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnResponseGetCurrentLevel(QStatus status, const uint8_t value)
{
    qWarning() << "CurrentAirQualityLevel::slotOnResponseGetCurrentLevel";

    edit_CurrentLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnCurrentLevelChanged(const uint8_t value)
{
    qWarning() << "CurrentAirQualityLevel::slotOnCurrentLevelChanged";

    edit_CurrentLevel->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnResponseGetMaxLevel(QStatus status, const uint8_t value)
{
    qWarning() << "CurrentAirQualityLevel::slotOnResponseGetMaxLevel";

    edit_MaxLevel->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Environment_CurrentAirQualityLevel::slotOnMaxLevelChanged(const uint8_t value)
{
    qWarning() << "CurrentAirQualityLevel::slotOnMaxLevelChanged";

    edit_MaxLevel->setText(QStringFrom(value));
}



