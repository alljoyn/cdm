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

#ifndef RAPIDMODEINTFCONTROLLERIMPL_H_
#define RAPIDMODEINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/RapidModeIntfController.h>

namespace ajn {
namespace services {

class RapidModeIntfControllerListener;
class CdmProxyBusObject;

/**
 * RapidMode Interface Controller implementation class
 */
class RapidModeIntfControllerImpl : public InterfaceController, public RapidModeIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of RapidModeIntfControllerImpl
     */
    RapidModeIntfControllerImpl(BusAttachment& busAttachment, RapidModeIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of RapidModeIntfControllerImpl
     */
    virtual ~RapidModeIntfControllerImpl();

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
     * Get RapidMode
     * @param[in] context the context that is passed to the callback handler
     * return ER_OK on successful
     */
    virtual QStatus GetRapidMode(void* context = NULL);

    /**
     * Set RapidMode
     * @param[in] rapidMode rapid mode
     * @param[in] context the context that is passed to the callback handler
     * return ER_OK on successful
     */
    virtual QStatus SetRapidMode(const bool rapidMode, void* context = NULL);

  private:
    RapidModeIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void SetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetRapidModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    RapidModeIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLERIMPL_H_ */