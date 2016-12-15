/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef CDM_MSG_CVT_H_
#define CDM_MSG_CVT_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>
#include <qcc/String.h>
#include <vector>
#include <string>
#include <sstream>

namespace ajn {
namespace services {
//======================================================================

/**
 *  Normally pointers passed to msgarg.Set() must remain valid until
 *  the msgarg is consumed somwhere.  We use Stabilize() to force a copy.
 */

template<typename T>
struct CdmMsgCvt
{
};



template<>
struct CdmMsgCvt<qcc::String>
{
    // Get the value from the msgarg
    void get(const MsgArg& msgarg, qcc::String& value)
    {
        char*  ptr;
        msgarg.Get("s", &ptr);
        value = qcc::String(ptr);
    }

    void set(MsgArg& msgarg, const qcc::String& value)
    {
        msgarg.Set("s", value.c_str());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        char*  ptr;
        msgarg.Get("s", &ptr);
        return std::string(ptr);
    }
};



template<>
struct CdmMsgCvt<std::vector<qcc::String>>
{
    void get(const MsgArg& msgarg, std::vector<qcc::String>& value)
    {
        char** v;
        size_t l;
        msgarg.Get("as", &l, &v);
        value = std::vector<qcc::String>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<qcc::String>& value)
    {
        msgarg.Set("a$", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::string result;
        char** v;
        size_t l;
        msgarg.Get("as", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            result += *v;
            result += "\n";
        }
        return result;
    }
};



template<>
struct CdmMsgCvt<bool>
{
    void get(const MsgArg& msgarg, bool& value)
    {
        msgarg.Get("b", &value);
    }

    void set(MsgArg& msgarg, bool value)
    {
        msgarg.Set("b", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        bool value;
        msgarg.Get("b", &value);
        return value? "true" : "false";
    }
};



template<>
struct CdmMsgCvt<std::vector<bool>>
{
    void get(const MsgArg& msgarg, std::vector<bool>& value)
    {
        bool* v;
        size_t l;
        msgarg.Get("ab", &l, &v);
        value = std::vector<bool>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<bool>& value)
    {
        // vector<bool> is likely to be a bit vector
        size_t l = value.size();
        bool *bp = new bool[l];

        for (size_t i = 0; i < l; ++i)
        {
            bp[i] = value[i];
        }

        msgarg.Set("ab", l, bp);
        msgarg.Stabilize();

        delete[] bp;
    }

    std::string str(const MsgArg& msgarg)
    {
        std::string result;
        bool* v;
        size_t l;
        msgarg.Get("ab", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            result += v[i]? "true" : "false";
            result += "\n";
        }
        return result;
    }
};



template<>
struct CdmMsgCvt<double>
{
    void get(const MsgArg& msgarg, double& value)
    {
        msgarg.Get("d", &value);
    }

    void set(MsgArg& msgarg, double value)
    {
        msgarg.Set("d", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        double value;
        msgarg.Get("d", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<double>>
{
    void get(const MsgArg& msgarg, std::vector<double>& value)
    {
        double* v;
        size_t l;
        msgarg.Get("ad", &l, &v);
        value = std::vector<double>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<double>& value)
    {
        msgarg.Set("ad", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        double* v;
        size_t l;
        msgarg.Get("ad", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<int32_t>
{
    void get(const MsgArg& msgarg, int32_t& value)
    {
        msgarg.Get("i", &value);
    }

    void set(MsgArg& msgarg, int32_t value)
    {
        msgarg.Set("i", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t value;
        msgarg.Get("i", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<int32_t>>
{
    void get(const MsgArg& msgarg, std::vector<int32_t>& value)
    {
        int32_t* v;
        size_t l;
        msgarg.Get("ai", &l, &v);
        value = std::vector<int32_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<int32_t>& value)
    {
        msgarg.Set("ai", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int32_t* v;
        size_t l;
        msgarg.Get("ai", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<int16_t>
{
    void get(const MsgArg& msgarg, int16_t& value)
    {
        msgarg.Get("n", &value);
    }

    void set(MsgArg& msgarg, int16_t value)
    {
        msgarg.Set("n", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int16_t value;
        msgarg.Get("n", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<int16_t>>
{
    void get(const MsgArg& msgarg, std::vector<int16_t>& value)
    {
        int16_t* v;
        size_t l;
        msgarg.Get("an", &l, &v);
        value = std::vector<int16_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<int16_t>& value)
    {
        msgarg.Set("an", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int16_t* v;
        size_t l;
        msgarg.Get("an", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<uint16_t>
{
    void get(const MsgArg& msgarg, uint16_t& value)
    {
        msgarg.Get("q", &value);
    }

    void set(MsgArg& msgarg, uint16_t value)
    {
        msgarg.Set("q", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint16_t value;
        msgarg.Get("q", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<uint16_t>>
{
    void get(const MsgArg& msgarg, std::vector<uint16_t>& value)
    {
        uint16_t* v;
        size_t l;
        msgarg.Get("aq", &l, &v);
        value = std::vector<uint16_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<uint16_t>& value)
    {
        msgarg.Set("aq", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint16_t* v;
        size_t l;
        msgarg.Get("aq", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<uint64_t>
{
    void get(const MsgArg& msgarg, uint64_t& value)
    {
        msgarg.Get("t", &value);
    }

    void set(MsgArg& msgarg, uint64_t value)
    {
        msgarg.Set("t", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint64_t value;
        msgarg.Get("t", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<uint64_t>>
{
    void get(const MsgArg& msgarg, std::vector<uint64_t>& value)
    {
        uint64_t* v;
        size_t l;
        msgarg.Get("at", &l, &v);
        value = std::vector<uint64_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<uint64_t>& value)
    {
        msgarg.Set("at", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint64_t* v;
        size_t l;
        msgarg.Get("at", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<uint32_t>
{
    void get(const MsgArg& msgarg, uint32_t& value)
    {
        msgarg.Get("u", &value);
    }

    void set(MsgArg& msgarg, uint32_t value)
    {
        msgarg.Set("u", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint32_t value;
        msgarg.Get("u", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<uint32_t>>
{
    void get(const MsgArg& msgarg, std::vector<uint32_t>& value)
    {
        uint32_t* v;
        size_t l;
        msgarg.Get("au", &l, &v);
        value = std::vector<uint32_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<uint32_t>& value)
    {
        msgarg.Set("au", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint32_t* v;
        size_t l;
        msgarg.Get("au", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<int64_t>
{
    void get(const MsgArg& msgarg, int64_t& value)
    {
        msgarg.Get("x", &value);
    }

    void set(MsgArg& msgarg, int64_t value)
    {
        msgarg.Set("x", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int64_t value;
        msgarg.Get("x", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<int64_t>>
{
    void get(const MsgArg& msgarg, std::vector<int64_t>& value)
    {
        int64_t* v;
        size_t l;
        msgarg.Get("ax", &l, &v);
        value = std::vector<int64_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<int64_t>& value)
    {
        msgarg.Set("ax", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        int64_t* v;
        size_t l;
        msgarg.Get("ax", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<uint8_t>
{
    void get(const MsgArg& msgarg, uint8_t& value)
    {
        msgarg.Get("y", &value);
    }

    void set(MsgArg& msgarg, uint8_t value)
    {
        msgarg.Set("y", value);
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint8_t value;
        msgarg.Get("y", &value);
        strm << value;
        return strm.str();
    }
};



template<>
struct CdmMsgCvt<std::vector<uint8_t>>
{
    void get(const MsgArg& msgarg, std::vector<uint8_t>& value)
    {
        uint8_t* v;
        size_t l;
        msgarg.Get("ay", &l, &v);
        value = std::vector<uint8_t>(v, v + l);
    }

    void set(MsgArg& msgarg, const std::vector<uint8_t>& value)
    {
        msgarg.Set("ay", value.size(), value.data());
        msgarg.Stabilize();
    }

    std::string str(const MsgArg& msgarg)
    {
        std::ostringstream strm;
        uint8_t* v;
        size_t l;
        msgarg.Get("ay", &l, &v);
        for (size_t i = 0; i < l; ++i)
        {
            strm << v[i] << "\n";
        }
        return strm.str();
    }
};



//======================================================================
} // namespace services
} // namespace ajn

#endif // CDM_MSG_CVT_H_