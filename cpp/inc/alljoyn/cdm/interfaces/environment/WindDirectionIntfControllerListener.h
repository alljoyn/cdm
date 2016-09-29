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

#ifndef WINDDIRECTIONINTFCONTROLLERLISTENER_H_
#define WINDDIRECTIONINTFCONTROLLERLISTENER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/InterfaceControllerListener.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionInterface.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface Controller Listener class
 */
class WindDirectionIntfControllerListener : public InterfaceControllerListener {
  public:
    using AutoMode = WindDirectionInterface::AutoMode;

    /**
     * Destructor of WindDirectionIntfControllerListener
     */
    virtual ~WindDirectionIntfControllerListener() {}

    /**
     * Callback handler for GetHorizontalDirection completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of HorizontalDirection
     *                  (Horizontal wind direction of a device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHorizontalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for HorizontalDirection property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of HorizontalDirection
     *                  (Horizontal wind direction of a device.)
     */
    virtual void OnHorizontalDirectionChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for SetHorizontalDirection completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetHorizontalDirection(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetHorizontalMax completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of HorizontalMax
     *                  (Maximum value allowed for a target horizontal wind direction.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHorizontalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for HorizontalMax property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of HorizontalMax
     *                  (Maximum value allowed for a target horizontal wind direction.)
     */
    virtual void OnHorizontalMaxChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for GetHorizontalAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of HorizontalAutoMode
     *                  (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context) {}

    /**
     * Handler for HorizontalAutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of HorizontalAutoMode
     *                  (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     */
    virtual void OnHorizontalAutoModeChanged(const qcc::String& objectPath, const AutoMode value) {}

    /**
     * Callback handler for SetHorizontalAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetHorizontalAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetVerticalDirection completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of VerticalDirection
     *                  (Vertical wind direction of a device.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVerticalDirection(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for VerticalDirection property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of VerticalDirection
     *                  (Vertical wind direction of a device.)
     */
    virtual void OnVerticalDirectionChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for SetVerticalDirection completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetVerticalDirection(QStatus status, const qcc::String& objectPath, void* context) {}

    /**
     * Callback handler for GetVerticalMax completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of VerticalMax
     *                  (Maximum value allowed for a target vertical wind direction.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVerticalMax(QStatus status, const qcc::String& objectPath, const uint16_t value, void* context) {}

    /**
     * Handler for VerticalMax property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of VerticalMax
     *                  (Maximum value allowed for a target vertical wind direction.)
     */
    virtual void OnVerticalMaxChanged(const qcc::String& objectPath, const uint16_t value) {}

    /**
     * Callback handler for GetVerticalAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] value The value of VerticalAutoMode
     *                  (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseGetVerticalAutoMode(QStatus status, const qcc::String& objectPath, const AutoMode value, void* context) {}

    /**
     * Handler for VerticalAutoMode property changed
     * @param[in] objectPath the object path
     * @param[in] value The value of VerticalAutoMode
     *                  (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     */
    virtual void OnVerticalAutoModeChanged(const qcc::String& objectPath, const AutoMode value) {}

    /**
     * Callback handler for SetVerticalAutoMode completion
     * @param[in] status ER_OK on success
     * @param[in] objectPath the object path
     * @param[in] context the context that is passed from application
     */
    virtual void OnResponseSetVerticalAutoMode(QStatus status, const qcc::String& objectPath, void* context) {}
};

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLERLISTENER_H_ */
