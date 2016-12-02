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

#ifndef org_alljoyn_SmartSpaces_Operation_HvacFanMode_H_
#define org_alljoyn_SmartSpaces_Operation_HvacFanMode_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <interfaces/common/operation/HvacFanModeInterface.h>
#include <interfaces/controller/operation/HvacFanModeIntfController.h>
#include <interfaces/controller/operation/HvacFanModeIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_HvacFanMode : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_HvacFanMode(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_HvacFanMode();

    // Slots mirror the callbacks to avoid threading issues
private slots:

    void slotOnResponseGetMode(QStatus status, const HvacFanModeInterface::Mode value);
    void slotOnModeChanged(const HvacFanModeInterface::Mode value);
    void slotOnResponseSetMode(QStatus status);
    void slotSetMode();
    void slotOnResponseGetSupportedModes(QStatus status, const std::vector<HvacFanModeInterface::Mode>& value);
    void slotOnSupportedModesChanged(const std::vector<HvacFanModeInterface::Mode>& value);

public:
    // ajn::services::HvacFanModeIntfControllerListener
    class Listener: public ajn::services::HvacFanModeIntfControllerListener
    {
    public:
        QWidget* m_widget;

        Listener(QWidget* widget)
          : m_widget(widget)
        {
        }

        virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const HvacFanModeInterface::Mode value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(HvacFanModeInterface::Mode, value)
                              );
        }
        virtual void OnModeChanged(const qcc::String& objectPath, const HvacFanModeInterface::Mode value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnModeChanged", Qt::QueuedConnection,
                              Q_ARG(HvacFanModeInterface::Mode, value)
                              );
        }
        virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseSetMode", Qt::QueuedConnection,
                              Q_ARG(QStatus, status)
                              );
        }
        virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const std::vector<HvacFanModeInterface::Mode>& value, void* context) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnResponseGetSupportedModes", Qt::QueuedConnection,
                              Q_ARG(QStatus, status),
                              Q_ARG(std::vector<HvacFanModeInterface::Mode>, value)
                              );
        }
        virtual void OnSupportedModesChanged(const qcc::String& objectPath, const std::vector<HvacFanModeInterface::Mode>& value) override
        {
            qWarning() << __FUNCTION__;
            QMetaObject::invokeMethod(m_widget, "slotOnSupportedModesChanged", Qt::QueuedConnection,
                              Q_ARG(std::vector<HvacFanModeInterface::Mode>, value)
                              );
        }
    };

private:
    Ref<ajn::services::HvacFanModeIntfController> controller;
    Ref<Listener> m_listener;


    QLineEdit* edit_Mode;
    QLineEdit* edit_SupportedModes;
};

}

#endif /* org_alljoyn_SmartSpaces_Operation_HvacFanMode_H_ */
