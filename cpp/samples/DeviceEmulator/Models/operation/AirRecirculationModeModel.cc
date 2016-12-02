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

#include "AirRecirculationModeModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


AirRecirculationModeModel::AirRecirculationModeModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus AirRecirculationModeModel::GetIsRecirculating(bool& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode", "IsRecirculating", out);
}

QStatus AirRecirculationModeModel::SetIsRecirculating(const bool value)
{
    return HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.AirRecirculationMode", "IsRecirculating", value);
}

} // namespace emulator
} // namespace services
} // namespace ajn