    std::vector<AlertsInterface::AlertRecord> empty;
    HAL::WriteProperty(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", empty);

    auto iface = controllee.GetInterface<AlertsIntfControllee>(BusPath, "org.alljoyn.SmartSpaces.Operation.Alerts");
    iface->EmitAlertsChanged(empty);
    return ER_OK;
