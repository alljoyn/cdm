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

#ifndef ALERTSINTERFACE_H_
#define ALERTSINTERFACE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/hae/interfaces/HaeInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface class
 */
class AlertsInterface : public HaeInterface {
  public:

    typedef enum
    {
        ALERT_SEVERITY_WARRNING,
        ALERT_SEVERITY_ALARM,
        ALERT_SEVERITY_FAULT
    } AlertSeverity;

    struct AlertRecord {
        AlertSeverity severity; // enumeration field
        uint16_t alertCode; // alert code
        bool needAcknowledgement; // acknowledgment request state
        inline bool operator==(const AlertRecord& a) {
        if (a.severity==severity && a.alertCode== alertCode && a.needAcknowledgement == needAcknowledgement)
            return true;
        else
            return false;
        }
    };

    typedef struct {
        uint16_t code;
        qcc::String description;
    } AlertCodeDescriptor;

    typedef std::vector<AlertRecord> Alerts;

    typedef std::vector<AlertCodeDescriptor> AlertCodesDescription;
    /**
     * Constructor of Alerts
     */
    AlertsInterface() {}

    /**
     * Destructor of Alerts
     */
    virtual ~AlertsInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const HaeInterfaceType GetInterfaceType() const { return ALERTS_INTERFACE; }

    /**
     * Get Introspection Xml
     * @return xml
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return interface version
     */
    virtual const uint16_t GetInterfaceVersion() const { return s_interfaceVersion; }

  protected:
    static const qcc::String s_prop_Version;
    static const qcc::String s_prop_Alerts;
    static const qcc::String s_method_GetAlertCodesDescription;
    static const qcc::String s_method_AcknowledgeAlert;
    static const qcc::String s_method_AcknowledgeAllAlerts;

  private:
    static const qcc::String s_xml;
    static const uint16_t s_interfaceVersion;
};

} //namespace services
} //namespace ajn

#endif /* ALERTSINTERFACE_H_ */
