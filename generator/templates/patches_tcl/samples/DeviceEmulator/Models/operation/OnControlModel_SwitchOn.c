    bool value = true;

    Element* elem = HAL_Encode_Bool(value, NULL);
    HAL_WritePropertyElem(s_objPath, "OnOffStatus", "IsOn", elem);
    BSXML_FreeElement(elem);

    OnControlModel* model = (OnControlModel*)context;
    Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, s_objPath, value);

    return AJ_OK;
