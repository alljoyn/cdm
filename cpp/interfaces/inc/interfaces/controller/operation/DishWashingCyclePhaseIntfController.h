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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

// This file is automatically generated. Do not edit it.

#ifndef DISHWASHINGCYCLEPHASEINTFCONTROLLER_H_
#define DISHWASHINGCYCLEPHASEINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <interfaces/common/operation/DishWashingCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * DishWashingCyclePhase Interface Controller class
 */
class DishWashingCyclePhaseIntfController : public DishWashingCyclePhaseInterface {
  public:
    /**
     * The LSF translater inherits and redefines this class.
     * Also std:make_shared needs this to be public.
     */
    DishWashingCyclePhaseIntfController(
        BusAttachment& busAttachment,
        Ref<InterfaceControllerListener> listener,
        Ref<ProxyBusObject> cdmProxyObject
        );

    /**
     * Destructor of DishWashingCyclePhaseIntfController
     */
    virtual ~DishWashingCyclePhaseIntfController();

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
     * Get CyclePhase property
     * (Current cycle phase. Range value [0x00-0x7F] is for standard phases; range value [0x80-0xFF] is for vendor-defined phases and so the meanings depend on manufacturer)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetCyclePhase(void* context = NULL);

    /**
     * Get SupportedCyclePhases property
     * (List of supported cycle phases.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedCyclePhases(void* context = NULL);

    /**
     * Call GetVendorPhasesDescription method
     * (Get cycle phases description.)
     * @param[in] languageTag Preferred language to use in selecting output strings.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVendorPhasesDescription(const qcc::String& languageTag, void* context = NULL);

  private:

    class Impl;

    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* DISHWASHINGCYCLEPHASEINTFCONTROLLER_H_ */