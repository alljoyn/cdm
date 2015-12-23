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

#ifndef ONCONTROLINTFCONTROLLERIMPL_H_
#define ONCONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/OnControlIntfController.h>

namespace ajn {
namespace services {

class OnControlIntfControllerListener;
class HaeProxyBusObject;

/**
 * OnControl Interface Controller implementation class
 */
class OnControlIntfControllerImpl : public InterfaceController, public OnControlIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of OnControlIntfControllerImpl
     */
    OnControlIntfControllerImpl(BusAttachment& busAttachment, OnControlIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of OnControlIntfControllerImpl
     */
    virtual ~OnControlIntfControllerImpl();

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
    * Switch On
    * @param[in] context
    * @return status
    */
    virtual QStatus SwitchOn(void* context);

  private:
    OnControlIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SwitchOnReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    OnControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ONCONTROLINTFCONTROLLERIMPL_H_ */
