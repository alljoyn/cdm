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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLERLISTENER_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/InterfaceControllerListener.h>
#include <alljoyn/hae/interfaces/environment/TargetTemperatureLevelInterface.h>

namespace ajn {
namespace services {

/**
 * TargetTemperatureLevel interface controller listener class
 */
class TargetTemperatureLevelIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TargetTemperatureLevelIntfControllerListener
     */
    virtual ~TargetTemperatureLevelIntfControllerListener() {}

    /**
     * Callback handler for setting TargetValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTargetLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting TargetLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target temperature level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting SelectableTemperatureLevels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the selectable temperature levels
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSelectableTemperatureLevels(QStatus status, const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value, void* context) {}

    /**
     * Handler for TargetLevel property changed
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     */
    virtual void OnTargetLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target temperature level
     */
    virtual void OnMaxLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for SelectableTemperatureLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value the step value of target temperature level
     */
    virtual void OnSelectableTemperatureLevelsChanged(const qcc::String& objectPath, const TargetTemperatureLevelInterface::TemperatureLevels& value) {}
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLERLISTENER_H_ */
