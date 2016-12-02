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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLEEIMPL_H_
#define AUDIOVIDEOINPUTINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfControllee.h>

namespace ajn {
namespace services {

class AudioVideoInputIntfControlleeListener;
class CdmBusObject;

/**
 * AudioVideoInput Interface Controllee implementation class
 */
class AudioVideoInputIntfControlleeImpl : public InterfaceControllee, public AudioVideoInputIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of AudioVideoInputIntfControlleeImpl
     */
    AudioVideoInputIntfControlleeImpl(BusAttachment& busAttachment, AudioVideoInputIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of AudioVideoInputIntfControlleeImpl
     */
    virtual ~AudioVideoInputIntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
     virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Set input source id
     * @param[in] input source id
     * @return status
     */
    virtual QStatus SetInputSourceId(const uint16_t inputSourceId);

    /**
     * Get input source id
     * @return input source id
     */
    virtual const uint16_t GetInputSourceId() const { return m_inputSourceId; }

    /**
     * Set supported input sources
     * @param[in] mute
     * @return status
     */
    virtual QStatus SetSupportedInputSources(const InputSources& supportedInputSources);

    /**
     * Get supported input sources
     * @return supported input sources
     */
    virtual const InputSources& GetSupportedInputSources() const { return m_supportedInputSources; }

  private:
    AudioVideoInputIntfControlleeImpl();
    QStatus CheckSupportedInputSources(const InputSources& supportedInputSources);

    BusAttachment& m_busAttachment;
    AudioVideoInputIntfControlleeListener& m_interfaceListener;
    uint16_t m_inputSourceId;             // read-write, EmitsChangedSignal
    InputSources m_supportedInputSources; // read-only, EmitsChangedSignal
    MethodHandlers m_methodHandlers;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLEEIMPL_H_ */