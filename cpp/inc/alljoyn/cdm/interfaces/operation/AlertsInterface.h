/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/

#ifndef ALERTSINTERFACE_H_
#define ALERTSINTERFACE_H_

#include <vector>
#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/interfaces/CdmInterface.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface class
 */
class AlertsInterface : public CdmInterface {
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
    const CdmInterfaceType GetInterfaceType() const { return ALERTS_INTERFACE; }

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