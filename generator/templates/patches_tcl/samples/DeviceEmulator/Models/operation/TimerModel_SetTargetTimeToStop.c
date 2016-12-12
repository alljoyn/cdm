    Element* elem = HAL_Encode_Int(targetTimeToStop, NULL);
    HAL_WritePropertyElem(objPath, "Timer", "SetTargetTimeToStop", elem);
    BSXML_FreeElement(elem);
    return AJ_OK;
