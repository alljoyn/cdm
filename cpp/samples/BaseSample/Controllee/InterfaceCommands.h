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

#ifndef INTERFACECOMMANDS_H_
#define INTERFACECOMMANDS_H_

#include <qcc/String.h>
#include "ControlleeCommands.h"

class ControlleeSample;

class InterfaceCommands : public ControlleeCommands
{
  public:
    InterfaceCommands(ControlleeSample* sample, const char* objectPath)
        : ControlleeCommands(sample),
          m_objectPath(objectPath)
    {
    }
    virtual ~InterfaceCommands() {}

  protected:
    qcc::String m_objectPath;
};

#endif /* INTERFACECOMMANDS_H_ */