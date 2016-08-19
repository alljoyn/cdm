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

#ifndef ALERTSINTFCONTROLLERLISTENER_H_
#define ALERTSINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
#include <alljoyn/hae/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface Controller Listener class
 */
class AlertsIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~AlertsIntfControllerListener() {}

    /**
     * Callback handler for getting Alerts property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] alerts the list of alerts
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const AlertsInterface::Alerts& alerts, void* context) {}

    /**
     * Handler for Alerts property changed
     * @param[in] objectPath the object path
     * @param[in] alerts the list of alerts
     */
    virtual void OnAlertsPropertyChanged(const qcc::String& objectPath, const AlertsInterface::Alerts& alerts) {}

    /**
     * Callback handler for GetAlertCodesDescription method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     * @param[out]descriptions list of alert codes descriptions
     */
    virtual void OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const AlertsInterface::AlertCodesDescription& descriptions,
                                                      void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for AcknowledgeAlert method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for AcknowledgeAllAlerts method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseAcknowledgeAllAlerts(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}




};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLERLISTENER_H_ */
