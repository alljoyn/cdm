    FILE* fp = HAL_WriteProperty("/cdm/emulated", "Timer", "SetTargetTimeToStop");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Int(fp, targetTimeToStop);
    fclose(fp);
    return AJ_OK;
