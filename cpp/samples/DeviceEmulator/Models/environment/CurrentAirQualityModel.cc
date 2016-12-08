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

#include "CurrentAirQualityModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<CurrentAirQualityInterface::ContaminantType>
{
    Element* put(Element* parent, CurrentAirQualityInterface::ContaminantType value)
    {
        Serializer<int32_t> ser;
        return ser.put(parent, value);
    }


    CurrentAirQualityInterface::ContaminantType get(Element* element)
    {
        Serializer<int32_t> ser;
        return static_cast<CurrentAirQualityInterface::ContaminantType>(ser.get(element));
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


CurrentAirQualityModel::CurrentAirQualityModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus CurrentAirQualityModel::GetContaminantType(CurrentAirQualityInterface::ContaminantType& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "ContaminantType", out);
}

QStatus CurrentAirQualityModel::GetCurrentValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "CurrentValue", out);
}

QStatus CurrentAirQualityModel::GetMinValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "MinValue", out);
}

QStatus CurrentAirQualityModel::GetMaxValue(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "MaxValue", out);
}

QStatus CurrentAirQualityModel::GetPrecision(double& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "Precision", out);
}

QStatus CurrentAirQualityModel::GetUpdateMinTime(uint16_t& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "UpdateMinTime", out);
}

} // namespace emulator
} // namespace services
} // namespace ajn