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

#ifndef ALERTSINTFCONTROLLER_H_
#define ALERTSINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/AlertsInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface Controller class
 */
class AlertsIntfController : public AlertsInterface {
  public:
    /**
     * Constructor of AlertsIntfController
     */
    AlertsIntfController() {}

    /**
     * Destructor of AlertsIntfController
     */
    virtual ~AlertsIntfController() {}

    /**
     * Get Alerts property
     * (List of current pending alerts.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlerts(void* context = NULL) = 0;

    /**
     * Call GetAlertCodesDescription method
     * (Get alert codes description.)
     * @param[in] languageTag Language to be used in the output strings.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetAlertCodesDescription(const qcc::String& languageTag, void* context = NULL) = 0;

    /**
     * Call AcknowledgeAlert method
     * (Reset the user acknowledgment request of a specific pending alert.)
     * @param[in] alertCode Alert code of the alert to be acknowledged.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAlert(const uint16_t alertCode, void* context = NULL) = 0;

    /**
     * Call AcknowledgeAllAlerts method
     * (Reset the user acknowledgment request of any pending alert.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus AcknowledgeAllAlerts(void* context = NULL) = 0;
};

typedef std::shared_ptr<AlertsIntfController> AlertsIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* ALERTSINTFCONTROLLER_H_ */
