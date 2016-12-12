    FILE* fp = HAL_WriteProperty("/cdm/emulated", "Timer", "SetTargetTimeToStart");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Int(fp, targetTimeToStart);
    fclose(fp);
    return AJ_OK;
