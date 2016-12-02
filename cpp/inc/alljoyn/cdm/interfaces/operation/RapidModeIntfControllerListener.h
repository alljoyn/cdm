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

#ifndef RAPIDMODEINTFCONTROLLERLISTENER_H_
#define RAPIDMODEINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * RapidMode Interface Controller Listener class
 */
class RapidModeIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~RapidModeIntfControllerListener() {}

    /**
     * Handler for RapidMode property changed
     * @param[in] objectPath the object path
     * @param[in] rapidMode rapid mode
     */
    virtual void RapidModePropertyChanged(const qcc::String& objectPath, const bool rapidMode) {}

    /**
     * Callback handler for setting RapidMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnSetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for getting RapidMode property
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] rapidMode rapid mode
     * @param[in] context the context that is passed from application
     */
    virtual void OnGetRapidModePropertyCallback(QStatus status, const qcc::String& objectPath, const bool rapidMode, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLERLISTENER_H_ */