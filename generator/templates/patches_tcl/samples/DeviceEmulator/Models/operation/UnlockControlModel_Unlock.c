    bool value = false;

    FILE* fp = HAL_WriteProperty(s_objPath, "LockedStatus", "IsLocked");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Int(fp, value);
    fclose(fp);

    UnlockControlModel* model = (UnlockControlModel*)context;
    Cdm_LockedStatus_EmitIsLockedChanged(model->busAttachment, s_objPath, value);

    return AJ_OK;
