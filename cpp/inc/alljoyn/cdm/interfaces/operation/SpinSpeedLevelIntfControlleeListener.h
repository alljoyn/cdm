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

#ifndef SPINSPEEDLEVELINTFCONTROLLEELISTENER_H_
#define SPINSPEEDLEVELINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <vector>
#include <alljoyn/cdm/interfaces/CdmInterfaceErrors.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * SpinSpeedLevel Interface Controllee Listener class
 */
class SpinSpeedLevelIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of SpinSpeedLevelIntfControlleeListener
     */
    virtual ~SpinSpeedLevelIntfControlleeListener() {}

    /**
     * Handler for getting MaxLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetMaxLevel(uint8_t& maxLevel) = 0;

    /**
     * Handler for setting MaxLevel
     * @param[in] maxLevel maxLevel
     * @return ER_OK on success
     */
    virtual QStatus OnSetMaxLevel(const uint8_t& maxLevel) = 0;

    /**
     * Handler for getting TargetLevel
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] targetLevel targetLevel
     * @return ER_OK on success
     */
    virtual QStatus OnGetTargetLevel(uint8_t& targetLevel) = 0;

    /**
     * Handler for setting TargetLevel
     * @param[in] targetLevel targetLevel
     * @return ER_OK on success
     */
    virtual QStatus OnSetTargetLevel(const uint8_t& targetLevel) = 0;

    /**
     * Handler for getting SelectableLevels
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] selectableLevels the list of selectable levels
     * @return ER_OK on success
     */
    virtual QStatus OnGetSelectableLevels(std::vector<uint8_t>& selectableLevels) = 0;

    /**
     * Handler for setting SelectableLevels
     * @param[in] selectableLevels the list of selectable levels
     * @return ER_OK on success
     */
    virtual QStatus OnSetSelectableLevels(const std::vector<uint8_t>& selectableLevels) = 0;
};

} //namespace services
} //namespace ajn

#endif /* SPINSPEEDLEVELINTFCONTROLLEELISTENER_H_ */