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

#ifndef TIMERINTERFACE_H_
#define TIMERINTERFACE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * Timer Interface class
 */
class TimerInterface : public CdmInterface {
  public:
    /**
     * Constructor of Timer
     */
    TimerInterface() {}

    /**
     * Destructor of Timer
     */
    virtual ~TimerInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return TIMER_INTERFACE; }

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

    static const int32_t TIMER_FEATURE_NOT_APPLIED = 0x80000000;
    static const int32_t TIMER_NOT_SUPPORTED       = 0x80000001;

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

} //namespace services
} //namespace ajn

#endif /* TIMERINTERFACE_H_ */