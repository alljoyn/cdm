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

#include "PlugInUnitsModel.h"
#include "../../../Utils/HAL.h"


namespace ajn {
namespace services {

template <>
struct Serializer<PlugInUnitsInterface::PlugInInfo>
{
    Element* put(Element* parent, PlugInUnitsInterface::PlugInInfo value)
    {
        std::vector<SerializerField> sfields;
        {
            SerializerField sfield;
            Serializer<qcc::String> ser;
            sfield.name = "objectPath";
            sfield.elem = ser.put(nullptr, value.objectPath);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<uint32_t> ser;
            sfield.name = "deviceId";
            sfield.elem = ser.put(nullptr, value.deviceId);
            sfields.push_back(sfield);
        }
        {
            SerializerField sfield;
            Serializer<bool> ser;
            sfield.name = "pluggedIn";
            sfield.elem = ser.put(nullptr, value.pluggedIn);
            sfields.push_back(sfield);
        }
        Serializer<std::vector<SerializerField>> ser;
        return ser.put(parent, sfields);
    }


    PlugInUnitsInterface::PlugInInfo get(Element* element)
    {
        Serializer<std::vector<SerializerField>> ser;
        PlugInUnitsInterface::PlugInInfo result;
        auto fields = ser.get(element);
        {
            auto& sfield = fields[0];
            if (sfield.name != "objectPath")
            {
                throw SerializerError();
            }
            Serializer<qcc::String> ser;
            result.objectPath = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[1];
            if (sfield.name != "deviceId")
            {
                throw SerializerError();
            }
            Serializer<uint32_t> ser;
            result.deviceId = ser.get(sfield.elem);
        }
        {
            auto& sfield = fields[2];
            if (sfield.name != "pluggedIn")
            {
                throw SerializerError();
            }
            Serializer<bool> ser;
            result.pluggedIn = ser.get(sfield.elem);
        }
        return result;
    }
};

} // namespace services
} // namespace ajn



namespace ajn {
namespace services {
namespace emulator {


PlugInUnitsModel::PlugInUnitsModel(const std::string& busPath) :
    m_busPath(busPath)
{}

QStatus PlugInUnitsModel::GetPlugInUnits(std::vector<PlugInInfo>& out) const
{
    return HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.PlugInUnits", "PlugInUnits", out);
}

} // namespace emulator
} // namespace services
} // namespace ajn
