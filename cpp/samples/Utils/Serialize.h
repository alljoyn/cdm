/******************************************************************************
 * 
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

#ifndef ALLJOYN_SERIALIZE_H
#define ALLJOYN_SERIALIZE_H

#include <iostream>
#include <sstream>
#include <exception>
#include <cstdint>

#include <qcc/String.h>
#include "../../framework/src/util/BSXML.h"

namespace ajn {
namespace services {
//======================================================================

using ajn::services::xml::Element;

struct SerializerError: public std::exception
{
};


template <typename T>
struct Serializer
{
};



template <>
struct Serializer<bool>
{
    Element* put(Element* parent, bool value)
    {
        auto* scalar = new Element("scalar", parent, true);
        scalar->AddAttribute("type", "bool");
        scalar->AddAttribute("value", value? "true" : "false");
        return scalar;
    }


    bool get(Element* element)
    {
        if (element->GetName() == "scalar")
        {
            auto& type  = element->GetAttribute("type");
            auto& value = element->GetAttribute("value");

            if (type == "bool")
            {
                return value == "true";
            }
        }

        throw SerializerError();
    }
};



template <>
struct Serializer<double>
{
    Element* put(Element* parent, double value)
    {
        std::ostringstream strm;
        strm << value;

        auto* scalar = new Element("scalar", parent, true);
        scalar->AddAttribute("type", "double");
        scalar->AddAttribute("value", strm.str());
        return scalar;
    }


    double get(Element* element)
    {
        if (element->GetName() == "scalar")
        {
            auto& type  = element->GetAttribute("type");
            auto& value = element->GetAttribute("value");

            if (type == "double")
            {
                std::istringstream strm(value);
                double v;
                strm >> v;
                return v;
            }
        }

        throw SerializerError();
    }
};



template <>
struct Serializer<qcc::String>
{
    Element* put(Element* parent, const qcc::String& value)
    {
        auto* scalar = new Element("scalar", parent, true);
        scalar->AddAttribute("type", "string");
        scalar->AddAttribute("value", std::string(value.c_str()));
        return scalar;
    }


    qcc::String get(Element* element)
    {
        if (element->GetName() == "scalar")
        {
            auto& type  = element->GetAttribute("type");
            auto& value = element->GetAttribute("value");

            if (type == "string")
            {
                return value.c_str();
            }
        }

        throw SerializerError();
    }
};



template <>
struct Serializer<int64_t>
{
    Element* put(Element* parent, int64_t value)
    {
        std::ostringstream strm;
        strm << value;

        auto* scalar = new Element("scalar", parent, true);
        scalar->AddAttribute("type", "signed");
        scalar->AddAttribute("value", strm.str());
        return scalar;
    }


    int64_t get(Element* element)
    {
        if (element->GetName() == "scalar")
        {
            auto& type  = element->GetAttribute("type");
            auto& value = element->GetAttribute("value");

            if (type == "signed")
            {
                std::istringstream strm(value);
                int64_t v = 0;
                strm >> v;
                return v;
            }
        }

        throw SerializerError();
    }
};



template <>
struct Serializer<uint64_t>
{
    Element* put(Element* parent, uint64_t value)
    {
        std::ostringstream strm;
        strm << value;

        auto* scalar = new Element("scalar", parent, true);
        scalar->AddAttribute("type", "unsigned");
        scalar->AddAttribute("value", strm.str());
        return scalar;
    }


    uint64_t get(Element* element)
    {
        if (element->GetName() == "scalar")
        {
            auto& type  = element->GetAttribute("type");
            auto& value = element->GetAttribute("value");

            if (type == "unsigned")
            {
                std::istringstream strm(value);
                uint64_t v;
                strm >> v;
                return v;
            }
        }

        throw SerializerError();
    }
};



template <>
struct Serializer<int32_t>
{
    Element* put(Element* parent, int32_t value)
    {
        Serializer<int64_t> s;
        return s.put(parent, value);
    }


    int32_t get(Element* element)
    {
        Serializer<int64_t> s;
        return static_cast<int32_t>(s.get(element));
    }
};



template <>
struct Serializer<int16_t>
{
    Element* put(Element* parent, int16_t value)
    {
        Serializer<int64_t> s;
        return s.put(parent, value);
    }


    int16_t get(Element* element)
    {
        Serializer<int64_t> s;
        return static_cast<int16_t>(s.get(element));
    }
};



template <>
struct Serializer<uint32_t>
{
    Element* put(Element* parent, uint32_t value)
    {
        Serializer<uint64_t> s;
        return s.put(parent, value);
    }


    uint32_t get(Element* element)
    {
        Serializer<uint64_t> s;
        return static_cast<uint32_t>(s.get(element));
    }
};



template <>
struct Serializer<uint16_t>
{
    Element* put(Element* parent, uint16_t value)
    {
        Serializer<uint64_t> s;
        return s.put(parent, value);
    }


    uint16_t get(Element* element)
    {
        Serializer<uint64_t> s;
        return static_cast<uint16_t>(s.get(element));
    }
};



template <>
struct Serializer<uint8_t>
{
    Element* put(Element* parent, uint8_t value)
    {
        Serializer<uint64_t> s;
        return s.put(parent, value);
    }


    uint8_t get(Element* element)
    {
        Serializer<uint64_t> s;
        return static_cast<uint8_t>(s.get(element));
    }
};



template <typename T>
struct Serializer<std::vector<T>>
{
    //  Read an array of scalars.
    Serializer<T> ser;

    Element* put(Element* parent, std::vector<T> elems)
    {
        auto* array = new Element("array", parent, true);
        for (auto& e : elems)
        {
            ser.put(array, e);
        }
        return array;
    }


    std::vector<T> get(Element* array)
    {
        std::vector<T> result;
        Serializer<T> ser;

        if (array->GetName() == "array")
        {
            for (Element* elem : array->GetChildren())
            {
                result.push_back(ser.get(elem));
            }
        }

        return result;
    }
};



template <>
struct Serializer<std::vector<Element*>>
{
    //  Read an array.
    Element* put(Element* parent, std::vector<Element*> elems)
    {
        auto* array = new Element("array", parent, true);
        for (auto& e : elems)
        {
            array->AddChild(e);
        }
        return array;
    }


    std::vector<Element*> get(Element* array)
    {
        if (array->GetName() == "array")
        {
            return array->GetChildren();
        }

        throw SerializerError();
    }
};


struct SerializerField
{
    std::string name;
    Element*    elem;
};



template <>
struct Serializer<std::vector<SerializerField>>
{
    //  Read an array.
    Element* put(Element* parent, std::vector<SerializerField> fields)
    {
        auto* struc = new Element("struct", parent, true);
        for (auto& f : fields)
        {
            auto* field = new Element("field", struc, true);
            field->AddAttribute("name", f.name);
            field->AddChild(f.elem);
        }
        return struc;
    }


    std::vector<SerializerField> get(Element* struc)
    {
        std::vector<SerializerField> result;

        if (struc->GetName() == "struct")
        {
            for (auto* f : struc->GetChildren())
            {
                if (f->GetName() == "field")
                {
                    auto fn = f->GetAttribute("name");
                    auto vs = f->GetChildren();        // should be only 1
                    if (!vs.empty() && !fn.empty())
                    {
                        SerializerField sf;
                        sf.name = fn;
                        sf.elem = vs[0];
                        result.push_back(sf);
                    }
                }
            }
        }

        return result;
    }
};

//======================================================================
} // namespace services
} // namespace ajn

#endif //ALLJOYN_HAL_H
