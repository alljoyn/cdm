/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
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

#ifndef TARGETHUMIDITYINTFCONTROLLERLISTENER_H_
#define TARGETHUMIDITYINTFCONTROLLERLISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/TargetHumidityInterface.h>

namespace ajn {
namespace services {

/**
 * TargetHumidity interface controller listener class
 */
class TargetHumidityIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of TargetHumidityIntfControllerListener
     */
    virtual ~TargetHumidityIntfControllerListener() {}

    /**
     * Callback handler for setting TargetValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetTargetValue(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting TargetValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetTargetValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MinValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the minimum value of target humidity
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMinValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting MaxValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target humidity
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting StepValue property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the step value of target humidity
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetStepValue(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting SelectableHumidityLevels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the selectable humidity levels
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSelectableHumidityLevels(QStatus status, const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value, void* context) {}

    /**
     * Handler for TargetValue property changed
     * @param[in] objectPath the object path
     * @param[in] TargetValue
     */
    virtual void OnTargetValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MinValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the minimum value of target humidity
     */
    virtual void OnMinValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum value of target humidity
     */
    virtual void OnMaxValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for StepValue property changed
     * @param[in] objectPath the object path
     * @param[in] value the step value of target humidity
     */
    virtual void OnStepValueChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for SelectableHumidityLevels property changed
     * @param[in] objectPath the object path
     * @param[in] value the step value of target humidity
     */
    virtual void OnSelectableHumidityLevelsChanged(const qcc::String& objectPath, const TargetHumidityInterface::HumidityLevels& value) {}
};

} //namespace services
} //namespace ajn

#endif /* TARGETHUMIDITYINTFCONTROLLERLISTENER_H_ */