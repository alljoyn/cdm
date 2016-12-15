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


#ifndef CDMBUSOBJECT_H_
#define CDMBUSOBJECT_H_

#include <map>
#include <qcc/String.h>

#include <alljoyn/BusObject.h>
#include <alljoyn/BusAttachment.h>

#include <alljoyn/cdm/common/CdmTypes.h>
#include <alljoyn/cdm/common/CdmInterfaceTypes.h>
#include <alljoyn/cdm/controllee/CdmControllee.h>

namespace ajn {
namespace services {

class CdmInterface;
class InterfaceControlleeModel;
/**
 * Cdm BusObject class.
 */
class CdmBusObject : public BusObject {
  public:

    /**
     * Constructor of CdmBusObject
     */
    CdmBusObject(BusAttachment& busAttachment, qcc::String const& objectPath, CdmControllee& controllee);

    /**
     * Destructor of CdmBusObject
     */
    ~CdmBusObject();

    /**
     * Start Cdm BusObject
     * @return status
     */
    QStatus Start();

    /**
     * Stop Cdm BusObject
     * @return status
     */
    QStatus Stop();

    /**
     * Registers an interface with the BusObject
     * @param[in] interface  CDM interface to be added to the bus object
     * @return status
     */
    QStatus RegisterInterface(CdmInterface* interface);


    /**
     * Get property
     * @param ifcName    Identifies the interface that the property is defined on
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus Get(const char* ifcName, const char* propName, MsgArg& val);

    /**
     * Set property
     * @param ifcName   Identifies the interface that the property is defined on
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus Set(const char* ifcName, const char* propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Reply to a method call.
     *
     * @param msg      The method call message
     * @param args     The reply arguments (can be NULL)
     * @param numArgs  The number of arguments
     * @return status
     */
    QStatus ReplyMethodCall(const Message& msg, const MsgArg* args = NULL, size_t numArgs = 0)
    {
       return MethodReply(msg, args, numArgs);
    }

    /**
     * Reply to a method call with an error message.
     *
     * @param msg              The method call message
     * @param error            The name of the error
     * @param errorMessage     An error message string
     * @return status
     */
    QStatus ReplyMethodCall(const Message& msg, const char* error, const char* errorMessage = NULL)
    {
       return MethodReply(msg, error, errorMessage);
    }

    /**
     * Reply to a method call with an error message.
     *
     * @param msg        The method call message
     * @param status     The status code for the error
     * @return status
     */
    QStatus ReplyMethodCall(const Message& msg, QStatus status)
    {
       return MethodReply(msg, status);
    }

  private:
    /**
     * Add handlers of interface
     * @param interface
     * @return status
     */
    QStatus AddInterfaceHandlers(CdmInterface* interface);

    BusAttachment& m_busAttachment;
    CdmControllee& m_controllee;
    std::map<qcc::String, CdmInterface*> m_cdmInterfacesMap;
};

}
}

#endif // CDMBUSOBJECT_H_