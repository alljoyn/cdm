/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLERIMPL_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/MoistureOutputLevelIntfController.h>

namespace ajn {
namespace services {

class MoistureOutputLevelIntfControllerListener;
class CdmProxyBusObject;

/**
 * MoistureOutputLevel Interface Controller implementation class
 */
class MoistureOutputLevelIntfControllerImpl : public InterfaceController, public MoistureOutputLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of MoistureOutputLevelIntfControllerImpl
     */
    MoistureOutputLevelIntfControllerImpl(BusAttachment& busAttachment, MoistureOutputLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of MoistureOutputLevelIntfControllerImpl
     */
    virtual ~MoistureOutputLevelIntfControllerImpl();

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
     * Get MoistureOutputLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMoistureOutputLevel(void* context);

    /**
     * Set MoistureOutputLevel
     * @param[in] HorizontalDirection
     * @param[in] context
     * @return status
     */
    virtual QStatus SetMoistureOutputLevel(const uint8_t value, void* context);

    /**
     * Get MaxMoistureOutputLevel
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxMoistureOutputLevel(void* context);

    /**
     * Get AutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus GetAutoMode(void* context);

    /**
     * Set AutoMode
     * @param[in] AutoMode
     * @param[in] context
     * @return status
     */
    virtual QStatus SetAutoMode(const uint8_t value, void* context);

  private:
    MoistureOutputLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetMaxMoistureOutputLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetAutoModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    MoistureOutputLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLERIMPL_H_ */