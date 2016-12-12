    FILE* fp = HAL_WriteProperty("/cdm/emulated", "EnergyUsage", "CumulativeEnergy");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Double(fp, 0);
    fclose(fp);
    return AJ_OK;
