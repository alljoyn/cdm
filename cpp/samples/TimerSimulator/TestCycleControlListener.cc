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

#include <iostream>
#include <algorithm>
#include "TestCycleControlListener.h"
#include "TestControllee.h"
using namespace std;

TestCycleControlListener::TestCycleControlListener(void* controllee)
{
    m_testControllee = controllee;
}

QStatus TestCycleControlListener::OnGetOperationalState(CycleControlInterface::CycleControlOperationalState& state)
{
    cout << "TestCycleControlListener::OnGetOperationalState()" << endl;
    return ER_OK;
}

QStatus TestCycleControlListener::OnExecuteCommand(CycleControlInterface::CycleControlOperationalCommand command, CycleControlInterface::CycleControlOperationalState& newState, ErrorCode& error)
{
    QStatus status = ER_OK;
    cout << "TestCycleControlListener::OnExecuteCommand. Command: " << (int)command << ". Command name: " << CycleControlInterface::OPERATIONAL_COMMAND_STRINGS[command] <<endl;
    TestControllee *controllee =  static_cast<TestControllee*>(m_testControllee);
    error = ErrorCode::NOT_ERROR;
    CycleControlInterface::CycleControlOperationalState currentState = controllee->CycleIntf()->GetOperationalState();
    switch (command)
    {
        case CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_START:
        {
            if(currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START)
            {
                if(controllee->TimerIntf()->GetTargetTimeToStart() > 0 )
                {
                    controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START);
                }
                else
                {
                    controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING);
                }
            }
            else
            {
                error = ErrorCode::NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE;
            }
        }
        break;
        case CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_STOP:
        {
            if(currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING ||
               currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED  ||
               currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START)
            {
                controllee->IsRecipeSet() ?
                    controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_READY_TO_START) :
                    controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_IDLE);
            }
            else
            {
                error = ErrorCode::NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE;
            }
        }
        break;
        case CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_PAUSE:
        {
            if(currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING)
            {
                controllee->m_pausedState = controllee->CycleIntf()->GetOperationalState();
                controllee->m_timeElapsed = controllee->TimerIntf()->GetTargetTimeToStop() - controllee->TimerIntf()->GetReferenceTimer();
                controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED);
            }
            else if (currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START)
            {
                controllee->m_pausedState = controllee->CycleIntf()->GetOperationalState();
                controllee->m_timeTillStart = controllee->TimerIntf()->GetTargetTimeToStart() - controllee->TimerIntf()->GetReferenceTimer();
                controllee->CycleIntf()->SetOperationalState(CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED);
            }
            else
            {
                error = ErrorCode::NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE;
            }
        }
        break;
        case CycleControlInterface::CycleControlOperationalCommand::OPERATIONAL_COMMAND_RESUME:
        {
            if(currentState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_PAUSED)
            {
                if(controllee->m_pausedState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_WORKING)
                {
                    controllee->CycleIntf()->SetOperationalState(controllee->m_pausedState);
                }
                else if(controllee->m_pausedState == CycleControlInterface::CycleControlOperationalState::OPERATIONAL_STATE_DELAYED_START)
                {
                    controllee->CycleIntf()->SetOperationalState(controllee->m_pausedState);
                }
                else
                {
                    error = ErrorCode::NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE;
                }
            }
            else
            {
                error = ErrorCode::NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE;
            }
        }
        break;
        default:
        {
            error = ErrorCode::INVALID_VALUE;
        }
        break;
    }

    newState = controllee->CycleIntf()->GetOperationalState();
    return status;
}
