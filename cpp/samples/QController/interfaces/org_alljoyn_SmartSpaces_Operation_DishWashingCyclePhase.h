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

#ifndef org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase_H_
#define org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfController.h>
#include <alljoyn/cdm/interfaces/operation/DishWashingCyclePhaseIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase : public QWidget, public ajn::services::DishWashingCyclePhaseIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickGetVendorPhasesDescription();

    void slotOnResponseGetCyclePhase(QStatus status, const uint8_t value);
    void slotOnCyclePhaseChanged(const uint8_t value);
    void slotOnResponseGetSupportedCyclePhases(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSupportedCyclePhasesChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::DishWashingCyclePhaseIntfControllerListener
    void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetCyclePhase", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnCyclePhaseChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetSupportedCyclePhases", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }
    void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnSupportedCyclePhasesChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }

private:
    ajn::services::DishWashingCyclePhaseIntfControllerPtr controller;

    QPushButton* button_GetVendorPhasesDescription;

    QLineEdit* edit_CyclePhase;
    QLineEdit* edit_SupportedCyclePhases;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_DishWashingCyclePhase_H_ */
