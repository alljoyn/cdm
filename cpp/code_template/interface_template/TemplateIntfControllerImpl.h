/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef {interface_nameu}INTFCONTROLLERIMPL_H_
#define {interface_nameu}INTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/{interface_category}/{interface_name}IntfController.h>

namespace ajn {
namespace services {

class {interface_name}IntfControllerListener;
class CdmProxyBusObject;

/**
 * {interface_name} Interface Controller implementation class
 */
class {interface_name}IntfControllerImpl : public InterfaceController, public {interface_name}IntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of {interface_name}IntfControllerImpl
     */
    {interface_name}IntfControllerImpl(BusAttachment& busAttachment, {interface_name}IntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of {interface_name}IntfControllerImpl
     */
    virtual ~{interface_name}IntfControllerImpl();

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
     * TODO: define functions to request the set/get properties
     * GetProperty function of read-only property must not be defined in the controller side.
     */

    /*
     * TODO: define functions to request the method call
     */

  private:
    {interface_name}IntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    /*
     * TODO: define callback fuctions that receive the response of SetProperty/GetProperty
     */

    /*
     * TODO: define method reply handler
     */

    /*
     * TODO: define signal handler
     */

    BusAttachment& m_busAttachment;
    {interface_name}IntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* {interface_nameu}INTFCONTROLLERIMPL_H_ */