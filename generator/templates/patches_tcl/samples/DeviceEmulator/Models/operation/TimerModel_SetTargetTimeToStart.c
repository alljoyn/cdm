    Element* elem = HAL_Encode_Int(targetTimeToStart, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Timer", "SetTargetTimeToStart", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        TimerModel* model = (TimerModel*)context;
        Cdm_Timer_EmitTargetTimeToStartChanged(model->busAttachment, objPath, targetTimeToStart);
    }

    return AJ_OK;
