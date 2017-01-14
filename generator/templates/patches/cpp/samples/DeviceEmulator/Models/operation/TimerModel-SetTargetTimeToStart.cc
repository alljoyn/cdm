    auto value = arg_targetTimeToStart;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetTimeToStart", value);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<TimerIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer");
        iface->EmitTargetTimeToStartChanged(value);
    }

    return status;
