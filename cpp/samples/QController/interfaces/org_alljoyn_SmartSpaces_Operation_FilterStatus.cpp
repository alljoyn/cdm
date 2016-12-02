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

#include "org_alljoyn_SmartSpaces_Operation_FilterStatus.h"
#include "QStringConversion.h"
#include <QDebug>
#include <QLabel>
#include <QPushButton>

using namespace CDMQtWidgets;

static const int auto_register_meta_type = qRegisterMetaType<org_alljoyn_SmartSpaces_Operation_FilterStatus*>();

org_alljoyn_SmartSpaces_Operation_FilterStatus::org_alljoyn_SmartSpaces_Operation_FilterStatus(CommonControllerInterface *iface) : controller(NULL)
{
    qWarning() << __FUNCTION__;

    QVBoxLayout *layout = new QVBoxLayout(this);



    layout->addWidget(new QLabel("ExpectedLifeInDays"));
    // Create line edit for ExpectedLifeInDays
    edit_ExpectedLifeInDays = new QLineEdit();
    edit_ExpectedLifeInDays->setToolTip("Days a new filter will last. Used to convert percentage into remaining days. If 0xFFFF there is no predicted life. If 0 the life is less than 1 day.");
    edit_ExpectedLifeInDays->setReadOnly(true);
    layout->addWidget(edit_ExpectedLifeInDays);
    layout->addWidget(new QLabel("IsCleanable"));
    // Create line edit for IsCleanable
    edit_IsCleanable = new QLineEdit();
    edit_IsCleanable->setToolTip("This is a static property of the filter.  If the property is true a new filter does not need to be ordered, just clean.");
    edit_IsCleanable->setReadOnly(true);
    layout->addWidget(edit_IsCleanable);
    layout->addWidget(new QLabel("OrderPercentage"));
    // Create line edit for OrderPercentage
    edit_OrderPercentage = new QLineEdit();
    edit_OrderPercentage->setToolTip("LifeRemaining it is recommended that a new filter be orderedIt can have a value of 0 because the remaining life is unpredictable, for example a psid switch. It can also have a value of 255 if OrderPercentage is N/A, for example a cleanable filter.");
    edit_OrderPercentage->setReadOnly(true);
    layout->addWidget(edit_OrderPercentage);
    layout->addWidget(new QLabel("Manufacturer"));
    // Create line edit for Manufacturer
    edit_Manufacturer = new QLineEdit();
    edit_Manufacturer->setToolTip("Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.");
    edit_Manufacturer->setReadOnly(true);
    layout->addWidget(edit_Manufacturer);
    layout->addWidget(new QLabel("PartNumber"));
    // Create line edit for PartNumber
    edit_PartNumber = new QLineEdit();
    edit_PartNumber->setToolTip("Identification of the filter manufacturer, which along with the part number act as a tuple to identify the filter within the Alljoyn device. Either one or both may be a null string.");
    edit_PartNumber->setReadOnly(true);
    layout->addWidget(edit_PartNumber);
    layout->addWidget(new QLabel("Url"));
    // Create line edit for Url
    edit_Url = new QLineEdit();
    edit_Url->setToolTip("Url can be just a domain or a complete URL to the exact filter. It may provide additional information of a site for ordering. A null string is acceptable.");
    edit_Url->setReadOnly(true);
    layout->addWidget(edit_Url);
    layout->addWidget(new QLabel("LifeRemaining"));
    // Create line edit for LifeRemaining
    edit_LifeRemaining = new QLineEdit();
    edit_LifeRemaining->setToolTip("Lifespan Remaining in percentage (100 - 0). 0 indicates replace/clean. A simple device may just implement 100/0 or 100/OrderPercentage/0 instead of implementing the entire range of values.");
    edit_LifeRemaining->setReadOnly(true);
    layout->addWidget(edit_LifeRemaining);

    if (iface)
    {
        controller = iface->CreateInterface<FilterStatusIntfController>(*this);
        if (controller)
        {
            qWarning() << __FUNCTION__ << " Getting properties";

            QStatus status;
            // Get current values
            status = controller->GetExpectedLifeInDays();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get ExpectedLifeInDays" << QCC_StatusText(status);
            }
            status = controller->GetIsCleanable();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get IsCleanable" << QCC_StatusText(status);
            }
            status = controller->GetOrderPercentage();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get OrderPercentage" << QCC_StatusText(status);
            }
            status = controller->GetManufacturer();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Manufacturer" << QCC_StatusText(status);
            }
            status = controller->GetPartNumber();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get PartNumber" << QCC_StatusText(status);
            }
            status = controller->GetUrl();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get Url" << QCC_StatusText(status);
            }
            status = controller->GetLifeRemaining();
            if (status != ER_OK)
            {
                qWarning() << __FUNCTION__ << " Failed to get LifeRemaining" << QCC_StatusText(status);
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

org_alljoyn_SmartSpaces_Operation_FilterStatus::~org_alljoyn_SmartSpaces_Operation_FilterStatus()
{
    qWarning() << __FUNCTION__;
}



void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetExpectedLifeInDays(QStatus status, const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_ExpectedLifeInDays->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnExpectedLifeInDaysChanged(const uint16_t value)
{
    qWarning() << __FUNCTION__;
    edit_ExpectedLifeInDays->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetIsCleanable(QStatus status, const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsCleanable->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnIsCleanableChanged(const bool value)
{
    qWarning() << __FUNCTION__;
    edit_IsCleanable->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetOrderPercentage(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_OrderPercentage->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnOrderPercentageChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_OrderPercentage->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetManufacturer(QStatus status, const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_Manufacturer->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnManufacturerChanged(const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_Manufacturer->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetPartNumber(QStatus status, const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_PartNumber->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnPartNumberChanged(const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_PartNumber->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetUrl(QStatus status, const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_Url->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnUrlChanged(const qcc::String& value)
{
    qWarning() << __FUNCTION__;
    edit_Url->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnResponseGetLifeRemaining(QStatus status, const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_LifeRemaining->setText(QStringFrom(value));
}

void org_alljoyn_SmartSpaces_Operation_FilterStatus::slotOnLifeRemainingChanged(const uint8_t value)
{
    qWarning() << __FUNCTION__;
    edit_LifeRemaining->setText(QStringFrom(value));
}

