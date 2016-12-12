#ifndef QC_TYPES_H
#define QC_TYPES_H

#include <mutex>

//======================================================================

typedef std::recursive_mutex Mutex;
typedef std::lock_guard<Mutex> LockGuard;

//======================================================================
#endif // QC_TYPES_H
