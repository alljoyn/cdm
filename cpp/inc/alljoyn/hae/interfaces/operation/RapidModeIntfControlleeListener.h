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

#ifndef RAPIDMODEINTFCONTROLLEELISTENER_H_
#define RAPIDMODEINTFCONTROLLEELISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterfaceErrors.h>
#include <alljoyn/hae/interfaces/InterfaceControlleeListener.h>

namespace ajn {
namespace services {

/**
 * RapidMode Interface Controllee Listener class
 */
class RapidModeIntfControlleeListener : public InterfaceControlleeListener {
  public:
    /**
     * Destructor of RapidModeIntfControlleeListener
     */
    virtual ~RapidModeIntfControlleeListener() {}

    /**
     * TODO: define functions that receives the SetProperty, GetProperty and other method call
     */
    virtual QStatus OnSetRapidMode(const bool& rapidMode) = 0;

    virtual QStatus OnGetRapidMode(bool& volume) = 0;

};

} //namespace services
} //namespace ajn

#endif /* RAPIDMODEINTFCONTROLLEELISTENER_H_ */
