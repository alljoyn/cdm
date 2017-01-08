    bool value = true;

    Element* elem = HAL_Encode_Bool(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.LockedStatus", "IsLocked", elem);
    BSXML_FreeElement(elem);

    LockControlModel* model = (LockControlModel*)context;
    Cdm_LockedStatus_EmitIsLockedChanged(model->busAttachment, objPath, value);

    return AJ_OK;
