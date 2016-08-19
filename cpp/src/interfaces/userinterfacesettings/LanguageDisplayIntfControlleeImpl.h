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

#ifndef LANGUAGEDISPLAYINTFCONTROLLEEIMPL_H_
#define LANGUAGEDISPLAYINTFCONTROLLEEIMPL_H_

#include <alljoyn/Status.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/InterfaceDescription.h>
#include <alljoyn/cdm/interfaces/InterfaceControllee.h>
#include <alljoyn/cdm/interfaces/InterfaceControlleeListener.h>
#include <alljoyn/cdm/interfaces/userinterfacesettings/LanguageDisplayIntfControllee.h>

namespace ajn {
namespace services {

class LanguageDisplayIntfControlleeListener;
class CdmBusObject;

/**
 * LanguageDisplay Interface Controllee implementation class
 */
class LanguageDisplayIntfControlleeImpl : public InterfaceControllee, public LanguageDisplayIntfControllee {
  public:
    /**
     * Create interface
     */
    static CdmInterface* CreateInterface(BusAttachment& busAttachment, InterfaceControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Constructor of LanguageDisplayIntfControlleeImpl
     */
    LanguageDisplayIntfControlleeImpl(BusAttachment& busAttachment, LanguageDisplayIntfControlleeListener& listener, CdmBusObject& cdmBusObject);

    /**
     * Destructor of LanguageDisplayIntfControlleeImpl
     */
    virtual ~LanguageDisplayIntfControlleeImpl();

    /**
     * Initialize interface
     * @return status
     */
     virtual QStatus Init();

    /**
     * a callback function for getting property.
     * @param propName   Identifies the property to get
     * @param[out] val   Returns the property value. The type of this value is the actual value type.
     * @return status
     */
    virtual QStatus OnGetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * a callback function for setting property.
     * @param propName  Identifies the property to set
     * @param val       The property value to set. The type of this value is the actual value type.
     */
    virtual QStatus OnSetProperty(const qcc::String& propName, MsgArg& val);

    /**
     * method handler
     * @param member    Method interface member entry.
     * @param message   The received method call message.
     */
    virtual void OnMethodHandler(const InterfaceDescription::Member* member, Message& msg);

    /**
     * Get method handlers
     * @return MethodHandlers
     */
    virtual const MethodHandlers& GetMethodHanders() const { return m_methodHandlers; }

    /**
     * Get bus attachment
     * @return bus attachment
     */
    virtual BusAttachment& GetBusAttachment() const { return m_busAttachment; }

    /**
     * Get DisplayLanguage
     * @return display language
     */
    virtual const qcc::String GetDisplayLanguage() { return m_displayLanguage; }

    /**
     * Set DisplayLanguage
     * @param[in] displayLanguage display language
     * @return ER_OK on success
     */
    virtual QStatus SetDisplayLanguage(const qcc::String& displayLanguage);

    /**
     * Get SupportedDisplayLanguages
     * @return list of supported display languages
     */
    virtual const std::vector<qcc::String>& GetSupportedDisplayLanguages() { return m_supportedDisplayLanguages; }

    /**
     * Set SupportedDisplayLanguages
     * @param[in] supportedDisplayLanguages list of supported display languages
     * @return ER_OK on success
     */
    virtual QStatus SetSupportedDisplayLanguages(const std::vector<qcc::String>& supportedDisplayLanguages);
  private:
    LanguageDisplayIntfControlleeImpl();
    bool CheckValidationOfDisplayLanguage(const qcc::String& displayLanguage);

    BusAttachment& m_busAttachment;
    LanguageDisplayIntfControlleeListener& m_interfaceListener;
    MethodHandlers m_methodHandlers;
    qcc::String m_displayLanguage;
    std::vector<qcc::String> m_supportedDisplayLanguages;
};

} //namespace services
} //namespace ajn

#endif /* LANGUAGEDISPLAYINTFCONTROLLEEIMPL_H_ */
