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

#ifndef AIRRECIRCULATIONMODEINTFCONTROLLERIMPL_H_
#define AIRRECIRCULATIONMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AirRecirculationModeIntfController.h>

namespace ajn {
namespace services {

class AirRecirculationModeIntfControllerListener;
class CdmProxyBusObject;

/**
 * AirRecirculationMode Interface Controller implementation class
 */
class AirRecirculationModeIntfControllerImpl : public InterfaceController, public AirRecirculationModeIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of AirRecirculationModeIntfControllerImpl
     */
    AirRecirculationModeIntfControllerImpl(BusAttachment& busAttachment, AirRecirculationModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of AirRecirculationModeIntfControllerImpl
     */
    virtual ~AirRecirculationModeIntfControllerImpl();

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
     * Set if air is being recirculated
     * @param[in] isRecirculating if air is being recirculated or not
     * @param[in] context
     * @return status
     */
    virtual QStatus SetIsRecirculating(const bool isRecirculating, void* context);

    /**
     * Get if air is being recirculated
     * @param[in] context
     * @return status
     */
    virtual QStatus GetIsRecirculating(void* context);

  private:
    AirRecirculationModeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetIsRecirculatingPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetIsRecirculatingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    AirRecirculationModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* AIRRECIRCULATIONMODEINTFCONTROLLERIMPL_H_ */
