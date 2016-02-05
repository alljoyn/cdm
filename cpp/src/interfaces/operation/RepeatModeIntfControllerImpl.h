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

#ifndef REPEATMODEINTFCONTROLLERIMPL_H_
#define REPEATMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/hae/interfaces/InterfaceController.h>
#include <alljoyn/hae/interfaces/operation/RepeatModeIntfController.h>

namespace ajn {
namespace services {

class RepeatModeIntfControllerListener;
class HaeProxyBusObject;

/**
 * RepeatMode Interface Controller implementation class
 */
class RepeatModeIntfControllerImpl : public InterfaceController, public RepeatModeIntfController {
  public:
    /**
     * Create interface
     */
    static HaeInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Constructor of RepeatModeIntfControllerImpl
     */
    RepeatModeIntfControllerImpl(BusAttachment& busAttachment, RepeatModeIntfControllerListener& listener, HaeProxyBusObject& haeProxyObject);

    /**
     * Destructor of RepeatModeIntfControllerImpl
     */
    virtual ~RepeatModeIntfControllerImpl();

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
     * Get RepeatMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetRepeatMode(void* context = NULL);

    /**
     * Set RepeatMode
     * @param[in] RepeatMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetRepeatMode(const bool value, void* context);

  private:
    RepeatModeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void SetRepeatModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetRepeatModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RepeatModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* REPEATMODEINTFCONTROLLERIMPL_H_ */
