    bool value = false;

    FILE* fp = HAL_WriteProperty(s_objPath, "OnOffStatus", "IsOn");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Int(fp, value);
    fclose(fp);

    OffControlModel* model = (OffControlModel*)context;
    Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, s_objPath, value);

    return AJ_OK;
