    Element* elem = HAL_Encode_Int(targetTimeToStop, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Timer", "SetTargetTimeToStop", elem);
    BSXML_FreeElement(elem);
    return AJ_OK;
