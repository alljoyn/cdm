    CycleControlInterface::OperationalState state;
    bool chg = false;

    switch (arg_command)
    {
    case CycleControlInterface::OPERATIONAL_COMMANDS_START:
        state = CycleControlInterface::OPERATIONAL_STATE_WORKING;
        chg = true;
        break;

    case CycleControlInterface::OPERATIONAL_COMMANDS_STOP:
        state = CycleControlInterface::OPERATIONAL_STATE_IDLE;
        chg = true;
        break;

    case CycleControlInterface::OPERATIONAL_COMMANDS_PAUSE:
        state = CycleControlInterface::OPERATIONAL_STATE_PAUSED;
        chg = true;
        break;

    case CycleControlInterface::OPERATIONAL_COMMANDS_RESUME:
        state = CycleControlInterface::OPERATIONAL_STATE_WORKING;
        chg = true;
        break;

    default:
        break;
    }

    if (chg)
    {
        QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "OperationalState", state);

        if (status == ER_OK && controllee.EmitChangedSignalOnSetProperty())
        {
            auto iface = controllee.GetInterface<CycleControlIntfControllee>(m_busPath, "org.alljoyn.SmartSpaces.Operation.CycleControl");
            iface->EmitOperationalStateChanged(state);
        }
    }

    return ER_OK;
