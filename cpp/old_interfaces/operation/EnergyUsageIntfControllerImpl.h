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

#ifndef ENERGYUSAGEINTFCONTROLLERIMPL_H_
#define ENERGYUSAGEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/EnergyUsageIntfController.h>

namespace ajn {
namespace services {

class EnergyUsageIntfControllerListener;

/**
 * EnergyUsage Interface Controller implementation class
 */
class EnergyUsageIntfControllerImpl : public InterfaceController, public EnergyUsageIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of EnergyUsageIntfControllerImpl
     */
    EnergyUsageIntfControllerImpl(BusAttachment& busAttachment, EnergyUsageIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of EnergyUsageIntfControllerImpl
     */
    virtual ~EnergyUsageIntfControllerImpl();

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
     * Get CumulativeEnergy property
     * (The cumulative energy consumption of the device)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCumulativeEnergy(void* context);

    /**
     * Get Precision property
     * (The precision of the CumulativeEnergy property; i.e., the value the actual energy consumption must change before CumulativeEnergy is updated)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetPrecision(void* context);

    /**
     * Get UpdateMinTime property
     * (The minimum time between updates of the CumulativeEnergy property)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetUpdateMinTime(void* context);

    /**
     * Call ResetCumulativeEnergy method
     * (Resets the value of CumulativeEnergy to 0.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus ResetCumulativeEnergy(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetCumulativeEnergyPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPrecisionPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUpdateMinTimePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void ResetCumulativeEnergyReplyHandler(Message& message, void* context);

    BusAttachment& m_busAttachment;
    EnergyUsageIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* ENERGYUSAGEINTFCONTROLLERIMPL_H_ */