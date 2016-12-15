/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
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

#ifndef CYCLECONTROLINTERFACE_H_
#define CYCLECONTROLINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * CycleControl Interface class
 */
class CycleControlInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
    enum OperationalState {
        OPERATIONAL_STATE_IDLE = 0,
        OPERATIONAL_STATE_WORKING = 1,
        OPERATIONAL_STATE_READY_TO_START = 2,
        OPERATIONAL_STATE_DELAYED_START = 3,
        OPERATIONAL_STATE_PAUSED = 4,
        OPERATIONAL_STATE_END_OF_CYCLE = 5,
    };

    enum OperationalCommands {
        OPERATIONAL_COMMANDS_START = 0,
        OPERATIONAL_COMMANDS_STOP = 1,
        OPERATIONAL_COMMANDS_PAUSE = 2,
        OPERATIONAL_COMMANDS_RESUME = 3,
    };


    /**
     * Constructor of CycleControlInterface
     */
    CycleControlInterface() {}

    /**
     * Destructor of CycleControlInterface
     */
    virtual ~CycleControlInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return CYCLE_CONTROL_INTERFACE; }

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
    static const qcc::String s_prop_OperationalState;
    static const qcc::String s_prop_SupportedOperationalStates;
    static const qcc::String s_prop_SupportedOperationalCommands;
    static const qcc::String s_method_ExecuteOperationalCommand;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters



template<>
struct CdmMsgCvt<CycleControlInterface::OperationalState>
{
    void get(const MsgArg& msgarg, CycleControlInterface::OperationalState& value)
    {
        int32_t v = 0;
        msgarg.Get("i", &v);
        value = static_cast<CycleControlInterface::OperationalState>(v);
    }

    void set(MsgArg& msgarg, CycleControlInterface::OperationalState value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t value = 0;
        msgarg.Get("i", &value);
        strm << value;
        return strm.str();
    }
};

template<>
struct CdmMsgCvt<std::vector<CycleControlInterface::OperationalState>>
{
    void get(const MsgArg& msgarg, std::vector<CycleControlInterface::OperationalState>& value)
    {
        int32_t* v = 0;
        size_t l = 0;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<CycleControlInterface::OperationalState>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<CycleControlInterface::OperationalState>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t* v = 0;
        size_t l = 0;
        msgarg.Get("ai", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<CycleControlInterface::OperationalCommands>
{
    void get(const MsgArg& msgarg, CycleControlInterface::OperationalCommands& value)
    {
        int32_t v = 0;
        msgarg.Get("i", &v);
        value = static_cast<CycleControlInterface::OperationalCommands>(v);
    }

    void set(MsgArg& msgarg, CycleControlInterface::OperationalCommands value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t value = 0;
        msgarg.Get("i", &value);
        strm << value;
        return strm.str();
    }
};

template<>
struct CdmMsgCvt<std::vector<CycleControlInterface::OperationalCommands>>
{
    void get(const MsgArg& msgarg, std::vector<CycleControlInterface::OperationalCommands>& value)
    {
        int32_t* v = 0;
        size_t l = 0;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<CycleControlInterface::OperationalCommands>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<CycleControlInterface::OperationalCommands>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t* v = 0;
        size_t l = 0;
        msgarg.Get("ai", &l, &v);
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

#endif /* CYCLECONTROLINTERFACE_H_ */