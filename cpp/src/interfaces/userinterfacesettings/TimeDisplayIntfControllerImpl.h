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

#ifndef TIMEDISPLAYINTFCONTROLLERIMPL_H_
#define TIMEDISPLAYINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/TimeDisplayIntfController.h>

namespace ajn {
namespace services {

class TimeDisplayIntfControllerListener;
class CdmProxyBusObject;

/**
 * TimeDisplay Interface Controller implementation class
 */
class TimeDisplayIntfControllerImpl : public InterfaceController, public TimeDisplayIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of TimeDisplayIntfControllerImpl
     */
    TimeDisplayIntfControllerImpl(BusAttachment& busAttachment, TimeDisplayIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of TimeDisplayIntfControllerImpl
     */
    virtual ~TimeDisplayIntfControllerImpl();

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
     * Get DisplayTimeFormat
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetDisplayTimeFormat(void* context = NULL);

    /**
     * Set DisplayTimeFormat
     * @param[in] timeformat time format
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayTimeFormat(const uint8_t timeFormat, void* context = NULL);

    /**
     * Get SupportedDisplayTimeFormats
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedDisplayTimeFormats(void* context = NULL);




  private:
    TimeDisplayIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);

    void GetDisplayTimeFormatPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetDisplayTimeFormatPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetSupportedDisplayTimeFormatsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    TimeDisplayIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLERIMPL_H_ */