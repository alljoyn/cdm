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

#ifndef org_alljoyn_SmartSpaces_Operation_OnControl_H_
#define org_alljoyn_SmartSpaces_Operation_OnControl_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/OnControlInterface.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/OnControlIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_OnControl : public QWidget, public ajn::services::OnControlIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_OnControl(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_OnControl();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickSwitchOn();


public:
    // ajn::services::OnControlIntfControllerListener

private:
    ajn::services::OnControlIntfControllerPtr controller;

    QPushButton* button_SwitchOn;

};

}

#endif /* org_alljoyn_SmartSpaces_Operation_OnControl_H_ */
