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

#ifndef CURRENTAIRQUALITYLEVELINTFCONTROLLERIMPL_H_
#define CURRENTAIRQUALITYLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/environment/CurrentAirQualityLevelIntfController.h>

namespace ajn {
namespace services {

class CurrentAirQualityLevelIntfControllerListener;
class HaeProxyBusObject;

/**
 * CurrentAirQualityLevel Interface Controller implementation class
 */
class CurrentAirQualityLevelIntfControllerImpl : public InterfaceController, public CurrentAirQualityLevelIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of CurrentAirQualityLevelIntfControllerImpl
     */
    CurrentAirQualityLevelIntfControllerImpl(BusAttachment& busAttachment, CurrentAirQualityLevelIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of CurrentAirQualityLevelIntfControllerImpl
     */
    virtual ~CurrentAirQualityLevelIntfControllerImpl();

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
     * Get ContaminantType
     * @param[in] context
     * @return status
     */
    QStatus GetContaminantType(void* context);

    /**
     * Get CurrentVale
     * @param[in] context
     * @return status
     */
    QStatus GetCurrentLevel(void* context);

    /**
     * Get MaxLevel
     * @param[in] context
     * @return status
     */
    QStatus GetMaxLevel(void* context);

  private:
    CurrentAirQualityLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetContaminantTypePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    CurrentAirQualityLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CURRENTAIRQUALITYLEVELINTFCONTROLLERIMPL_H_ */
