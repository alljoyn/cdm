/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef RESOURCESAVINGINTFCONTROLLERIMPL_H_
#define RESOURCESAVINGINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/ResourceSavingIntfController.h>

namespace ajn {
namespace services {

class ResourceSavingIntfControllerListener;
class CdmProxyBusObject;

/**
 * ResourceSaving interface controller implementation class
 */
class ResourceSavingIntfControllerImpl : public InterfaceController, public ResourceSavingIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);


    /**
     * Constructor of ResourceSavingIntfControllerImpl
     */
    ResourceSavingIntfControllerImpl(BusAttachment& busAttachment, ResourceSavingIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of ResourceSavingIntfControlleeImpl
     */
    virtual ~ResourceSavingIntfControllerImpl();

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
     * Set ResouceSaving Mode
     * @param[in] mode
     * @return status
     */
    virtual QStatus SetResourceSavingMode(const bool mode, void* context );

    /**
     * Get ResourceSaving mode
     * @return ResourceSavingMode
     */
    virtual QStatus GetResourceSavingMode( void* context );

  private:
    ResourceSavingIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetResourceSavingModePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    ResourceSavingIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* RESOURCESAVINGINTFCONTROLLERIMPL_H_ */