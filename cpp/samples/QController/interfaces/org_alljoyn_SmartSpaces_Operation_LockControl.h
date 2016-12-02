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

#ifndef org_alljoyn_SmartSpaces_Operation_LockControl_H_
#define org_alljoyn_SmartSpaces_Operation_LockControl_H_

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include <alljoyn/cdm/interfaces/operation/LockControlInterface.h>
#include <alljoyn/cdm/interfaces/operation/LockControlIntfController.h>
#include <alljoyn/cdm/interfaces/operation/LockControlIntfControllerListener.h>
#include "commoncontrollerimpl.h"

using namespace ajn::services;

namespace CDMQtWidgets
{

class org_alljoyn_SmartSpaces_Operation_LockControl : public QWidget, public ajn::services::LockControlIntfControllerListener
{
    Q_OBJECT
public:
    Q_INVOKABLE org_alljoyn_SmartSpaces_Operation_LockControl(CommonControllerInterface *iface=NULL);
    ~org_alljoyn_SmartSpaces_Operation_LockControl();

    // Slots mirror the callbacks to avoid threading issues
private slots:
    void slotClickLock();


public:
    // ajn::services::LockControlIntfControllerListener

private:
    ajn::services::LockControlIntfControllerPtr controller;

    QPushButton* button_Lock;

};

}

#endif /* org_alljoyn_SmartSpaces_Operation_LockControl_H_ */
