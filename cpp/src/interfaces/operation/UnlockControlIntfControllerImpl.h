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

#ifndef UNLOCKCONTROLINTFCONTROLLERIMPL_H_
#define UNLOCKCONTROLINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/UnlockControlIntfController.h>

namespace ajn {
namespace services {

class UnlockControlIntfControllerListener;

/**
 * UnlockControl Interface Controller implementation class
 */
class UnlockControlIntfControllerImpl : public InterfaceController, public UnlockControlIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of UnlockControlIntfControllerImpl
     */
    UnlockControlIntfControllerImpl(BusAttachment& busAttachment, UnlockControlIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of UnlockControlIntfControllerImpl
     */
    virtual ~UnlockControlIntfControllerImpl();

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
     * Call Unlock method
     * (Disengage the locking mechanism.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus Unlock(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void UnlockReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    UnlockControlIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* UNLOCKCONTROLINTFCONTROLLERIMPL_H_ */
