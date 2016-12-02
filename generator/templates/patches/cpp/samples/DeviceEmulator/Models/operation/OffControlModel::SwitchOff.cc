    bool value = false;
    QStatus status = HAL::WriteProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn", value);

    if (status == ER_OK)
    {
        sideEffects[{"org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn"}] = CdmSideEffect("b", value);
    }

    return status;
