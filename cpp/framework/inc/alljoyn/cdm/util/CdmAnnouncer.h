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


#ifndef CDM_ANNOUNCER_H_
#define CDM_ANNOUNCER_H_

#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmTypes.h>

namespace ajn {
namespace services {
//======================================================================


class CdmAnnouncer
{
  public:

    /**
     * Constructor
     */
    CdmAnnouncer(BusAttachment& busAttachment);

    ~CdmAnnouncer();

    /**
     * Set the 'about' data in XML format. The last
     * SetAboutData() call will win.
     */
    CdmAnnouncer& SetAboutData(const qcc::String& xml);

    /**
     * Set the 'about' data from an object. The last
     * SetAboutData() call will win.
     */
    CdmAnnouncer& SetAboutData(Ref<CdmAboutData> aboutData);

    /**
     * Set a custom session listener. Otherwise a default
     * listener will accept all sessions.
     */
    CdmAnnouncer& SetSessionListener(Ref<SessionPortListener> listener);

    /**
     * Announce to the world.
     */
    QStatus Announce();

    /**
     * Unannounce from the world. This is normally done automatically
     * by the destructor.
     */
    QStatus Unannounce();

    /**
     * Retrieve the internal about data object. It can be
     * modified before the announcement is made.
     */
    Ref<CdmAboutData> GetAboutData() const;

  private:
    class Impl;

    Impl* m_impl;
};

//======================================================================
} // namespace services
} // namespace ajn

#endif // CDM_ANNOUNCER_H_
