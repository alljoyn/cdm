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

#ifndef HIDINTFCONTROLLERIMPL_H_
#define HIDINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/input/HidIntfController.h>

namespace ajn {
namespace services {

class HidIntfControllerListener;

/**
 * Hid Interface Controller implementation class
 */
class HidIntfControllerImpl : public InterfaceController, public HidIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of HidIntfControllerImpl
     */
    HidIntfControllerImpl(BusAttachment& busAttachment, HidIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of HidIntfControllerImpl
     */
    virtual ~HidIntfControllerImpl();

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
     * Get SupportedEvents property
     * (List of supported input events by a device)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedEvents(void* context);

    /**
     * Call InjectEvents method
     * (Inject the user input events for human interface devices)
     * @param[in] inputEvents Injected input event
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus InjectEvents(const std::vector<InputEvent>& inputEvents, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetSupportedEventsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void InjectEventsReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    HidIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLERIMPL_H_ */
