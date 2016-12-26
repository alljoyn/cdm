    bool value = true;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.LockedStatus", "IsLocked", value);

    if (status == ER_OK)
    {
        auto iface = controllee.GetInterface<LockedStatusIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.LockedStatus");
        iface->EmitIsLockedChanged(value);
    }

    return status;
