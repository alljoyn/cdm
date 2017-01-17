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

#ifndef WINDDIRECTIONINTFCONTROLLER_H_
#define WINDDIRECTIONINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <interfaces/common/environment/WindDirectionInterface.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface Controller class
 */
class WindDirectionIntfController : public WindDirectionInterface {
  public:
    /**
     * The LSF translater inherits and redefines this class.
     * Also std:make_shared needs this to be public.
     */
    WindDirectionIntfController(
        BusAttachment& busAttachment,
        Ref<InterfaceControllerListener> listener,
        Ref<ProxyBusObject> cdmProxyObject
        );

    /**
     * Destructor of WindDirectionIntfController
     */
    virtual ~WindDirectionIntfController();

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
     * Get HorizontalDirection property
     * (Horizontal wind direction of a device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalDirection(void* context = NULL);

    /**
     * Set HorizontalDirection property
     * (Horizontal wind direction of a device.)
     * @param[in] value The horizontal direction to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalDirection(const uint16_t value, void* context = NULL);

    /**
     * Get HorizontalMax property
     * (Maximum value allowed for a target horizontal wind direction.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalMax(void* context = NULL);

    /**
     * Get HorizontalAutoMode property
     * (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalAutoMode(void* context = NULL);

    /**
     * Set HorizontalAutoMode property
     * (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] value The horizontal auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalAutoMode(const WindDirectionInterface::AutoMode value, void* context = NULL);

    /**
     * Get VerticalDirection property
     * (Vertical wind direction of a device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalDirection(void* context = NULL);

    /**
     * Set VerticalDirection property
     * (Vertical wind direction of a device.)
     * @param[in] value The vertical direction to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalDirection(const uint16_t value, void* context = NULL);

    /**
     * Get VerticalMax property
     * (Maximum value allowed for a target vertical wind direction.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalMax(void* context = NULL);

    /**
     * Get VerticalAutoMode property
     * (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalAutoMode(void* context = NULL);

    /**
     * Set VerticalAutoMode property
     * (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] value The vertical auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalAutoMode(const WindDirectionInterface::AutoMode value, void* context = NULL);

  private:

    class Impl;

    Impl* m_impl;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLER_H_ */
