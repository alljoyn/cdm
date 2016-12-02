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

#ifndef org_alljoyn_SmartSpaces_Operation_UnlockControl_H_
#define org_alljoyn_SmartSpaces_Operation_UnlockControl_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/UnlockControlInterface.h>
#include <alljoyn/cdm/interfaces/operation/UnlockControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/UnlockControlIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_UnlockControl : public QWidget, public ajn::services::UnlockControlIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_UnlockControl(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_UnlockControl();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickUnlock();


public:
    // ajn::services::UnlockControlIntfControllerListener

private:
    ajn::services::UnlockControlIntfControllerPtr controller;

    QPushButton* button_Unlock;

};

}

#endif /* org_alljoyn_SmartSpaces_Operation_UnlockControl_H_ */
