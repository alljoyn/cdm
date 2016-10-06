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

#ifndef ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEE_H_
#define ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/RobotCleaningCyclePhaseInterface.h>

namespace ajn {
namespace services {

/**
 * RobotCleaningCyclePhase Interface Controllee class
 */
class RobotCleaningCyclePhaseIntfControllee : public RobotCleaningCyclePhaseInterface {
  public:
    /**
     * Constructor of RobotCleaningCyclePhaseIntfControllee
     */
    RobotCleaningCyclePhaseIntfControllee() {}

    /**
     * Destructor of RobotCleaningCyclePhaseIntfControllee
     */
    virtual ~RobotCleaningCyclePhaseIntfControllee() {}

    /**
     * Get cycle phase
     * @return Cycle phase
     */
    virtual const uint8_t GetCyclePhase() const = 0;

    /**
     * Set cycle phase
     * @param[in] cyclePhase cycle phase
     * @return ER_OK on success
     */
    virtual QStatus SetCyclePhase(uint8_t cyclePhase) = 0;

    /**
     * Get supported cycle phases
     * @return Supported cycle phases
     */
    virtual const SupportedCyclePhases& GetSupportedCyclePhases() const = 0;

    /**
     * Set supported cycle phases
     * @param[in] supportedCyclePhases supported cycle phases
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedCyclePhases(const SupportedCyclePhases& supportedCyclePhases) = 0;
};

} //namespace services
} //namespace ajn

#endif /* ROBOTCLEANINGCYCLEPHASEINTFCONTROLLEE_H_ */