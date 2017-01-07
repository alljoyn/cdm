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

#ifndef org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase_H_
#define org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase_H_

#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/RobotCleaningCyclePhaseInterface.h>
#include <interfaces/controller/operation/RobotCleaningCyclePhaseIntfController.h>
#include <interfaces/controller/operation/RobotCleaningCyclePhaseIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;


namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickGetVendorPhasesDescription();

    void slotOnResponseGetCyclePhase(QStatus status, const uint8_t value);
    void slotOnCyclePhaseChanged(const uint8_t value);
    void slotOnResponseGetSupportedCyclePhases(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSupportedCyclePhasesChanged(const std::vector<uint8_t>& value);
    void slotOnResponseMethodGetVendorPhasesDescription(QStatus status, const std::vector<RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor>& phasesDescription, const QString& errorName);

public:
    // ajn::services::RobotCleaningCyclePhaseIntfControllerListener
    class Listener: public ajn::services::RobotCleaningCyclePhaseIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetCyclePhase(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << "RobotCleaningCyclePhase::OnResponseGetCyclePhase";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetCyclePhase", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnCyclePhaseChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << "RobotCleaningCyclePhase::OnCyclePhaseChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnCyclePhaseChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseGetSupportedCyclePhases(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) override
        {
            qWarning() << "RobotCleaningCyclePhase::OnResponseGetSupportedCyclePhases";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedCyclePhases", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
        virtual void OnSupportedCyclePhasesChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) override
        {
            qWarning() << "RobotCleaningCyclePhase::OnSupportedCyclePhasesChanged";
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedCyclePhasesChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
        virtual void OnResponseGetVendorPhasesDescription(QStatus status, const qcc::String& objectPath, const std::vector<RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor>& phasesDescription, void* context, const char* errorName, const char* errorMessage) override
        {
            qWarning() << "RobotCleaningCyclePhase::OnResponseGetVendorPhasesDescription";
            QMetaObject::invokeMethod(m_widget, "slotOnResponseMethodGetVendorPhasesDescription", Qt::QueuedConnection,
                              Q_ARG(QStatus, status), Q_ARG(std::vector<RobotCleaningCyclePhaseInterface::CyclePhaseDescriptor>, phasesDescription), Q_ARG(QString, QString(errorName))
                              );
        }
    };

private:
    Ref<ajn::services::RobotCleaningCyclePhaseIntfController> controller;
    Ref<Listener> m_listener;

    QPushButton* button_GetVendorPhasesDescription;

    QLineEdit* edit_CyclePhase;
    QLineEdit* edit_SupportedCyclePhases;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_RobotCleaningCyclePhase_H_ */
