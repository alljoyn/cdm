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

// This file is automatically generated. Do not edit it.

#ifndef CYCLECONTROLINTFCONTROLLERLISTENER_H_
#define CYCLECONTROLINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/controller/InterfaceControllerListener.h>
#include <interfaces/common/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controller Listener class
 */
class CycleControlIntfControllerListener : public InterfaceControllerListener {
  public:
    using OperationalState = CycleControlInterface::OperationalState;
    using OperationalCommands = CycleControlInterface::OperationalCommands;

    /**
     * Destructor of CycleControlIntfControllerListener
     */
    virtual ~CycleControlIntfControllerListener() {}

    /**
     * Callback handler for GetOperationalState completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of OperationalState
     *                  (Current operational state of the appliance.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetOperationalState(QStatus status, const qcc::String& objectPath, const CycleControlInterface::OperationalState value, void* context) {}

    /**
     * Handler for OperationalState property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of OperationalState
     *                  (Current operational state of the appliance.)
     */
    virtual void OnOperationalStateChanged(const qcc::String& objectPath, const CycleControlInterface::OperationalState value) {}

    /**
     * Callback handler for GetSupportedOperationalStates completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedOperationalStates
     *                  (Operational states which are supported by the appliance.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedOperationalStates(QStatus status, const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalState>& value, void* context) {}

    /**
     * Handler for SupportedOperationalStates property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedOperationalStates
     *                  (Operational states which are supported by the appliance.)
     */
    virtual void OnSupportedOperationalStatesChanged(const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalState>& value) {}

    /**
     * Callback handler for GetSupportedOperationalCommands completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedOperationalCommands
     *                  (Operational commands which are supported by the appliance.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetSupportedOperationalCommands(QStatus status, const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalCommands>& value, void* context) {}

    /**
     * Handler for SupportedOperationalCommands property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of SupportedOperationalCommands
     *                  (Operational commands which are supported by the appliance.)
     */
    virtual void OnSupportedOperationalCommandsChanged(const qcc::String& objectPath, const std::vector<CycleControlInterface::OperationalCommands>& value) {}

    /**
     * Callback handler for ExecuteOperationalCommand completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnResponseExecuteOperationalCommand(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}
};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLERLISTENER_H_ */
