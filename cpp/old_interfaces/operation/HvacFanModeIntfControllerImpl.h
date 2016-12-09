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

#ifndef HVACFANMODEINTFCONTROLLERIMPL_H_
#define HVACFANMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/HvacFanModeIntfController.h>

namespace ajn {
namespace services {

class HvacFanModeIntfControllerListener;

/**
 * HvacFanMode Interface Controller implementation class
 */
class HvacFanModeIntfControllerImpl : public InterfaceController, public HvacFanModeIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of HvacFanModeIntfControllerImpl
     */
    HvacFanModeIntfControllerImpl(BusAttachment& busAttachment, HvacFanModeIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of HvacFanModeIntfControllerImpl
     */
    virtual ~HvacFanModeIntfControllerImpl();

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
     * Get Mode property
     * (Current mode of device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMode(void* context);

    /**
     * Set Mode property
     * (Current mode of device.)
     * @param[in] value The mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const Mode value, void* context);

    /**
     * Get SupportedModes property
     * (Array of supported modes.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedModes(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedModesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    HvacFanModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* HVACFANMODEINTFCONTROLLERIMPL_H_ */