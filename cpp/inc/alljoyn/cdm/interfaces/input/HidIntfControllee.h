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

#ifndef HIDINTFCONTROLLEE_H_
#define HIDINTFCONTROLLEE_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/input/HidInterface.h>

namespace ajn {
namespace services {

/**
 * Hid Interface Controllee class
 */
class HidIntfControllee : public HidInterface {
  public:
    /**
     * Constructor of HidIntfControllee
     */
	HidIntfControllee() {}

    /**
     * Destructor of HidIntfControllee
     */
    virtual ~HidIntfControllee() {}

    /**
     * Get supported events
     * @return Supported events
     */
    virtual const SupportedInputEvents& GetSupportedEvents() const = 0;

    /**
     * Set supported events
     * @param[in] supportedEvents supported events
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedEvents(const SupportedInputEvents& supportedEvents) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLEE_H_ */