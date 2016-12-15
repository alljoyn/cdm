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

#include "org_alljoyn_SmartSpaces_Operation_PlugInUnits.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>


template<>
QString
QStringFrom<PlugInUnitsInterface::PlugInInfo>(const PlugInUnitsInterface::PlugInInfo& value)
{
    std::ostringstream strm;
    strm << "{";
    strm << "objectPath=" << value.objectPath.c_str();
    strm << " ";
    strm << "deviceId=" << value.deviceId;
    strm << " ";
    strm << "pluggedIn=" << value.pluggedIn;
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<PlugInUnitsInterface::PlugInInfo>>(const std::vector<PlugInUnitsInterface::PlugInInfo>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<PlugInUnitsInterface::PlugInInfo>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}





using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_PlugInUnits*>();


org_alljoyn_SmartSpaces_Operation_PlugInUnits::org_alljoyn_SmartSpaces_Operation_PlugInUnits(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("PlugInUnits"));
    // Create line edit for PlugInUnits
    edit_PlugInUnits = new QLineEdit();
    edit_PlugInUnits->setToolTip("The lists of all the possible hot pluggable devices and the associated status.");
    edit_PlugInUnits->setReadOnly(true);
    layout->addWidget(edit_PlugInUnits);

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
        qWarning() << "org_alljoyn_SmartSpaces_Operation_PlugInUnits getting properties";

        status = controller->GetPlugInUnits();
        if (status != ER_OK)
        {
            qWarning() << __FUNCTION__ << " Failed to get PlugInUnits" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_PlugInUnits::slotOnResponseGetPlugInUnits(QStatus status, const std::vector<PlugInUnitsInterface::PlugInInfo>& value)
{
    qWarning() << __FUNCTION__;
    edit_PlugInUnits->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_PlugInUnits::slotOnPlugInUnitsChanged(const std::vector<PlugInUnitsInterface::PlugInInfo>& value)
{
    qWarning() << __FUNCTION__;
    edit_PlugInUnits->setText(QStringFrom(value));
}
