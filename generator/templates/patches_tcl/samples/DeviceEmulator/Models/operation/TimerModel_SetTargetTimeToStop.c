    Element* elem = HAL_Encode_Int(targetTimeToStop, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Timer", "SetTargetTimeToStop", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        TimerModel* model = (TimerModel*)context;
        Cdm_Timer_EmitTargetTimeToStopChanged(model->busAttachment, objPath, targetTimeToStop);
    }

    return AJ_OK;
