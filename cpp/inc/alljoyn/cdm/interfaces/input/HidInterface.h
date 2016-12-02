/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef HIDINTERFACE_H_
#define HIDINTERFACE_H_

#include <vector>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * Hid Interface class
 */
class HidInterface : public CdmInterface {
  public:
    /**
     * InputEvent struct
     */
    typedef struct {
        uint16_t type;
        uint16_t code;
        int32_t value;
    } InputEvent;
    typedef std::vector<InputEvent> InputEvents;

    /**
     * SupportedInputEvent struct
     */
    typedef struct {
        uint16_t type;
        uint16_t code;
        int32_t min;
        int32_t max;
    } SupportedInputEvent;
    typedef std::vector<SupportedInputEvent> SupportedInputEvents;

    /**
     * Constructor of HidInterface
     */
    HidInterface() {}

    /**
     * Destructor of HidInterface
     */
    virtual ~HidInterface() {}

    /**
     * Get Interface Type
     * @return Interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return HID_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return Introspection xml
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return Interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_SupportedEvents;
    static const qcc::String s_method_InjectEvents;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTERFACE_H_ */