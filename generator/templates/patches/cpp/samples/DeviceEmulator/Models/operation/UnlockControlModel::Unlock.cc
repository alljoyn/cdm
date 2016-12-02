    bool value = false;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.LockedStatus", "IsLocked", value);

    if (status == ER_OK)
    {
        sideEffects[{"org.alljoyn.SmartSpaces.Operation.LockedStatus", "IsLocked"}] = CdmSideEffect("b", value);
    }

    return status;
