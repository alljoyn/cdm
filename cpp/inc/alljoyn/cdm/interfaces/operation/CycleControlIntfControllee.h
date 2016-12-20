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

#ifndef CYCLECONTROLINTFCONTROLLEE_H_
#define CYCLECONTROLINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {


/**
 * CycleControl Interface Controllee class
 */
class CycleControlIntfControllee : public CycleControlInterface {
  public:
    /**
     * Constructor of CycleControlIntfControllee
     */
    CycleControlIntfControllee() {}

    /**
     * Destructor of CycleControlIntfControllee
     */
    virtual ~CycleControlIntfControllee() {}

    /**
     * Get OpertaionalState
     * @return OpertaionalState
     */
    virtual const CycleControlOperationalState GetOperationalState() const = 0 ;

    /**
     * Set OperationalState
     * @param[in]  state the state to set
     * @return ER_OK on success
     */
    virtual QStatus SetOperationalState(CycleControlOperationalState state) = 0;

    /**
     * Get SupportedCommands
     * @return The list of supported commands
     */
    virtual const SupportedOperationalCommands& GetSupportedCommands() const = 0;

    /**
     * Get SupportedStates
     * @return The list of supported states
     */
    virtual const SupportedOperationalStates& GetSupportedStates() const = 0;
    /**
     * Set SupportedCommands
     * @param[in]  commands the list of commands to set
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedCommands(SupportedOperationalCommands commands) = 0;

    /**
     * Set SupportedStates
     * @param[in]  states the list of states to set
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedStates(SupportedOperationalStates states) = 0;

};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLEE_H_ */