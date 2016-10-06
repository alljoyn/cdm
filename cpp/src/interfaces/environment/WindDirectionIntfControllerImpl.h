/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
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
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of WindDirectionIntfControllerImpl
     */
    WindDirectionIntfControllerImpl(BusAttachment& busAttachment, WindDirectionIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

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
     * Get HorizontalDirection
     * @param[in] context
     * @return status
     */
    virtual QStatus GetHorizontalDirection(void* context);

    /**
     * Set HorizontalDirection
     * @param[in] HorizontalDirection
     * @param[in] context
     * @return status
     */
    virtual QStatus SetHorizontalDirection(const uint16_t value, void* context);

    /**
     * Get HorizontalMax
     * @param[in] context
     * @return status
     */
    virtual QStatus GetHorizontalMax(void* context);

    /**
     * Get HorizontalAutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetHorizontalAutoMode(void* context);

    /**
     * Set HorizontalAutoMode
     * @param[in] HorizontalAutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetHorizontalAutoMode(const uint8_t value, void* context);

    /**
     * Get VerticalDirection
     * @param[in] context
     * @return status
     */
    virtual QStatus GetVerticalDirection(void* context);

    /**
     * Set VerticalDirection
     * @param[in] VerticalDirection
     * @param[in] context
     * @return status
     */
    virtual QStatus SetVerticalDirection(const uint16_t value, void* context);

    /**
     * Get VerticalMax
     * @param[in] context
     * @return status
     */
    virtual QStatus GetVerticalMax(void* context);

    /**
     * Get VerticalAutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetVerticalAutoMode(void* context);

    /**
     * Set VerticalAutoMode
     * @param[in] VerticalAutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetVerticalAutoMode(const uint8_t value, void* context);


  private:
    WindDirectionIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetHorizontalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetHorizontalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetHorizontalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    void SetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVerticalDirectionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetVerticalMaxPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetVerticalAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    WindDirectionIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLERIMPL_H_ */