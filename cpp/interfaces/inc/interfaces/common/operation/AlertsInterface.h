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

#include <qcc/String.h>
#include <alljoyn/Status.h>
#include <alljoyn/cdm/common/CdmInterface.h>
#include <alljoyn/cdm/util/CdmMsgCvt.h>

namespace ajn {
namespace services {

/**
 * Alerts Interface class
 */
class AlertsInterface : public CdmInterface {
  public:
    static const char* const INTERFACE_NAME;
    static const CdmInterfaceType INTERFACE_TYPE;
    enum Severity {
        SEVERITY_WARNING = 0,
        SEVERITY_ALARM = 1,
        SEVERITY_FAULT = 2,
    };

    struct AlertRecord {
        AlertsInterface::Severity severity;
        uint16_t alertCode;
        bool needAcknowledgement;

        inline bool operator==(const AlertRecord& a) {
            return a.severity==severity && a.alertCode==alertCode && a.needAcknowledgement==needAcknowledgement;
        }
    };
    struct AlertCodesDescriptor {
        uint16_t alertCode;
        qcc::String description;

        inline bool operator==(const AlertCodesDescriptor& a) {
            return a.alertCode==alertCode && a.description==description;
        }
    };

    /**
     * Constructor of AlertsInterface
     */
    AlertsInterface() {}

    /**
     * Destructor of AlertsInterface
     */
    virtual ~AlertsInterface() {}

    /**
     * Get Interface Type
     * @return interface type
     */
    const CdmInterfaceType GetInterfaceType() const { return ALERTS_INTERFACE; }

    /**
     * Get Introspection XML
     * @return Introspection XML
     */
    virtual const qcc::String& GetIntrospectionXml() { return s_xml; }

    /**
     * Get Interface version
     * @return Interface version
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

// Enum converters



template<>
struct CdmMsgCvt<AlertsInterface::Severity>
{
    void get(const MsgArg& msgarg, AlertsInterface::Severity& value)
    {
        int32_t v;
        msgarg.Get("i", &v);
        value = static_cast<AlertsInterface::Severity>(v);
    }

    void set(MsgArg& msgarg, AlertsInterface::Severity value)
    {
        int32_t v = static_cast<int32_t>(value);
        msgarg.Set("i", v);
    }
};

template<>
struct CdmMsgCvt<std::vector<AlertsInterface::Severity>>
{
    void get(const MsgArg& msgarg, std::vector<AlertsInterface::Severity>& value)
    {
        int32_t* v;
        size_t l;

        msgarg.Get("ai", &l, &v);
        value.resize(l);

        for (size_t i = 0; i < l; ++i)
        {
            value[i] = static_cast<AlertsInterface::Severity>(v[i]);
        }
    }

    void set(MsgArg& msgarg, const std::vector<AlertsInterface::Severity>& value)
    {
        size_t l = value.size();
        std::vector<int32_t> ints(l);

        for (size_t i = 0; i < l; ++i)
        {
            ints[i] = static_cast<int32_t>(value[i]);
        }

        msgarg.Set("ai", ints.size(), ints.data());
        msgarg.Stabilize();
    }
};

// Struct converters
template<>
struct CdmMsgCvt<AlertsInterface::AlertRecord>
{
    void get(const MsgArg& msgarg, AlertsInterface::AlertRecord& value)
    {
        msgarg.Get("(iqb)", &value.severity, &value.alertCode, &value.needAcknowledgement);
    }

    void set(MsgArg& msgarg, AlertsInterface::AlertRecord value)
    {
        msgarg.Set("(iqb)", &value.severity, &value.alertCode, &value.needAcknowledgement);
    }
};


template<>
struct CdmMsgCvt<std::vector<AlertsInterface::AlertRecord>>
{
    void get(const MsgArg& msgarg, std::vector<AlertsInterface::AlertRecord>& value)
    {
        MsgArg* elems;
        size_t  num;

        msgarg.Get("a*", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Get("(iqb)", &value[i].severity, &value[i].alertCode, &value[i].needAcknowledgement);
        }
    }

    void set(MsgArg& msgarg, std::vector<AlertsInterface::AlertRecord>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Set("(iqb)", &value[i].severity, &value[i].alertCode, &value[i].needAcknowledgement);
        }

        msgarg.Set("a*", num, elems.data());
    }
};

template<>
struct CdmMsgCvt<AlertsInterface::AlertCodesDescriptor>
{
    void get(const MsgArg& msgarg, AlertsInterface::AlertCodesDescriptor& value)
    {
        msgarg.Get("(qs)", &value.alertCode, &value.description);
    }

    void set(MsgArg& msgarg, AlertsInterface::AlertCodesDescriptor value)
    {
        msgarg.Set("(qs)", &value.alertCode, &value.description);
    }
};


template<>
struct CdmMsgCvt<std::vector<AlertsInterface::AlertCodesDescriptor>>
{
    void get(const MsgArg& msgarg, std::vector<AlertsInterface::AlertCodesDescriptor>& value)
    {
        MsgArg* elems;
        size_t  num;

        msgarg.Get("a*", &num, &elems);
        value.resize(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Get("(qs)", &value[i].alertCode, &value[i].description);
        }
    }

    void set(MsgArg& msgarg, std::vector<AlertsInterface::AlertCodesDescriptor>& value)
    {
        size_t num = value.size();
        std::vector<MsgArg> elems(num);

        for (size_t i = 0; i < num; ++i)
        {
            elems[i].Set("(qs)", &value[i].alertCode, &value[i].description);
        }

        msgarg.Set("a*", num, elems.data());
    }
};


} //namespace services
} //namespace ajn

#endif /* ALERTSINTERFACE_H_ */
