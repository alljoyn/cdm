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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLERLISTENER_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * AirRecirculationMode Interface Controller Listener class
 */
class AirRecirculationModeIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~AirRecirculationModeIntfControllerListener() {}

    /**
     * Callback handler for setting IsRecirculating property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetIsRecirculating(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting IsRecirculating property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] isRecirculating if air is being recirculated or not
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetIsRecirculating(QStatus status, const qcc::String& objectPath, const bool isRecirculating, void* context) {}

    /**
     * Handler for IsRecirculating property changed
     * @param[in] objectPath the object path
     * @param[in] isRecirculating if air is being recirculated or not
     */
    virtual void OnIsRecirculatingChanged(const qcc::String& objectPath, const bool isRecirculating) {}
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLERLISTENER_H_ */
