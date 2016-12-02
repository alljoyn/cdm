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

#ifndef WINDDIRECTIONINTFCONTROLLEE_H_
#define WINDDIRECTIONINTFCONTROLLEE_H_

#include <vector>
#include <map>
#include <utility>

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionInterface.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface Controllee class
 */
class WindDirectionIntfControllee : public WindDirectionInterface {
  public:
    /**
     * Constructor of WindDirectionIntfControllee
     */
    WindDirectionIntfControllee() {}

    /**
     * Destructor of WindDirectionIntfControllee
     */
    virtual ~WindDirectionIntfControllee() {}

    /**
     * Get horizontal direction
     * @return Horizontal direction
     */
    virtual const uint16_t GetHorizontalDirection () const = 0;

    /**
     * Set horizontal direction
     * @param[in] value horizontal direction
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalDirection (const uint16_t value) = 0;

    /**
     * Get the maximum horizontal direction
     * @return The maximum horizontal direction
     */
    virtual const uint16_t GetHorizontalMax() const = 0;

    /**
     * Set horizontal max direction
     * @param[in] value horizontal max direction
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalMax(const uint16_t value) = 0;

    /**
     * Get horizontal auto mode
     * @return Horizontal auto mode
     */
    virtual const uint8_t GetHorizontalAutoMode () const = 0;

    /**
     * Set horizontal auto mode
     * @param[in] value horizontal auto mode
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalAutoMode (const uint8_t value) = 0;

    /**
     * Get vertical direction
     * @return Vertical direction
     */
    virtual const uint16_t GetVerticalDirection () const = 0;

    /**
     * Set vertical direction
     * @param[in] value vertical direction
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalDirection (const uint16_t value) = 0;

    /**
     * Get the maximum vertical direction
     * @return The maximum vertical direction
     */
    virtual const uint16_t GetVerticalMax() const = 0;

    /**
     * Set vertical max direction
     * @param[in] value vertical max direction
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalMax(const uint16_t value) = 0;

    /**
     * Get vertical auto mode
     * @return Vertical auto node
     */
    virtual const uint8_t GetVerticalAutoMode () const = 0;

    /**
     * Set vertical auto mode
     * @param[in] value vertical auto mode
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalAutoMode (const uint8_t value) = 0;
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLEE_H_ */