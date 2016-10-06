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

#ifndef CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_
#define CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * ClimateControlMode interface controller listener class
 */
class ClimateControlModeIntfControllerListener : public InterfaceControllerListener {
  public:
    typedef std::vector<uint16_t> SupportedModes;

    /**
     * Destructor of ClimateControlModeIntfControllerListener
     */
    virtual ~ClimateControlModeIntfControllerListener() {}

    /**
     * Callback handler for setting Mode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting Mode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMode(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Callback handler for getting SupportedModes property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value supported mdoes
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedModes(QStatus status, const qcc::String& objectPath, const SupportedModes& value, void* context) {}

    /**
     * Callback handler for getting OperationalState property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value operational state
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for Mode property changed
     * @param[in] objectPath the object path
     * @param[in] value mode
     */
    virtual void OnModeChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Handler for SupportedModes property changed
     * @param[in] objectPath the object path
     * @param[in] value supported modes
     */
    virtual void OnSupportedModesChanged(const qcc::String& objectPath, const SupportedModes& value) {}

    /**
     * Handler for OperationalState property changed
     * @param[in] objectPath the object path
     * @param[in] value operational state
     */
    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const uint16_t value) {}

};

} //namespace services
} //namespace ajn

#endif /* CLIMATECONTROLMODEINTFCONTROLLERLISTENER_H_ */