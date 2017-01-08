    bool value = true;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn", value);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<OnOffStatusIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus");
        iface->EmitIsOnChanged(value);
    }

    return status;
