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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLERLISTENER_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * CurrentAirQualityLevel Interface Controller Listener class
 */
class CurrentAirQualityLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~CurrentAirQualityLevelIntfControllerListener() {}

    /**
     * Callback handler for getting ContaminantType property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value contaminant type
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetContaminantType(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting CurrentLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value air quality level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum level of air quality
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for ContaminantType property changed
     * @param[in] objectPath the object path
     * @param[in] value air quality
     */
    virtual void OnContaminantTypeChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for CurrentLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value air quality
     */
    virtual void OnCurrentLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of air quality
     */
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) {}


};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLERLISTENER_H_ */
