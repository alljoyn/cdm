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

#ifndef WINDDIRECTIONINTFCONTROLLER_H_
#define WINDDIRECTIONINTFCONTROLLER_H_

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/environment/WindDirectionInterface.h>

namespace ajn {
namespace services {

/**
 * WindDirection Interface Controller class
 */
class WindDirectionIntfController : public WindDirectionInterface {
  public:
    /**
     * Constructor of WindDirectionIntfController
     */
    WindDirectionIntfController() {}

    /**
     * Destructor of WindDirectionIntfController
     */
    virtual ~WindDirectionIntfController() {}

    /**
     * Get HorizontalDirection property
     * (Horizontal wind direction of a device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalDirection(void* context = NULL) = 0;

    /**
     * Set HorizontalDirection property
     * (Horizontal wind direction of a device.)
     * @param[in] value The horizontal direction to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalDirection(const uint16_t value, void* context = NULL) = 0;

    /**
     * Get HorizontalMax property
     * (Maximum value allowed for a target horizontal wind direction.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalMax(void* context = NULL) = 0;

    /**
     * Get HorizontalAutoMode property
     * (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetHorizontalAutoMode(void* context = NULL) = 0;

    /**
     * Set HorizontalAutoMode property
     * (Represent enabled/disabled state of the horizontal auto mode. HorizontalAutoMode is for controlling horizontal wind direction automatically.)
     * @param[in] value The horizontal auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetHorizontalAutoMode(const AutoMode value, void* context = NULL) = 0;

    /**
     * Get VerticalDirection property
     * (Vertical wind direction of a device.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalDirection(void* context = NULL) = 0;

    /**
     * Set VerticalDirection property
     * (Vertical wind direction of a device.)
     * @param[in] value The vertical direction to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalDirection(const uint16_t value, void* context = NULL) = 0;

    /**
     * Get VerticalMax property
     * (Maximum value allowed for a target vertical wind direction.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalMax(void* context = NULL) = 0;

    /**
     * Get VerticalAutoMode property
     * (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetVerticalAutoMode(void* context = NULL) = 0;

    /**
     * Set VerticalAutoMode property
     * (Represent enabled/disabled state of the vertical auto mode. VerticalAutoMode is for controlling vertical wind direction automatically.)
     * @param[in] value The vertical auto mode to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetVerticalAutoMode(const AutoMode value, void* context = NULL) = 0;
};

typedef std::shared_ptr<WindDirectionIntfController> WindDirectionIntfControllerPtr;

} //namespace services
} //namespace ajn

#endif /* WINDDIRECTIONINTFCONTROLLER_H_ */
