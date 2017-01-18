    auto status = HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase", "__PhaseDescription", arg_phasesDescription);
    if (status != ER_OK) {
        error = FEATURE_NOT_AVAILABLE;
    }
    return status;
