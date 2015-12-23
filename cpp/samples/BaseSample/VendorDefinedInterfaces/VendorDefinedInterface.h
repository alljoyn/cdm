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

#ifndef VENDORDEFINEDINTERFACE_H_
#define VENDORDEFINEDINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>

namespace ajn {
namespace services {

/**
 * VendorDefined Interface class
 */
class VendorDefinedInterface : public HaeInterface {
  public:
    /**
     * Constructor of VendorDefined
     */
    VendorDefinedInterface() {}

    /**
     * Destructor of VendorDefined
     */
    virtual ~VendorDefinedInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const HaeInterfaceType GetInterfaceType() const { return VENDOR_DEFIEND_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return xml
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_TestProperty;
    static const qcc::String s_method_TestMethod;
    static const qcc::String s_signal_TestSignal;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTERFACE_H_ */
