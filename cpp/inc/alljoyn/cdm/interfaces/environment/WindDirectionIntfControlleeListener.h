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

#ifndef WINDDIRECTIONINTFCONTROLLEELISTENER_H_
#define WINDDIRECTIONINTFCONTROLLEELISTENER_H_

#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * WindDirection interface controllee listener class
 */
class WindDirectionIntfControlleeListener : public InterfaceControlleeListener {
  public:

    /**
     * Destructor of WindDirectionIntfControlleeListener
     */
    virtual ~WindDirectionIntfControlleeListener() {}

    /**
     * Handler for setting horizontal wind direction
     * @param[in] value horizontal wind direction
     * @return ER_OK on success
     */
    virtual QStatus OnSetHorizontalDirection(const uint16_t& value) = 0;

    /**
     * Handler for getting horizontal wind direction
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value horizontal wind direction
     * @return ER_OK on success
     */
    virtual QStatus OnGetHorizontalDirection(uint16_t& value) = 0;

    /**
     * Handler for getting the maximum horizontal wind direction
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum horizontal wind direction
     * @return ER_OK on success
     */
    virtual QStatus OnGetHorizontalMax(uint16_t& value) = 0;

    /**
     * Handler for setting horizontal auto mode
     * @param[in] value horizontal auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetHorizontalAutoMode(const uint8_t& value) = 0;

    /**
     * Handler for getting horizontal auto mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value horizontal auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetHorizontalAutoMode(uint8_t& value) = 0;

    /**
     * Handler for setting vertical wind direction
     * @param[in] value vertical wind direction
     * @return ER_OK on success
     */
    virtual QStatus OnSetVerticalDirection(const uint16_t& value) = 0;

    /**
     * Handler for getting vertical wind direction
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value vertical wind direction
     * @return ER_OK on success
     */
    virtual QStatus OnGetVerticalDirection(uint16_t& value) = 0;

    /**
     * Handler for getting the maximum vertical wind direction
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value the maximum vertical wind direction
     * @return ER_OK on success
     */
    virtual QStatus OnGetVerticalMax(uint16_t& value) = 0;

    /**
     * Handler for setting vertical auto mode
     * @param[in] value vertical auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnSetVerticalAutoMode(const uint8_t& value) = 0;

    /**
     * Handler for getting vertical auto mode
     * This function is only called, when InterfaceControllee::s_retrievingActualPropertyValue is true.
     * @param[out] value vertical auto mode
     * @return ER_OK on success
     */
    virtual QStatus OnGetVerticalAutoMode(uint8_t& value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLEELISTENER_H_ */