    if (arg_languageTag != "en") {      // the unit tests require this
        error = LANGUAGE_NOT_SUPPORTED;
        return ER_INVALID_DATA;
    }
    auto status = HAL::ReadProperty(m_busPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "__AlertCodesDescriptor", arg_description);
    if (status != ER_OK) {
        error = FEATURE_NOT_AVAILABLE;
    }
    return status;
