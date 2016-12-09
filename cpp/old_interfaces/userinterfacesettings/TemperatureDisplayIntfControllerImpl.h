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

#ifndef TEMPERATUREDISPLAYINTFCONTROLLERIMPL_H_
#define TEMPERATUREDISPLAYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TemperatureDisplayIntfController.h>

namespace ajn {
namespace services {

class TemperatureDisplayIntfControllerListener;

/**
 * TemperatureDisplay Interface Controller implementation class
 */
class TemperatureDisplayIntfControllerImpl : public InterfaceController, public TemperatureDisplayIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of TemperatureDisplayIntfControllerImpl
     */
    TemperatureDisplayIntfControllerImpl(BusAttachment& busAttachment, TemperatureDisplayIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of TemperatureDisplayIntfControllerImpl
     */
    virtual ~TemperatureDisplayIntfControllerImpl();

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
     * Get DisplayTemperatureUnit property
     * (The unit being used to display temperature (0=C, 1=F, 2 =K))
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTemperatureUnit(void* context);

    /**
     * Set DisplayTemperatureUnit property
     * (The unit being used to display temperature (0=C, 1=F, 2 =K))
     * @param[in] value The display temperature unit to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTemperatureUnit(const uint8_t value, void* context);

    /**
     * Get SupportedDisplayTemperatureUnits property
     * (List of supported temperature units)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTemperatureUnits(void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetDisplayTemperatureUnitPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedDisplayTemperatureUnitsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TemperatureDisplayIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TEMPERATUREDISPLAYINTFCONTROLLERIMPL_H_ */