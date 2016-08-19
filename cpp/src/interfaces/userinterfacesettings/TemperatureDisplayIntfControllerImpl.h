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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLERIMPL_H_
#define TEMPERATUREDISPLAYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfController.h>

namespace ajn {
namespace services {

class TemperatureDisplayIntfControllerListener;
class CdmProxyBusObject;

/**
 * TemperatureDisplay Interface Controller implementation class
 */
class TemperatureDisplayIntfControllerImpl : public InterfaceController, public TemperatureDisplayIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of TemperatureDisplayIntfControllerImpl
     */
    TemperatureDisplayIntfControllerImpl(BusAttachment& busAttachment, TemperatureDisplayIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of TemperatureDisplayIntfControllerImpl
     */
    virtual ~TemperatureDisplayIntfControllerImpl();

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
     * Get DisplayTemperatureUnit
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTemperatureUnit(void* context = NULL);

    /**
     * Set DisplayTemperatureUnit
     * @param[in] temperatureUnit temperature unit
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t temperatureUnit, void* context = NULL);

    /**
     * Get SupportedDisplayTemperatureUnits
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTemperatureUnits(void* context = NULL);

  private:
    TemperatureDisplayIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedDisplayTemperatureUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TemperatureDisplayIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLERIMPL_H_ */
