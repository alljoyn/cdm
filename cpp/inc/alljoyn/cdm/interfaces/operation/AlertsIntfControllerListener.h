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
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface Controller Listener class
 */
class AlertsIntfControllerListener : public InterfaceControllerListener {
  public:
    using Severity = AlertsInterface::Severity;
    using AlertRecord = AlertsInterface::AlertRecord;
    using AlertCodesDescriptor = AlertsInterface::AlertCodesDescriptor;

    /**
     * Destructor of AlertsIntfControllerListener
     */
    virtual ~AlertsIntfControllerListener() {}

    /**
     * Callback handler for GetAlerts completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of Alerts
     *                  (List of current pending alerts.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAlerts(QStatus status, const qcc::String& objectPath, const std::vector<AlertRecord>& value, void* context) {}

    /**
     * Handler for Alerts property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of Alerts
     *                  (List of current pending alerts.)
     */
    virtual void OnAlertsChanged(const qcc::String& objectPath, const std::vector<AlertRecord>& value) {}

    /**
     * Callback handler for GetAlertCodesDescription completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] description Alert codes description.
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseGetAlertCodesDescription(QStatus status, const qcc::String& objectPath, const std::vector<AlertCodesDescriptor>& description, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for AcknowledgeAlert completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseAcknowledgeAlert(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Callback handler for AcknowledgeAllAlerts completion
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
