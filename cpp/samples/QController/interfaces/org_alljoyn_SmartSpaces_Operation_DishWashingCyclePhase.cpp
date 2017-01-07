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
#include "org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <sstream>


template<>
QString
QStringFrom<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>(const DishWashingCyclePhaseInterface::CyclePhaseDescriptor& value)
{
    std::ostringstream strm;
    strm << "{";
    strm << "phase=" << value.phase;
    strm << " ";
    strm << "name=" << value.name.c_str();
    strm << " ";
    strm << "description=" << value.description.c_str();
    strm << "}";

    return QString::fromStdString(strm.str());
}


template<>
QString
QStringFrom<std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>>(const std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& value)
{
    std::string result;

    for (auto& v : value)
    {
        auto qs = QStringFrom<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>(v);
        result += qs.toStdString();
    }
    return QString::fromStdString(result);
}





using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase*>();

Q_DECLARE_METATYPE(ajn::services::DishWashingCyclePhaseInterface::CyclePhaseDescriptor);
Q_DECLARE_METATYPE(std::vector<ajn::services::DishWashingCyclePhaseInterface::CyclePhaseDescriptor>);
static const int auto_register_struct_CyclePhaseDescriptor = qRegisterMetaType<ajn::services::DishWashingCyclePhaseInterface::CyclePhaseDescriptor>("DishWashingCyclePhaseInterface::CyclePhaseDescriptor");
static const int auto_register_struct_v_CyclePhaseDescriptor = qRegisterMetaType<std::vector<ajn::services::DishWashingCyclePhaseInterface::CyclePhaseDescriptor>>("std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>");



org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase(CommonControllerInterface *iface)
  : controller(NULL),
    m_listener(mkRef<Listener>(this))
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for GetVendorPhasesDescription
    button_GetVendorPhasesDescription = new QPushButton("GetVendorPhasesDescription");
    button_GetVendorPhasesDescription->setToolTip("Get cycle phases description.");
    QObject::connect(button_GetVendorPhasesDescription, SIGNAL(clicked()), this, SLOT(slotClickGetVendorPhasesDescription()));
    layout->addWidget(button_GetVendorPhasesDescription);

    layout->addWidget(new QLabel("CyclePhase"));
    // Create the editing widget for CyclePhase
    edit_CyclePhase = new QLineEdit();
    edit_CyclePhase->setToolTip("Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer");
    edit_CyclePhase->setReadOnly(true);

    layout->addWidget(edit_CyclePhase);
    layout->addWidget(new QLabel("SupportedCyclePhases"));
    // Create the editing widget for SupportedCyclePhases
    edit_SupportedCyclePhases = new QLineEdit();
    edit_SupportedCyclePhases->setToolTip("List of supported cycle phases.");
    edit_SupportedCyclePhases->setReadOnly(true);

    layout->addWidget(edit_SupportedCyclePhases);

    if (iface)
    {
        controller = iface->CreateInterface<DishWashingCyclePhaseIntfController>(m_listener);
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

org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::~org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::fetchProperties()
{
    // Get current values
    QStatus status;

    if (controller)
    {
        qWarning() << "DishWashingCyclePhase getting properties";

        status = controller->GetCyclePhase();
        if (status != ER_OK)
        {
            qWarning() << "DishWashingCyclePhase::fetchProperties Failed to get CyclePhase" << QCC_StatusText(status);
        }

        status = controller->GetSupportedCyclePhases();
        if (status != ER_OK)
        {
            qWarning() << "DishWashingCyclePhase::fetchProperties Failed to get SupportedCyclePhases" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::slotClickGetVendorPhasesDescription()
{
    qWarning() << "DishWashingCyclePhase::slotClickGetVendorPhasesDescription";

    qcc::String languageTag {};

    bool ok = true;

    if (ok)
    {
        QStatus status = controller->GetVendorPhasesDescription(languageTag, NULL);
        if (status != ER_OK)
        {
            qWarning() << "DishWashingCyclePhase::slotClick Failed to call GetVendorPhasesDescription" << QCC_StatusText(status);
        }
    }
}



void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::slotOnResponseGetCyclePhase(QStatus status, const uint8_t value)
{
    qWarning() << "DishWashingCyclePhase::slotOnResponseGetCyclePhase";

    edit_CyclePhase->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::slotOnCyclePhaseChanged(const uint8_t value)
{
    qWarning() << "DishWashingCyclePhase::slotOnCyclePhaseChanged";

    edit_CyclePhase->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::slotOnResponseGetSupportedCyclePhases(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << "DishWashingCyclePhase::slotOnResponseGetSupportedCyclePhases";

    edit_SupportedCyclePhases->setText(QStringFrom(value));
}



void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::slotOnSupportedCyclePhasesChanged(const std::vector<uint8_t>& value)
{
    qWarning() << "DishWashingCyclePhase::slotOnSupportedCyclePhasesChanged";

    edit_SupportedCyclePhases->setText(QStringFrom(value));
}






void org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase::slotOnResponseMethodGetVendorPhasesDescription(QStatus status, const std::vector<DishWashingCyclePhaseInterface::CyclePhaseDescriptor>& phasesDescription, const QString& errorName)
{
    if (status == ER_OK)
    {
        qInfo() << "DishWashingCyclePhase::slotOnResponseMethodGetVendorPhasesDescription";
    }
    else
    {
        qWarning() << "DishWashingCyclePhase::slotOnResponseMethodGetVendorPhasesDescription Received error = " << errorName;
    }
}
