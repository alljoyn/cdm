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


#ifndef CDMTYPES_H_
#define CDMTYPES_H_

#include <memory>
#include <map>

#include <qcc/String.h>
#include <alljoyn/MsgArg.h>

namespace ajn {

// Forward declarations that should be in core
class BusAttachment;
class AuthListener;
class SessionPortListener;
class PermissionConfigurationListener;

namespace services {
//======================================================================

/*  Shorthands for shared_ptr.
*/

template<typename T>
using Ref = std::shared_ptr<T>;


template<typename T, typename ... Args>
static inline
Ref<T>
mkRef(Args&& ...args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

//======================================================================
// Forward Declarations

class CdmAboutData;
class CdmAnnouncer;
class CdmSecurity;

//======================================================================
}  // services
}  // ajn

#endif //  CDMTYPES_H_
