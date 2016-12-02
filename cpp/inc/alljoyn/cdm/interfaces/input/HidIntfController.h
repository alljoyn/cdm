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

#ifndef HIDINTFCONTROLLER_H_
#define HIDINTFCONTROLLER_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/input/HidInterface.h>

namespace ajn {
namespace services {

/**
 * Hid Interface Controller class
 */
class HidIntfController : public HidInterface {
  public:
    /**
     * Constructor of HidIntfController
     */
    HidIntfController() {}

    /**
     * Destructor of HidIntfController
     */
    virtual ~HidIntfController() {}

    /**
     * Get supported events
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetSupportedEvents(void* context = NULL) = 0;

    /**
     * Inject events
     * @param[in] inputEvents input events
     * @return ER_OK on success
     */
    virtual QStatus InjectEvents(InputEvents& inputEvents) = 0;
};

} //namespace services
} //namespace ajn

#endif /* HIDINTFCONTROLLER_H_ */