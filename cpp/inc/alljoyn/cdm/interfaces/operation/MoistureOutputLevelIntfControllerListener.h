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

#ifndef MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_
#define MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * MoistureOutputLevel interface controller listener class
 */
class MoistureOutputLevelIntfControllerListener : public InterfaceControllerListener {
  public:

    /**
     * Destructor of MoistureOutputLevelIntfControllerListener
     */
    virtual ~MoistureOutputLevelIntfControllerListener() {}

    /**
     * Handler for MoistureOutputLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value moisture output level
     */
    virtual void OnMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for MaxMoistureOutputLevel property changed
     * @param[in] objectPath the object path
     * @param[in] value the maximum moisture output level
     */
    virtual void OnMaxMoistureOutputLevelChanged(const qcc::String& objectPath, const uint8_t value) {}

    /**
     * Handler for AutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] autoMode auto mode
     */
    virtual void OnAutoModeChanged(const qcc::String& objectPath, const uint8_t autoMode) {}

    /**
     * Callback handler for getting MoistureOutputLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value moisture output level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for setting MoistureOutputLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetMoistureOutputLevel(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting MaxMoistureOutputLevel property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value the maximum moisture output level
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetMaxMoistureOutputLevel(QStatus status, const qcc::String& objectPath, const uint8_t value, void* context) {}

    /**
     * Callback handler for getting AutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] autoMode auto mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetAutoMode(QStatus status, const qcc::String& objectPath, const uint8_t autoMode, void* context) {}

    /**
     * Callback handler for setting AutoMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* MOISTUREOUTPUTLEVELINTFCONTROLLERLISTENER_H_ */