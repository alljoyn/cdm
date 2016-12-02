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

#include "SwitchModel.h"
#include <interfaces/controllee/operation/OnOffStatusIntfControllee.h>
#include "../Utils/HAL.h"

using namespace ajn::services;

SwitchModel::SwitchModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus SwitchModel::GetIsOn(bool& out) const
{
    return HAL::ReadProperty<bool>(m_busPath, "OnOffStatus", "IsOn", out);
}

static QStatus writeIsOnWithSideEffect(const qcc::String& busPath, bool value, ajn::services::CdmControllee& controllee)
{
    QStatus status = HAL::WriteProperty(busPath, "OnOffStatus", "IsOn", value);

    if (status == ER_OK) {
        auto iface = controllee.GetInterface<OnOffStatusIntfControllee>(busPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus");
        iface->EmitIsOnChanged(value);
    }

    return status;
}

QStatus SwitchModel::SwitchOn(ajn::services::ErrorCode& error, ajn::services::CdmControllee& controllee)
{
    return writeIsOnWithSideEffect(m_busPath, true, controllee);
}

QStatus SwitchModel::SwitchOff(ajn::services::ErrorCode& error, ajn::services::CdmControllee& controllee)
{
    return writeIsOnWithSideEffect(m_busPath, false, controllee);
}
