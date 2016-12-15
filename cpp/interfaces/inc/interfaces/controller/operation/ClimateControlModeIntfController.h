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

// This file is automatically generated. Do not edit it.

#ifndef CLIMATECONTROLMODEINTFCONTROLLER_H_
#define CLIMATECONTROLMODEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <interfaces/common/operation/ClimateControlModeInterface.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode Interface Controller class
 */
class ClimateControlModeIntfController : public ClimateControlModeInterface {
  public:
    /**
     * The LSF translater inherits and redefines this class.
     * Also std:make_shared needs this to be public.
     */
    ClimateControlModeIntfController(
        BusAttachment& busAttachment,
        Ref<InterfaceControllerListener> listener,
        Ref<ProxyBusObject> cdmProxyObject
        );

    /**
     * Destructor of ClimateControlModeIntfController
     */
    virtual ~ClimateControlModeIntfController();

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
     * Get Mode property
     * (Current mode of device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetMode(void* context = NULL);

    /**
     * Set Mode property
     * (Current mode of device.)
     * @param[in] value The mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetMode(const ClimateControlModeInterface::Mode value, void* context = NULL);

    /**
     * Get SupportedModes property
     * (Array of supported modes.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedModes(void* context = NULL);

    /**
     * Get OperationalState property
     * (Current status of device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOperationalState(void* context = NULL);

  private:

    class Impl;

    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLER_H_ */