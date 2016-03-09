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

#ifndef RAPIDMODEINTFCONTROLLERIMPL_H_
#define RAPIDMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/RapidModeIntfController.h>

namespace ajn {
namespace services {

class RapidModeIntfControllerListener;
class HaeProxyBusObject;

/**
 * RapidMode Interface Controller implementation class
 */
class RapidModeIntfControllerImpl : public InterfaceController, public RapidModeIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of RapidModeIntfControllerImpl
     */
    RapidModeIntfControllerImpl(BusAttachment& busAttachment, RapidModeIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of RapidModeIntfControllerImpl
     */
    virtual ~RapidModeIntfControllerImpl();

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
     * Get RapidMode
     * @param[in] context the context that is passed to the callback handler
     * return ER_OK on successful
     */
    virtual QStatus GetRapidMode(void* context = NULL);

    /**
     * Set RapidMode
     * @param[in] rapidMode rapid mode
     * @param[in] context the context that is passed to the callback handler
     * return ER_OK on successful
     */
    virtual QStatus SetRapidMode(const bool rapidMode, void* context = NULL);

  private:
    RapidModeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void SetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RapidModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLERIMPL_H_ */
