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

#ifndef FILTERSTATUSINTFCONTROLLERIMPL_H_
#define FILTERSTATUSINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/FilterStatusIntfController.h>

namespace ajn {
namespace services {

class FilterStatusIntfControllerListener;
class CdmProxyBusObject;

/**
 * FilterStatus Interface Controller implementation class
 */
class FilterStatusIntfControllerImpl : public InterfaceController, public FilterStatusIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Constructor of FilterStatusIntfControllerImpl
     */
    FilterStatusIntfControllerImpl(BusAttachment& busAttachment, FilterStatusIntfControllerListener& listener, CdmProxyBusObject& cdmProxyObject);

    /**
     * Destructor of FilterStatusIntfControllerImpl
     */
    virtual ~FilterStatusIntfControllerImpl();

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
     * Get ExpectedLifeInDays
     * @param[in] context
     * @return status
     */
    virtual QStatus GetExpectedLifeInDays(void* context);

    /**
     * Get IsCleanable
     * @param[in] context
     * @return status
     */
    virtual QStatus GetIsCleanable(void* context);

    /**
     * Get OrderPercentage
     * @param[in] context
     * @return status
     */
    virtual QStatus GetOrderPercentage(void* context);

    /**
     * Get Manufacturer
     * @param[in] context
     * @return status
     */
    virtual QStatus GetManufacturer(void* context);

    /**
     * Get PartNumber
     * @param[in] context
     * @return status
     */
    virtual QStatus GetPartNumber(void* context);

    /**
     * Get Url
     * @param[in] context
     * @return status
     */
    virtual QStatus GetUrl(void* context);

    /**
     * Get LifeRemaining
     * @param[in] context
     * @return status
     */
    virtual QStatus GetLifeRemaining(void* context);

  private:
    FilterStatusIntfControllerImpl();

    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetExpectedLifeInDaysPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetIsCleanablePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetOrderPercentagePropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetManufacturerPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetPartNumberPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetUrlPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetLifeRemainingPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);

    BusAttachment& m_busAttachment;
    FilterStatusIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* FILTERSTATUSINTFCONTROLLERIMPL_H_ */