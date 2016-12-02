/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase*>();

org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);


    // Create button for GetVendorPhasesDescription
    button_GetVendorPhasesDescription = new QPushButton("GetVendorPhasesDescription");
    button_GetVendorPhasesDescription->setToolTip("Get cycle phases description.");
    QObject::connect(button_GetVendorPhasesDescription, SIGNAL(clicked()), this, SLOT(slotClickGetVendorPhasesDescription()));
    layout->addWidget(button_GetVendorPhasesDescription);

    layout->addWidget(new QLabel("CyclePhase"));
    // Create line edit for CyclePhase
    edit_CyclePhase = new QLineEdit();
    edit_CyclePhase->setToolTip("Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer.");
    edit_CyclePhase->setReadOnly(true);
    layout->addWidget(edit_CyclePhase);
    layout->addWidget(new QLabel("SupportedCyclePhases"));
    // Create line edit for SupportedCyclePhases
    edit_SupportedCyclePhases = new QLineEdit();
    edit_SupportedCyclePhases->setToolTip("List of supported cycle phases.");
    edit_SupportedCyclePhases->setReadOnly(true);
    layout->addWidget(edit_SupportedCyclePhases);

    if (iface)
    {
        controller = iface->CreateInterface<RobotCleaningCyclePhaseIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetCyclePhase();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get CyclePhase" << QCC_StatusText(status);
            }
            status = controller->GetSupportedCyclePhases();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get SupportedCyclePhases" << QCC_StatusText(status);
            }
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

org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::~org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase()
{
    qWarning() << __FUNCTION__;
}

void org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::slotClickGetVendorPhasesDescription()
{
    qWarning() << __FUNCTION__;

    qcc::String languageTag {};

    QStatus status = controller->GetVendorPhasesDescription(languageTag, NULL);
    if (status != ER_OK)
    {
        qWarning() << __FUNCTION__ << " Failed to call GetVendorPhasesDescription" << QCC_StatusText(status);
    }
}


void org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::slotOnResponseGetCyclePhase(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CyclePhase->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::slotOnCyclePhaseChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_CyclePhase->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::slotOnResponseGetSupportedCyclePhases(QStatus status, const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedCyclePhases->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase::slotOnSupportedCyclePhasesChanged(const std::vector<uint8_t>& value)
{
    qWarning() << __FUNCTION__;
    edit_SupportedCyclePhases->setText(QStringFrom(value));
}
