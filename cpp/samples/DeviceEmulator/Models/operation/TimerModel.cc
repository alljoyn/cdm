/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include "TimerModel.h"
#include "../../../Utils/HAL.h"

#include <interfaces/controllee/operation/TimerIntfControllee.h>

namespace ajn {
namespace services {

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


TimerModel::TimerModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus TimerModel::GetReferenceTimer(int32_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "ReferenceTimer", out);
}

QStatus TimerModel::GetTargetTimeToStart(int32_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetTimeToStart", out);
}

QStatus TimerModel::GetTargetTimeToStop(int32_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetTimeToStop", out);
}

QStatus TimerModel::GetEstimatedTimeToEnd(int32_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "EstimatedTimeToEnd", out);
}

QStatus TimerModel::GetRunningTime(int32_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "RunningTime", out);
}

QStatus TimerModel::GetTargetDuration(int32_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetDuration", out);
}

QStatus TimerModel::SetTargetTimeToStart(int32_t arg_targetTimeToStart, ErrorCode& error, CdmControllee& controllee)
{
    auto value = arg_targetTimeToStart;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetTimeToStart", value);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<TimerIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer");
        iface->EmitTargetTimeToStartChanged(value);
    }

    return status;
}

QStatus TimerModel::SetTargetTimeToStop(int32_t arg_targetTimeToStop, ErrorCode& error, CdmControllee& controllee)
{
    auto value = arg_targetTimeToStop;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetTimeToStop", value);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<TimerIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer");
        iface->EmitTargetTimeToStopChanged(value);
    }

    return status;
}

} // namespace emulator
} // namespace services
} // namespace ajn
