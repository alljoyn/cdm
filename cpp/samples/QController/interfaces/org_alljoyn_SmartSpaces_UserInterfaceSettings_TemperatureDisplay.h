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

#ifndef org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay_H_
#define org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/userinterfacesettings/TemperatureDisplayInterface.h>
#include <interfaces/controller/userinterfacesettings/TemperatureDisplayIntfController.h>
#include <interfaces/controller/userinterfacesettings/TemperatureDisplayIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetDisplayTemperatureUnit(QStatus status, const uint8_t value);
    void slotOnDisplayTemperatureUnitChanged(const uint8_t value);
    void slotOnResponseSetDisplayTemperatureUnit(QStatus status);
    void slotSetDisplayTemperatureUnit();
    void slotOnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const std::vector<uint8_t>& value);
    void slotOnSupportedDisplayTemperatureUnitsChanged(const std::vector<uint8_t>& value);

public:
    // ajn::services::TemperatureDisplayIntfControllerListener
    class Listener: public ajn::services::TemperatureDisplayIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetDisplayTemperatureUnit", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnDisplayTemperatureUnitChanged(const qcc::String& objectPath, const uint8_t value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnDisplayTemperatureUnitChanged", Qt::QueuedConnection,
                              Q_ARG(uint8_t, value)
                              );
        }
        virtual void OnResponseSetDisplayTemperatureUnit(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetDisplayTemperatureUnit", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSupportedDisplayTemperatureUnits(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedDisplayTemperatureUnits", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
        virtual void OnSupportedDisplayTemperatureUnitsChanged(const qcc::String& objectPath, const std::vector<uint8_t>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedDisplayTemperatureUnitsChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<uint8_t>, value)
                              );
        }
    };

private:
    Ref<ajn::services::TemperatureDisplayIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_DisplayTemperatureUnit;
    QLineEdit* edit_SupportedDisplayTemperatureUnits;

    void    fetchProperties();

protected:
    virtual void showEvent(QShowEvent *event) override
    {
        fetchProperties();
    }
};

}

#endif /* org_alljoyn_SmartSpaces_UserInterfaceSettings_TemperatureDisplay_H_ */
