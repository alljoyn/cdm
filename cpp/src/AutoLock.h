/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
