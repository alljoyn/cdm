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

#ifndef org_alljoyn_SmartSpaces_Operation_HeatingZone_H_
#define org_alljoyn_SmartSpaces_Operation_HeatingZone_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/HeatingZoneInterface.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfController.h>
#include <alljoyn/cdm/interfaces/operation/HeatingZoneIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_HeatingZone : public QWidget, public ajn::services::HeatingZoneIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_HeatingZone(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_HeatingZone();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetNumberOfHeatingZones(QStatus status, const uint8_t value);
    void slotOnNumberOfHeatingZonesChanged(const uint8_t value);
    void slotOnResponseGetMaxHeatingLevels(QStatus status, const std::vector<uint8_t>& value);
    void slotOnMaxHeatingLevelsChanged(const std::vector<uint8_t>& value);
    void slotOnResponseGetHeatingLevels(QStatus status, const std::vector<uint8_t>& value);
    void slotOnHeatingLevelsChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::HeatingZoneIntfControllerListener
    void OnResponseGetNumberOfHeatingZones(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetNumberOfHeatingZones", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnNumberOfHeatingZonesChanged(const qcc::String& objectPath, const uint8_t value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnNumberOfHeatingZonesChanged", Qt::QueuedConnection,
                          Q_ARG(uint8_t, value)
                          );
    }
    void OnResponseGetMaxHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetMaxHeatingLevels", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }
    void OnMaxHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnMaxHeatingLevelsChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }
    void OnResponseGetHeatingLevels(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnResponseGetHeatingLevels", Qt::QueuedConnection,
                          Q_ARG(QStatus, status),
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }
    void OnHeatingLevelsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value)
    {
        qWarning() << __FUNCTION__;
        QMetaObject::invokeMethod(this, "slotOnHeatingLevelsChanged", Qt::QueuedConnection,
                          Q_ARG(std::vector<uint8_t>, value)
                          );
    }

private:
    ajn::services::HeatingZoneIntfControllerPtr controller;


    QLineEdit* edit_NumberOfHeatingZones;
    QLineEdit* edit_MaxHeatingLevels;
    QLineEdit* edit_HeatingLevels;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_HeatingZone_H_ */
