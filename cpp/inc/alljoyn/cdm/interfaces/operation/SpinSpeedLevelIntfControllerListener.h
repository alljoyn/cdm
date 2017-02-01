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

#ifndef SPINSPEEDLEVELINTFCONTROLLERLISTENER_H_
#define SPINSPEEDLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <vector>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * SpinSpeedLevel Interface Controller Listener class
 */
class SpinSpeedLevelIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~SpinSpeedLevelIntfControllerListener() {}

    /**
     * Callback handler for getting MaxLevel
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] maxLevel maxLevel
     * @param[in] context the context that is passed from application
     */
    virtual void GetMaxLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t maxLevel, void* context) {};

    /**
     * Callback handler for getting TargetLevel
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] targetLevel targetLevel
     * @param[in] context the context that is passed from application
     */
    virtual void GetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t targetLevel, void* context) {};

    /**
     * Callback handler for setting TargetLevel
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] targetLevel targetLevel
     * @param[in] context the context that is passed from application
     */
    virtual void SetTargetLevelPropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {};

    /**
     * Callback handler for getting SelectableLevels
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] selectableLevels selectableLevels
     * @param[in] context the context that is passed from application
     */
    virtual void GetSelectableLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels, void* context) {};

    /**
     * Handler for MaxLevel property changed
     * @param[in] objectPath the object path
     * @param[in] maxLevel maxLevel
     */
    virtual void MaxLevelPropertyChanged(const qcc::String& objectPath, const uint8_t maxLevel) {};

    /**
     * Handler for TargetLevel property changed
     * @param[in] objectPath the object path
     * @param[in] targetLevel targetLevel
     */
    virtual void TargetLevelPropertyChanged(const qcc::String& objectPath, const uint8_t targetLevel) {};

    /**
     * Handler for SelectableLevels property changed
     * @param[in] objectPath the object path
     * @param[in] selectableLevels selectableLevels
     */
    virtual void SelectableLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& selectableLevels) {};
};

} //namespace services
} //namespace ajn

#endif /* SPINSPEEDLEVELINTFCONTROLLERLISTENER_H_ */