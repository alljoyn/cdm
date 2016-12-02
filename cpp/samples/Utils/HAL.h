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

#ifndef ALLJOYN_HAL_H
#define ALLJOYN_HAL_H

#include <alljoyn/Status.h>
#include <qcc/String.h>
#include "../../framework/src/util/BSXML.h"

#include "Serialize.h"


namespace ajn {
namespace services {
namespace HAL {
//======================================================================

using ajn::services::xml::Element;

/**
 *  This is a singleton
 */

class X
{
  public:
    static X& instance();

    void SetRootDir(const std::string& rootDir);

    xml::Element* ReadPropertyXml(const std::string& busPath, const std::string& interface, const std::string& property);

    // This doesn't retain the Element pointer.
    void WritePropertyXml(const std::string& busPath, const std::string& interface, const std::string& property, xml::Element* xml);

    void WritePropertyXml(const std::string& busPath, const std::string& interface, const std::string& property, const std::string& xml);

  private:
    X();

    class Impl;

    Impl* m_impl;

  public:
    // for std::unique_ptr
    ~X();
};

//======================================================================

inline void SetRootDir(const std::string& rootDir)
{
    X::instance().SetRootDir(rootDir);
}



template<typename T>
inline QStatus ReadProperty(const std::string& busPath, const std::string& interface, const std::string& property, T& out)
{
    QStatus status = ER_FAIL;
    Element* xml = X::instance().ReadPropertyXml(busPath, interface, property);

    try
    {
        if (xml)
        {
            Serializer<T> ser;
            out = ser.get(xml);
            status = ER_OK;
        }
    }
    catch(...)
    {
    }

    return status;
}



template<typename T>
inline QStatus WriteProperty(const std::string& busPath, const std::string& interface, const std::string& property, const T& value)
{
    typedef typename std::remove_const<T>::type BaseType;
    QStatus status = ER_FAIL;

    try
    {
        Serializer<BaseType> ser;
        Element* xml = ser.put(nullptr, value);
        X::instance().WritePropertyXml(busPath, interface, property, xml);
        delete xml;
        status = ER_OK;
    }
    catch(...)
    {
    }

    return status;
}

//======================================================================
} // namespace HAL
} // namespace services
} // namespace ajn

#endif //ALLJOYN_HAL_H
