    std::vector<AlertsInterface::AlertRecord> alerts;
    HAL::ReadProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);
    alerts.erase(std::remove_if(alerts.begin(), alerts.end(),
            [arg_alertCode](const AlertsInterface::AlertRecord& record){return record.alertCode == arg_alertCode;}),
            alerts.end()
            );
    HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", alerts);

    auto iface = controllee.GetInterface<AlertsIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts");
    iface->EmitAlertsChanged(alerts);
    return ER_OK;
