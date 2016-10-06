/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef RAPIDMODETIMEDINTFCONTROLLERIMPL_H_
#define RAPIDMODETIMEDINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeTimedIntfController.h>

namespace ajn {
namespace services {

class RapidModeTimedIntfControllerListener;
class CdmProxyBusObject;

/**
 * RapidModeTimed Interface Controller implementation class
 */
class RapidModeTimedIntfControllerImpl : public InterfaceController, public RapidModeTimedIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of RapidModeTimedIntfControllerImpl
     */
    RapidModeTimedIntfControllerImpl(BusAttachment& busAttachment, RapidModeTimedIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of RapidModeTimedIntfControllerImpl
     */
    virtual ~RapidModeTimedIntfControllerImpl();

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
      * Get rapid mode minutes remaining
      * @param[in] context
      * @return status
     */
    virtual QStatus GetRapidModeMinutesRemaining(void* context);

    /**
     * Set rapid mode minutes remaining
     * @param[in] rapid mode minutes remaining
     * @param[in] context
     * @return status
     */
    virtual QStatus SetRapidModeMinutesRemaining(const uint16_t value, void* context);

    /**
      * Get max set minutes
      * @param[in] context
      * @return status
     */
    virtual QStatus GetMaxSetMinutes(void* context);

  private:
    RapidModeTimedIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetRapidModeMinutesRemainingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetRapidModeMinutesRemainingPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMaxSetMinutesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RapidModeTimedIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODETIMEDINTFCONTROLLERIMPL_H_ */