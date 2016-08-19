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

#ifndef WATERLEVELINTFCONTROLLERLISTENER_H_
#define WATERLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelInterface.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface Controller Listener class
 */
class WaterLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~WaterLevelIntfControllerListener() {}

    /**
     * Callback handler for getting MaxLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] maxLevel maxLevel
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}
    /**
     * Callback handler for getting SupplySource property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supplySource supplySource
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetSupplySourcePropertyCallback (QStatus status, const qcc::String& objectPath, const WaterLevelInterface::WaterLevelSupplySource value, void* context) {}
    /**
     * Callback handler for getting CurrentLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] currentLevel currentLevel
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetCurrentLevelPropertyCallback (QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value MaxLevel
     */
    virtual void MaxLevelProprtyChanged(const qcc::String& objectPath, const uint8_t value){}
    /**
     * Handler for CurrentLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value CurrentLevel
     */
    virtual void CurrentLevelProprtyChanged(const qcc::String& objectPath, const uint8_t value){}
    /**
     * Handler for SupplySource property changed
     * @param[in] objectPath the object path
     * @param[in] value SupplySource
     */
    virtual void SupplySourceProprtyChanged(const qcc::String& objectPath, const WaterLevelInterface::WaterLevelSupplySource value){}
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLERLISTENER_H_ */
