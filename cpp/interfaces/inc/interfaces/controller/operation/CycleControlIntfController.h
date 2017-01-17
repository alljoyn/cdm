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

// This file is automatically generated. Do not edit it.

#ifndef CYCLECONTROLINTFCONTROLLER_H_
#define CYCLECONTROLINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <interfaces/common/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controller class
 */
class CycleControlIntfController : public CycleControlInterface {
  public:
    /**
     * The LSF translater inherits and redefines this class.
     * Also std:make_shared needs this to be public.
     */
    CycleControlIntfController(
        BusAttachment& busAttachment,
        Ref<InterfaceControllerListener> listener,
        Ref<ProxyBusObject> cdmProxyObject
        );

    /**
     * Destructor of CycleControlIntfController
     */
    virtual ~CycleControlIntfController();

    /**
     * Create interface
     */
    static Ref<CdmInterface> CreateInterface(BusAttachment& busAttachment, Ref<InterfaceControllerListener> listener, Ref<ProxyBusObject> ProxyBusObject);

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init() override;

    virtual BusAttachment& GetBusAttachment() const override;



    /**
     * Get OperationalState property
     * (Current operational state of the appliance.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOperationalState(void* context = NULL);

    /**
     * Get SupportedOperationalStates property
     * (Operational states which are supported by the appliance.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedOperationalStates(void* context = NULL);

    /**
     * Get SupportedOperationalCommands property
     * (Operational commands which are supported by the appliance.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedOperationalCommands(void* context = NULL);

    /**
     * Call ExecuteOperationalCommand method
     * (Execute an operational command.)
     * @param[in] command Operational command to be executed.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus ExecuteOperationalCommand(const CycleControlInterface::OperationalCommands command, void* context = NULL);

  private:

    class Impl;

    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLER_H_ */
