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

#ifndef CYCLECONTROLINTFCONTROLLER_H_
#define CYCLECONTROLINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controller class
 */
class CycleControlIntfController : public CycleControlInterface {
  public:
    /**
     * Constructor of CycleControlIntfController
     */
    CycleControlIntfController() {}

    /**
     * Destructor of CycleControlIntfController
     */
    virtual ~CycleControlIntfController() {}

    /**
     * Get OperationalState property
     * (Current operational state of the appliance.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetOperationalState(void* context = NULL) = 0;

    /**
     * Get SupportedOperationalStates property
     * (Operational states which are supported by the appliance.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedOperationalStates(void* context = NULL) = 0;

    /**
     * Get SupportedOperationalCommands property
     * (Operational commands which are supported by the appliance.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedOperationalCommands(void* context = NULL) = 0;

    /**
     * Call ExecuteOperationalCommand method
     * (Execute an operational command.)
     * @param[in] command Operational command to be executed.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus ExecuteOperationalCommand(const OperationalCommands command, void* context = NULL) = 0;
};

typedef std::shared_ptr<CycleControlIntfController> CycleControlIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLER_H_ */
