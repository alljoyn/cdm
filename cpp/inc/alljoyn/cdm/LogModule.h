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


#ifndef LOGMODULE_H_
#define LOGMODULE_H_

#include <qcc/Debug.h>
#include <qcc/platform.h>

namespace ajn {


static char const* const CDM_MODULE_LOG_NAME = "Cdm";
static char const* const QCC_MODULE = CDM_MODULE_LOG_NAME;

static const uint32_t ALL_LOG_LEVELS = 15;

}

#endif /* LOGMODULE_H_ */