    std::vector<AlertsInterface::AlertRecord> empty;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", empty);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty()) {
        auto iface = controllee.GetInterface<AlertsIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts");
        iface->EmitAlertsChanged(empty);
    }

    return status;
