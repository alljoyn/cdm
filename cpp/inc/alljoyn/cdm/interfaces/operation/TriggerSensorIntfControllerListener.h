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

#ifndef TRIGGERSENSORINTFCONTROLLERLISTENER_H_
#define TRIGGERSENSORINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/TriggerSensorInterface.h>

namespace ajn {
namespace services {

/**
 * TriggerSensor Interface Controller Listener class
 */
class TriggerSensorIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TriggerSensorIntfControllerListener
     */
    virtual ~TriggerSensorIntfControllerListener() {}

    /**
     * Callback handler for GetCurrentlyTriggered completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentlyTriggered
     *                  (The current status of the sensor's trigger.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetCurrentlyTriggered(QStatus status, const qcc::String& objectPath, const bool value, void* context) {}

    /**
     * Handler for CurrentlyTriggered property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of CurrentlyTriggered
     *                  (The current status of the sensor's trigger.)
     */
    virtual void OnCurrentlyTriggeredChanged(const qcc::String& objectPath, const bool value) {}
};

} //namespace services
} //namespace ajn

#endif /* TRIGGERSENSORINTFCONTROLLERLISTENER_H_ */
