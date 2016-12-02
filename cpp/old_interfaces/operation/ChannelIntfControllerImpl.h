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

#ifndef CHANNELINTFCONTROLLERIMPL_H_
#define CHANNELINTFCONTROLLERIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/cdm/interfaces/InterfaceController.h>
#include <alljoyn/cdm/interfaces/operation/ChannelIntfController.h>

namespace ajn {
namespace services {

class ChannelIntfControllerListener;

/**
 * Channel Interface Controller implementation class
 */
class ChannelIntfControllerImpl : public InterfaceController, public ChannelIntfController {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Constructor of ChannelIntfControllerImpl
     */
    ChannelIntfControllerImpl(BusAttachment& busAttachment, ChannelIntfControllerListener& listener, ProxyBusObject& ProxyBusObject);

    /**
     * Destructor of ChannelIntfControllerImpl
     */
    virtual ~ChannelIntfControllerImpl();

    /**
     * Initialize interface
     * @return status
     */
    virtual QStatus Init();

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get ChannelId property
     * (Current channel id.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetChannelId(void* context);

    /**
     * Set ChannelId property
     * (Current channel id.)
     * @param[in] value The channel id to set
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus SetChannelId(const qcc::String& value, void* context);

    /**
     * Get TotalNumberOfChannels property
     * (Total number of scanned channels.)
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetTotalNumberOfChannels(void* context);

    /**
     * Call GetChannelList method
     * (Retrieve the list of channels.)
     * @param[in] startingRecord List built from this record number.
     * @param[in] numRecords List generated at most this many records.
     * @param[in] context the context that is passed to the callback handler
     * @return ER_OK on success
     */
    virtual QStatus GetChannelList(const uint16_t startingRecord, const uint16_t numRecords, void* context);

  private:
    void PropertiesChanged(ProxyBusObject& obj, const char* ifaceName, const MsgArg& changed, const MsgArg& invalidated, void* context);
    void GetChannelIdPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void SetChannelIdPropertyCB(QStatus status, ProxyBusObject* obj, void* context);
    void GetTotalNumberOfChannelsPropertyCB(QStatus status, ProxyBusObject* obj, const MsgArg& value, void* context);
    void GetChannelListReplyHandler(Message& message, void* context);
    void ChannelListChanged(const InterfaceDescription::Member* member, const char* srcPath, Message& message);

    BusAttachment& m_busAttachment;
    ChannelIntfControllerListener& m_interfaceListener;
};

} //namespace services
} //namespace ajn

#endif /* CHANNELINTFCONTROLLERIMPL_H_ */
