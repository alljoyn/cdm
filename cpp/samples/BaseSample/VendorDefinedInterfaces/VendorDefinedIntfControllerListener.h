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

#ifndef VENDORDEFINEDINTFCONTROLLERLISTENER_H_
#define VENDORDEFINEDINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>

namespace ajn {
namespace services {

/**
 * VendorDefined Interface Controller Listener class
 */
class VendorDefinedIntfControllerListener : public InterfaceControllerListener {
  public:
    virtual ~VendorDefinedIntfControllerListener() {}

    /*
     * TODO: define functions that receives the response of SetProperty, GetProperty or method call
     */
    virtual void OnResponseSetTestProperty(QStatus status, const qcc::String& objectPath, void* context) {}
    virtual void OnResponseGetTestProperty(QStatus status, const qcc::String& objectPath, int32_t property, void* context) {}
    virtual void OnResponseTestMethod(QStatus status, const qcc::String& objectPath,
            void* context, const char* errorName, const char* errorMessage) {}

    /*
     * TODO: define functions that receives the PropertyChanged and other signals
     */
    virtual void OnTestPropertyChanged(const qcc::String& objectPath, const int32_t property) {}
    virtual void OnTestSignal(const qcc::String& objectPath) {}
};

} //namespace services
} //namespace ajn

#endif /* VENDORDEFINEDINTFCONTROLLERLISTENER_H_ */
