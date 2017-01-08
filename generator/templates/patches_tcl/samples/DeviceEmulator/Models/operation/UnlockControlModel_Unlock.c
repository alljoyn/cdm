    bool value = false;

    Element* elem = HAL_Encode_Bool(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.LockedStatus", "IsLocked", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        UnlockControlModel* model = (UnlockControlModel*)context;
        Cdm_LockedStatus_EmitIsLockedChanged(model->busAttachment, objPath, value);
    }

    return AJ_OK;
