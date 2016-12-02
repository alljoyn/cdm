/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef CYCLECONTROLINTFCONTROLLEELISTENER_H_
#define CYCLECONTROLINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceErrors.h>
#include <alljoyn/cdm/controllee/InterfaceControlleeModel.h>

#include <alljoyn/cdm/controllee/CdmControlleeInterface.h>
#include <interfaces/common/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Model Interface class for the Controllee
 */
class CycleControlIntfControlleeModel : public virtual InterfaceControlleeModel {
  public:
    using OperationalState = CycleControlInterface::OperationalState;
    using OperationalCommands = CycleControlInterface::OperationalCommands;

    /**
     * Destructor of CycleControlIntfControlleeModel
     */
    virtual ~CycleControlIntfControlleeModel() {}

    /**
     * Get OperationalState
     * @return current operational state
     */
    virtual QStatus GetOperationalState(OperationalState& out) const = 0;
    /**
     * Get SupportedOperationalStates
     * @return current supported operational states
     */
    virtual QStatus GetSupportedOperationalStates(std::vector<OperationalState>& out) const = 0;
    /**
     * Get SupportedOperationalCommands
     * @return current supported operational commands
     */
    virtual QStatus GetSupportedOperationalCommands(std::vector<OperationalCommands>& out) const = 0;

    /**
     * Handler for method ExecuteOperationalCommand
     * @param[out] error Internal error code occurred during command execution
     * @return ER_OK on success
     */
    virtual QStatus ExecuteOperationalCommand(OperationalCommands arg_command, ErrorCode& error, CdmSideEffects& sideEffects) = 0;
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLEELISTENER_H_ */
