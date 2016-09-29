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

#ifndef WINDDIRECTIONINTFCONTROLLERIMPL_H_
#define WINDDIRECTIONINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionIntfController.h>

namespace ajn {
namespace services {

class WindDirectionIntfControllerListener;
class CdmProxyBusObject;

/**
 * WindDirection Interface Controller implementation class
 */
class WindDirectionIntfControllerImpl : public InterfaceController, public WindDirectionIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Constructor of WindDirectionIntfControllerImpl
     */
    WindDirectionIntfControllerImpl(BusAttachment& busAttachment, WindDirectionIntfControllerListener& listener, CdmProxyBusObject& cdmProxyBusObject);

    /**
     * Destructor of WindDirectionIntfControllerImpl
     */
    virtual ~WindDirectionIntfControllerImpl();

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
     * Get HorizontalDirection property
     * (Horizontal wind direction of a device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalDirection(void* context);

    /**
     * Set HorizontalDirection property
     * (Horizontal wind direction of a device.)
     * @param[in] value The horizontal direction to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalDirection(const uint16_t value, void* context);

    /**
     * Get HorizontalMax property
     * (Maximum value allowed for a target horizontal wind direction.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalMax(void* context);

    /**
     * Get HorizontalAutoMode property
     * (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalAutoMode(void* context);

    /**
     * Set HorizontalAutoMode property
     * (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] value The horizontal auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalAutoMode(const AutoMode value, void* context);

    /**
     * Get VerticalDirection property
     * (Vertical wind direction of a device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalDirection(void* context);

    /**
     * Set VerticalDirection property
     * (Vertical wind direction of a device.)
     * @param[in] value The vertical direction to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalDirection(const uint16_t value, void* context);

    /**
     * Get VerticalMax property
     * (Maximum value allowed for a target vertical wind direction.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalMax(void* context);

    /**
     * Get VerticalAutoMode property
     * (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalAutoMode(void* context);

    /**
     * Set VerticalAutoMode property
     * (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] value The vertical auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalAutoMode(const AutoMode value, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetHorizontalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVerticalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);

    BusAttachment& m_busAttachment;
    WindDirectionIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLERIMPL_H_ */
