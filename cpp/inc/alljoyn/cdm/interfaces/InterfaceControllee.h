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

#ifndef INTERFACECONTROLLEE_H_
#define INTERFACECONTROLLEE_H_

#include <vector>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/MsgArg.h>
#include <alljoyn/MessageReceiver.h>

namespace ajn {
namespace services {

class CdmBusObject;

/**
 * InterfaceControllee class
 */
class InterfaceControllee : public MessageReceiver {
  public:

    typedef std::vector<std::pair<const InterfaceDescription::Member*, MessageReceiver::MethodHandler> > MethodHandlers;

    /**
     * Constructor of InterfaceControllee
     */
    InterfaceControllee(CdmBusObject& cdmBusObject) : m_busObject(cdmBusObject) {}

    /**
     * Destructor of InterfaceControllee
     */
    virtual ~InterfaceControllee() {}

    /**
     * Callback handler for getting property.
     * @param[in] propName identifies the property to get
     * @param[out] val returns the property value. The type of this value is the actual value type.
     * @return ER_OK on success
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val) = 0;

    /**
     * Callback handler for setting property.
     * @param[in] propName identifies the property to set
     * @param[in] val returns the property value. The type of this value is the actual value type.
     * @return ER_OK on success
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val) = 0;

    /**
     * Handler for method
     * @param[in] member method interface member entry.
     * @param[in] message the received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg) = 0;

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const = 0;

  protected:
    /**
     * When get property method is called from controller and if this value is true,
     * retrieving actual property value from controllee application, and then send
     * the value of property to controller.
     */
    static const bool s_retrievingActualPropertyValue = false;

    CdmBusObject& m_busObject;
};

} //namespace services
} //namespace ajn

#endif /* INTERFACECONTROLLEE_H_ */