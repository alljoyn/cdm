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

#ifndef TIMEDISPLAYINTFCONTROLLERIMPL_H_
#define TIMEDISPLAYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfController.h>

namespace ajn {
namespace services {

class TimeDisplayIntfControllerListener;

/**
 * TimeDisplay Interface Controller implementation class
 */
class TimeDisplayIntfControllerImpl : public InterfaceController, public TimeDisplayIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of TimeDisplayIntfControllerImpl
     */
    TimeDisplayIntfControllerImpl(BusAttachment& busAttachment, TimeDisplayIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of TimeDisplayIntfControllerImpl
     */
    virtual ~TimeDisplayIntfControllerImpl();

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
     * Get DisplayTimeFormat property
     * (The clock format which is currently used to display time (0=12-hour, 1=24-hour))
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTimeFormat(void* context);

    /**
     * Set DisplayTimeFormat property
     * (The clock format which is currently used to display time (0=12-hour, 1=24-hour))
     * @param[in] value The display time format to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t value, void* context);

    /**
     * Get SupportedDisplayTimeFormats property
     * (List of supported clock formats)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTimeFormats(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetDisplayTimeFormatPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetDisplayTimeFormatPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedDisplayTimeFormatsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TimeDisplayIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLERIMPL_H_ */
