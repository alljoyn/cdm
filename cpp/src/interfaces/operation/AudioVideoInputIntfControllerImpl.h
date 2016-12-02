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

#ifndef AUDIOVIDEOINPUTINTFCONTROLLERIMPL_H_
#define AUDIOVIDEOINPUTINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/AudioVideoInputIntfController.h>

namespace ajn {
namespace services {

class AudioVideoInputIntfControllerListener;
class CdmProxyBusObject;

/**
 * AudioVideoInput Interface Controller implementation class
 */
class AudioVideoInputIntfControllerImpl : public InterfaceController, public AudioVideoInputIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of AudioVideoInputIntfControllerImpl
     */
    AudioVideoInputIntfControllerImpl(BusAttachment& busAttachment, AudioVideoInputIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of AudioVideoInputIntfControllerImpl
     */
    virtual ~AudioVideoInputIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Set input source id
     * @param[in] input source id
     * @param[in] context
     * @return status
     */
    virtual QStatus SetInputSourceId(const uint16_t inputSourceId, void* context);

    /**
     * Get input source id
     * @param[in] context
     * @return status
     */
    QStatus GetInputSourceId(void* context);

    /**
     * Get supported input sources
     * @param[in] context
     * @return status
     */
    QStatus GetSupportedInputSources(void* context);

  private:
    AudioVideoInputIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void SetInputSourceIdPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetInputSourceIdPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetSupportedInputSourcesPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    AudioVideoInputIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* AUDIOVIDEOINPUTINTFCONTROLLERIMPL_H_ */