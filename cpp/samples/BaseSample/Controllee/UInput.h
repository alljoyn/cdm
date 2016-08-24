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
#ifdef UINPUT
#ifndef UINPUT_H_
#define UINPUT_H_

#include <linux/input.h>
#include <linux/uinput.h>
#include <inttypes.h>

#include <alljoyn/cdm/interfaces/input/HidInterface.h>

using namespace ajn;
using namespace services;

/**
 * UInput singleton.
 * This helper class offers a standardized way to inject user events in linux kernel
 * This functionnality is based on linux UInput
 */
class UInput
{
  //---------------------------------------------------------------------------------
  private:
    /**
     * Instance of of UInput helper
     */
    static UInput m_instance;

    /**
     * Constructor of UInput
     */
    UInput();

    /**
     * Destructor of UInput
     */
    ~UInput();

    /**
     * File descriptor of the device which is used to inject events
     */
    int m_deviceFD;

    /**
     * Supported events by the controllee
     */
    HidInterface::SupportedInputEvents m_supportedEvents;

  //---------------------------------------------------------------------------------
  public:
    /**
     * Get Instance
     * @return instance
     */
    static UInput& Instance();

    /**
     * Initialize the input device which is used to inject events.
     * This initialization is the responsibility of the application and
     * must be done before any injection.
     * vendorId, productId and version are used to define the input device during its creation
     * @param vendorId              Vendor id (see available list on http://www.linux-usb.org/usb.ids)
     * @param productId             Product id (see available list on http://www.linux-usb.org/usb.ids)
     * @param version               Version
     * @param supportedEvents       Supported events
     */
    void Init(uint16_t vendorId, uint16_t productId, uint16_t version, HidInterface::SupportedInputEvents supportedEvents);

    /**
     * Release the input device which is used to inject events.
     * This release is the responsibility of the application and should be
     * performed to close properly the input device.
     */
    void Release();

    /**
     * Get the file descriptor of the device which is used to inject events
     * @return file descriptor
     */
    inline int GetDeviceFileDescriptor(){return m_deviceFD;};

    /**
     * Inject a generic event (as UInput format)
     * @param type      Type of the event : EV_KEY, EV_ABS, EV_REL, ...
     * @param code      Code of the event : could be either a key code when using EV_KEY, or an axis for EV_ABS and EV_REL
     * @param value     Value of the event : may be 1 (press) or 0 (release) for EV_KEY, or any values for others (positive integer for EV_ABS, signed integer for EV_REL, etc…)
     * @return size     The number of bytes written on the input device to inject the event (-1 on failure)
     */
    int InjectEvent(uint16_t type, uint16_t code, int32_t value);
};

#endif /* UINPUT_H_ */
#endif
