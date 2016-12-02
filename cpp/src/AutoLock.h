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

#ifndef AUTOLOCK_H_
#define AUTOLOCK_H_

#include <qcc/Mutex.h>

namespace ajn {
namespace services {

class AutoLock {
  public:
    inline AutoLock(qcc::Mutex& mutex) : mLock(mutex)  { mLock.Lock(); }
    inline AutoLock(qcc::Mutex* mutex) : mLock(*mutex) { mLock.Lock(); }
    inline ~AutoLock() { mLock.Unlock(); }
  private:
    qcc::Mutex& mLock;
};

}
}

#endif /* AUTOLOCK_H_ */