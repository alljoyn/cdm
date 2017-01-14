    uint8_t minValue;
    status = model->GetMinValue(model, objPath, &minValue);
    if (status != AJ_OK)
        return status;

    uint8_t maxValue;
    status = model->GetMaxValue(model, objPath, &maxValue);
    if (status != AJ_OK)
        return status;

    if (minValue == maxValue)
    {
        status = ValidateTargetValue(model, objPath, *value);
        if (status != AJ_OK)
            return status;
    }
    else
    {
        uint8_t stepValue;
        status = model->GetStepValue(model, objPath, &stepValue);
        if (status != AJ_OK)
            return status;

        *value = clamp_uint8(*value, minValue, maxValue, stepValue);
    }
