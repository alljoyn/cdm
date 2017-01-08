    std::vector<AlertsInterface::AlertRecord> alerts;
    QStatus status = HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);
    if (status != ER_OK)
        return status;

    alerts.erase(std::remove_if(alerts.begin(), alerts.end(),
            [arg_alertCode](const AlertsInterface::AlertRecord& record){return record.alertCode == arg_alertCode;}),
            alerts.end()
            );

    status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty()) {
        auto iface = controllee.GetInterface<AlertsIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts");
        iface->EmitAlertsChanged(alerts);
    }

    return status;
