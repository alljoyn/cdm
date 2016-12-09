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

#ifndef TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_
#define TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/TargetTemperatureLevelIntfController.h>

namespace ajn {
namespace services {

class TargetTemperatureLevelIntfControllerListener;

/**
 * TargetTemperatureLevel Interface Controller implementation class
 */
class TargetTemperatureLevelIntfControllerImpl : public InterfaceController, public TargetTemperatureLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of TargetTemperatureLevelIntfControllerImpl
     */
    TargetTemperatureLevelIntfControllerImpl(BusAttachment& busAttachment, TargetTemperatureLevelIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of TargetTemperatureLevelIntfControllerImpl
     */
    virtual ~TargetTemperatureLevelIntfControllerImpl();

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
     * Get MaxLevel property
     * (Maximum value allowed for target temperature level setting.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMaxLevel(void* context);

    /**
     * Get TargetLevel property
     * (Target set-point value of temperature level.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTargetLevel(void* context);

    /**
     * Set TargetLevel property
     * (Target set-point value of temperature level.)
     * @param[in] value The target level to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetTargetLevel(const uint8_t value, void* context);

    /**
     * Get SelectableTemperatureLevels property
     * (List of the values of temperature level which can be selected.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSelectableTemperatureLevels(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetTargetLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSelectableTemperatureLevelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TargetTemperatureLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TARGETTEMPERATURELEVELINTFCONTROLLERIMPL_H_ */