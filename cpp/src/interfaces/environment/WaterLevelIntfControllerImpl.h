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

#ifndef WATERLEVELINTFCONTROLLERIMPL_H_
#define WATERLEVELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/environment/WaterLevelIntfController.h>

namespace ajn {
namespace services {

class WaterLevelIntfControllerListener;
class CdmProxyBusObject;

/**
 * WaterLevel Interface Controller implementation class
 */
class WaterLevelIntfControllerImpl : public InterfaceController, public WaterLevelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of WaterLevelIntfControllerImpl
     */
    WaterLevelIntfControllerImpl(BusAttachment& busAttachment, WaterLevelIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of WaterLevelIntfControllerImpl
     */
    virtual ~WaterLevelIntfControllerImpl();

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
     * Get current water level
     * @param[in] context
     * @return status
     */
    virtual QStatus GetCurrentLevel(void* context = NULL);

    /**
     * Get supply source
     * @param[in] context
     * @return status
     */
    virtual QStatus GetSupplySource(void* context = NULL);

    /**
     * Get max level
     * @param[in] context
     * @return status
     */
    virtual QStatus GetMaxLevel(void* context = NULL);

  private:
    WaterLevelIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void OnGetMaxLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void OnGetCurrentLevelPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void OnGetSupplySourcePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);


    BusAttachment& m_busAttachment;
    WaterLevelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTFCONTROLLERIMPL_H_ */