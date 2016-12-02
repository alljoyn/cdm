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

#ifndef TIMERINTERFACE_H_
#define TIMERINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * Timer Interface class
 */
class TimerInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;

    /**
     * Constructor of TimerInterface
     */
    TimerInterface() {}

    /**
     * Destructor of TimerInterface
     */
    virtual ~TimerInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return TIMER_INTERFACE; }

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
    static const qcc::String s_prop_ReferenceTimer;
    static const qcc::String s_prop_TargetTimeToStart;
    static const qcc::String s_prop_TargetTimeToStop;
    static const qcc::String s_prop_EstimatedTimeToEnd;
    static const qcc::String s_prop_RunningTime;
    static const qcc::String s_prop_TargetDuration;
    static const qcc::String s_method_SetTargetTimeToStart;
    static const qcc::String s_method_SetTargetTimeToStop;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

// Enum converters

// Struct converters

} //namespace services
} //namespace ajn

#endif /* TIMERINTERFACE_H_ */