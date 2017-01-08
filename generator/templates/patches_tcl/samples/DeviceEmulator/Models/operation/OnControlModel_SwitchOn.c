    bool value = true;

    Element* elem = HAL_Encode_Bool(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        OnControlModel* model = (OnControlModel*)context;
        Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, objPath, value);
    }

    return AJ_OK;
