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

// This file is automatically generated. Do not edit it.

#ifndef WATERLEVELINTERFACE_H_
#define WATERLEVELINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * WaterLevel Interface class
 */
class WaterLevelInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;

    enum SupplySource {
        SUPPLY_SOURCE_TANK = 0,
        SUPPLY_SOURCE_PIPE = 1,
        SUPPLY_SOURCE_NOT_SUPPORTED = 255,
    };


    /**
     * Constructor of WaterLevelInterface
     */
    WaterLevelInterface() {}

    /**
     * Destructor of WaterLevelInterface
     */
    virtual ~WaterLevelInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return WATER_LEVEL_INTERFACE; }

    /**
     * Get Introspection XML
     * @return Introspection XML
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return Interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_SupplySource;
    static const qcc::String s_prop_CurrentLevel;
    static const qcc::String s_prop_MaxLevel;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters



template<>
struct CdmMsgCvt<WaterLevelInterface::SupplySource>
{
    void get(const MsgArg& msgarg, WaterLevelInterface::SupplySource& value)
    {
        uint8_t v = 0;
        msgarg.Get("y", &v);
        value = static_cast<WaterLevelInterface::SupplySource>(v);
    }

    void set(MsgArg& msgarg, WaterLevelInterface::SupplySource value)
    {
        uint8_t v = static_cast<uint8_t>(value);
        msgarg.Set("y", v);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint8_t value = 0;
        msgarg.Get("y", &value);
        strm << value;
        return strm.str();
    }
};

template<>
struct CdmMsgCvt<std::vector<WaterLevelInterface::SupplySource>>
{
    void get(const MsgArg& msgarg, std::vector<WaterLevelInterface::SupplySource>& value)
    {
        uint8_t* v = 0;
        size_t l = 0;

        msgarg.Get("ay", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<WaterLevelInterface::SupplySource>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<WaterLevelInterface::SupplySource>& value)
    {
        size_t l = value.size();
        std::vector<uint8_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<uint8_t>(value[i]);
        }

        msgarg.Set("ay", ints.size(), ints.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint8_t* v = 0;
        size_t l = 0;
        msgarg.Get("ay", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};

// Struct converters

} //namespace services
} //namespace ajn

#endif /* WATERLEVELINTERFACE_H_ */
