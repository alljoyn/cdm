static std::vector<AlertsInterface::AlertCodesDescriptor> s_descriptions = {
    // alertCode description
    {1,   "bad",    },
    {2,   "worse"   },
    {3,   "stuffed" }
};

/*static bool AlertCommand(const std::string& key, const StringVec& args, CdmControllee& controllee)
{
    bool ok = false;

    if (args.size() >= 1 && args[0] == "show")
    {
        std::vector<AlertsInterface::AlertRecord> alerts;
        HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);
        ok = true;

        for (auto& alert : alerts)
        {
            std::cout << "severity " << alert.severity << ", code " << alert.alertCode << "\n";
        }
    }
    else
    if (args.size() >= 2)
    {
        AlertsInterface::Severity severity = AlertsInterface::SEVERITY_WARNING;
        uint16_t code = 0;

        if (args[0] == "w" || args[0] == "warning")
        {
            severity = AlertsInterface::SEVERITY_WARNING;
        }
        else
        if (args[0] == "a" || args[0] == "alarm")
        {
            severity = AlertsInterface::SEVERITY_ALARM;
        }
        else
        if (args[0] == "f" || args[0] == "fault")
        {
            severity = AlertsInterface::SEVERITY_FAULT;
        }

        {
            std::istringstream strm(args[1]);
            strm >> code;
        }

        ok = true;

        std::vector<AlertsInterface::AlertRecord> alerts;
        HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

        AlertsInterface::AlertRecord record;

        record.severity = severity;
        record.alertCode = code;
        record.needAcknowledgement = true;

        alerts.push_back(record);
        HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

        if (auto iface = controllee.GetInterface<AlertsIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts"))
        {
            iface->EmitAlertsChanged(alerts);
        }
    }

    return ok;
}

static bool s_subscribed = Commands::Instance().Subscribe("alert", AlertCommand, "alert args");*/

