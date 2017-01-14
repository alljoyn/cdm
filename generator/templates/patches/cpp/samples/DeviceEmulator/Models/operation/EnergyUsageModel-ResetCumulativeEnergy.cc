    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.EnergyUsage", "CumulativeEnergy", 0.0);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<EnergyUsageIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.EnergyUsage");
        iface->EmitCumulativeEnergyChanged(0.0);
    }

    return status;
