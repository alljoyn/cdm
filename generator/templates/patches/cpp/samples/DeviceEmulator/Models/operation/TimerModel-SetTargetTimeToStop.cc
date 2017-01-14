    auto value = arg_targetTimeToStop;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer", "TargetTimeToStop", value);

    if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
    {
        auto iface = controllee.GetInterface<TimerIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.Timer");
        iface->EmitTargetTimeToStopChanged(value);
    }

    return status;
