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
#include "org_alljoyn_SmartSpaces_Operation_PlugInUnits.h"
#include "qcUtils.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <sstream>



template<>
QString
QStringFrom<PlugInUnitsInterface::PlugInInfo>(const PlugInUnitsInterface::PlugInInfo& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<b>objectPath</b>: " << value.objectPath.c_str() << "\n";
    strm << "<b>deviceId</b>: " << value.deviceId << "\n";
    strm << "<b>pluggedIn</b>: " << value.pluggedIn << "\n";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<PlugInUnitsInterface::PlugInInfo>>(const std::vector<PlugInUnitsInterface::PlugInInfo>& value)
{
    // the QLabel is AutoFmt 
    std::ostringstream strm;

    strm << "<html><body>";
    strm << "<table><thead><tr>";
    strm << "<th bgcolor=\"light blue\">objectPath</th>";
    strm << "<th bgcolor=\"light blue\">deviceId</th>";
    strm << "<th bgcolor=\"light blue\">pluggedIn</th>";
    strm << "</tr></thead>";

    for (auto& v : value)
    {
        strm << "<tr>";
        strm << "<td>" << v.objectPath.c_str() << "</td>";
        strm << "<td>" << v.deviceId << "</td>";
        strm << "<td>" << v.pluggedIn << "</td>";
        strm << "</tr>";
    }

    strm << "</table></body></html>";
    return QString::fromStdString(strm.str());
}


using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_PlugInUnits*>();

Q_DECLARE_METATYPE(ajn::services::PlugInUnitsInterface::PlugInInfo);
Q_DECLARE_METATYPE(std::vector<ajn::services::PlugInUnitsInterface::PlugInInfo>);
static const int auto_register_struct_PlugInInfo = qRegisterMetaType<ajn::services::PlugInUnitsInterface::PlugInInfo>("PlugInUnitsInterface::PlugInInfo");
static const int auto_register_struct_v_PlugInInfo = qRegisterMetaType<std::vector<ajn::services::PlugInUnitsInterface::PlugInInfo>>("std::vector<PlugInUnitsInterface::PlugInInfo>");



org_alljoyn_SmartSpaces_Operation_PlugInUnits::org_alljoyn_SmartSpaces_Operation_PlugInUnits(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("<b>PlugInUnits</b>"));
    // Create the editing widget for PlugInUnits
    edit_PlugInUnits = new QLabel();

    layout->addWidget(edit_PlugInUnits);

    messages_ = new QLabel();
    layout->addWidget(messages_);

    if (iface)
    {
        controller = iface->CreateInterface<PlugInUnitsIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_PlugInUnits::~org_alljoyn_SmartSpaces_Operation_PlugInUnits()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_PlugInUnits::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "PlugInUnits getting properties";

        status = controller->GetPlugInUnits();
        if (status != ER_OK)
        {
            qWarning() << "PlugInUnits::fetchProperties Failed to get PlugInUnits" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_PlugInUnits::slotOnResponseGetPlugInUnits(QStatus status, const std::vector<PlugInUnitsInterface::PlugInInfo>& value)
{
    qWarning() << "PlugInUnits::slotOnResponseGetPlugInUnits";

    edit_PlugInUnits->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_PlugInUnits::slotOnPlugInUnitsChanged(const std::vector<PlugInUnitsInterface::PlugInInfo>& value)
{
    qWarning() << "PlugInUnits::slotOnPlugInUnitsChanged";

    edit_PlugInUnits->setText(QStringFrom(value));
}



