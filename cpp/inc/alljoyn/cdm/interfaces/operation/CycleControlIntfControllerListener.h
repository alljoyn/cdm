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

#ifndef CYCLECONTROLINTFCONTROLLERLISTENER_H_
#define CYCLECONTROLINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/operation/CycleControlInterface.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface Controller Listener class
 */
class CycleControlIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~CycleControlIntfControllerListener() {}

    /**
     * Callback handler for getting OperaionalState property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] currentState current state
     * @param[in] context the context that is passed from application
     */
    virtual void GetOperationalStatePropertyCallback(QStatus status, const qcc::String& objectPath, const CycleControlInterface::CycleControlOperationalState& currentState, void* context) {}

    /**
     * Callback handler for getting SupportedOperationalStates property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] states The list of states
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedStatesPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states, void* context) {}

    /**
     * Callback handler for getting SupportedOpearionalCommands property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] commands The list of commands
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedCommandsPropertyCallbalck(QStatus status, const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands, void* context) {}

    /**
     * Handler for OperationalState property changed
     * @param[in] objectPath the object path
     * @param[in] currentState current state
     */
    virtual void OperationalStatePropertyChanged(const qcc::String& objectPath, const CycleControlInterface::CycleControlOperationalState& currentState) {}

    /**
     * Handler for SupportedOperationalStates property changed
     * @param[in] objectPath the object path
     * @param[in] states The list of states
     */
    virtual void SupportedOperationalStatesProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalStates& states) {}

    /**
     * Handler for SupportedOperationalCommands property changed
     * @param[in] objectPath the object path
     * @param[in] commands The list of commands
     */
    virtual void SupportedOperationalCommandsProperyChanged(const qcc::String& objectPath, const CycleControlInterface::SupportedOperationalCommands& commands) {}

    /**
     * Callback handler for ExecuteCommand method
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     * @param[in] errorName the detail errorName is passed when the method call is failed
     * @param[in] errorMessage the errorMessage that describes the error
     */
    virtual void OnExecuteCommandRespose(QStatus status, const qcc::String& objectPath, void* context, const char* errorName, const char* errorMessage) {}

    /**
     * Handler for EndOfCycle Signal
     * @param[in] objectPath the object path
     */
    virtual void OnEndOfCycle( const qcc::String& objectPath ) {}

};

} //namespace services
} //namespace ajn

#endif /* CYCLECONTROLINTFCONTROLLERLISTENER_H_ */
