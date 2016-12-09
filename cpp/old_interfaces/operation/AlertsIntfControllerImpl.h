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

#ifndef ALERTSINTFCONTROLLERIMPL_H_
#define ALERTSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AlertsIntfController.h>

namespace ajn {
namespace services {

class AlertsIntfControllerListener;

/**
 * Alerts Interface Controller implementation class
 */
class AlertsIntfControllerImpl : public InterfaceController, public AlertsIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of AlertsIntfControllerImpl
     */
    AlertsIntfControllerImpl(BusAttachment& busAttachment, AlertsIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of AlertsIntfControllerImpl
     */
    virtual ~AlertsIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get Alerts property
     * (List of current pending alerts.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlerts(void* context);

    /**
     * Call GetAlertCodesDescription method
     * (Get alert codes description.)
     * @param[in] languageTag Language to be used in the output strings.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlertCodesDescription(const qcc::String& languageTag, void* context);

    /**
     * Call AcknowledgeAlert method
     * (Reset the user acknowledgment request of a specific pending alert.)
     * @param[in] alertCode Alert code of the alert to be acknowledged.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAlert(const uint16_t alertCode, void* context);

    /**
     * Call AcknowledgeAllAlerts method
     * (Reset the user acknowledgment request of any pending alert.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAllAlerts(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetAlertsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetAlertCodesDescriptionReplyHandler(Message& message, void* context);
    void AcknowledgeAlertReplyHandler(Message& message, void* context);
    void AcknowledgeAllAlertsReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    AlertsIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLERIMPL_H_ */