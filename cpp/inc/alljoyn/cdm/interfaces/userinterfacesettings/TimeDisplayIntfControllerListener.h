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

#ifndef TIMEDISPLAYINTFCONTROLLERLISTENER_H_
#define TIMEDISPLAYINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <vector>

namespace ajn {
namespace services {

/**
 * TimeDisplay Interface Controller Listener class
 */
class TimeDisplayIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~TimeDisplayIntfControllerListener() {}

    /**
     * Callback handler for getting DisplayTimeFormat
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] timeformat time format
     * @param[in] context the context that is passed from application
     */
    virtual void GetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, const uint8_t timeformat, void* context) {};

    /**
     * Callback handler for setting DisplayTimeFormat
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void SetDisplayTimeFormatPropertyCallback(QStatus status, const qcc::String& objectPath, void* context) {};

    /**
     * Callback handler for getting SupportedDisplayTimeFormats
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] supportedTimeFormats supportedTimeFormats
     * @param[in] context the context that is passed from application
     */
    virtual void GetSupportedDisplayTimeFormatsPropertyCallback(QStatus status, const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats, void* context) {};


    /**
     * Handler for DisplayTimeFormat property changed
     * @param[in] objectPath the object path
     * @param[in] timeformat timeformat
     */
    virtual void DisplayTimeFormatPropertyChanged(const qcc::String& objectPath, const uint8_t timeformat) {};

    /**
     * Handler for SupportedDisplayTimeFormats property changed
     * @param[in] objectPath the object path
     * @param[in] supportedTimeFormats supportedTimeFormats
     */
    virtual void SupportedDisplayTimeFormatsPropertyChanged(const qcc::String& objectPath, const std::vector<uint8_t>& supportedTimeFormats) {};

};

} //namespace services
} //namespace ajn

#endif /* TIMEDISPLAYINTFCONTROLLERLISTENER_H_ */