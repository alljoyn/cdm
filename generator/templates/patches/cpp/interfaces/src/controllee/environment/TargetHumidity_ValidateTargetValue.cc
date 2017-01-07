        uint8_t minValue;
        if (m_TargetHumidityModelInterface->GetMinValue(minValue) != ER_OK)
            return ER_FAIL;

        uint8_t maxValue;
        if (m_TargetHumidityModelInterface->GetMaxValue(maxValue) != ER_OK)
            return ER_FAIL;

        if (minValue == maxValue)
        {
            if (ValidateTargetValue(validValue) != ER_OK)
                return ER_FAIL;
        }
        else
        {
            uint8_t stepValue;
            if (m_TargetHumidityModelInterface->GetStepValue(stepValue) != ER_OK)
                return ER_FAIL;

            validValue = clamp<uint8_t>(value, minValue, maxValue, stepValue);
        }
