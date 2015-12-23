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

#ifndef ONOFFSTATUSINTFCONTROLLERIMPL_H_
#define ONOFFSTATUSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/OnOffStatusIntfController.h>

namespace ajn {
namespace services {

class OnOffStatusIntfControllerListener;
class HaeProxyBusObject;

/**
 * OnOffStatus Interface Controller implementation class
 */
class OnOffStatusIntfControllerImpl : public InterfaceController, public OnOffStatusIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of OnOffStatusIntfControllerImpl
     */
    OnOffStatusIntfControllerImpl(BusAttachment& busAttachment, OnOffStatusIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of OnOffStatusIntfControllerImpl
     */
    virtual ~OnOffStatusIntfControllerImpl();

    /**
     * Get OnOff
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOnOff(void* context);

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
     * TODO: define set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */

    /*
     * TODO: define methods
     */

  private:
    OnOffStatusIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetOnOffPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    OnOffStatusIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ONOFFSTATUSINTFCONTROLLERIMPL_H_ */
