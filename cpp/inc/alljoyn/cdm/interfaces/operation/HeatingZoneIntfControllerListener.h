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

#ifndef HEATINGZONEINTFCONTROLLERLISTENER_H_
#define HEATINGZONEINTFCONTROLLERLISTENER_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * HeatingZone Interface Controller Listener class
 */
class HeatingZoneIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~HeatingZoneIntfControllerListener() {}

    /**
     * Callback handler for getting NumberOfHeatingZones property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] numberOfZones number of heating zones
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetNumberOfHeatingZonesPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t numberOfZones, void* context) {}

    /**
     * Callback handler for getting MaxHeatingLevels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] maxHeatingLevels The list of max heating levels
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetMaxHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels, void* context) {}

    /**
     * Callback handler for getting HeatingLevels property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] heatingLevels The list heating levels
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetHeatingLevelsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels, void* context) {}

    /**
     * Handler for NumberOfHeating property changed
     * @param[in] objectPath the object path
     * @param[in] numberOfHeatingZones number of heating zones
     */
    virtual void NumberOfHeatingZonesPropertyChanged(const qcc::String& objectPath, const uint8_t numberOfHeatingZones) {}

    /**
     * Handler for MaxHeatingLevels property changed
     * @param[in] objectPath the object path
     * @param[in] maxHeatingLevels max heating levels
     */
    virtual void MaxHeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& maxHeatingLevels) {}

    /**
     * Handler for HeatingLevels property changed
     * @param[in] objectPath the object path
     * @param[in] heatingLevels heating levels
     */
    virtual void HeatingLevelsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& heatingLevels) {}
};

} //namespace services
} //namespace ajn

#endif /* HEATINGZONEINTFCONTROLLERLISTENER_H_ */