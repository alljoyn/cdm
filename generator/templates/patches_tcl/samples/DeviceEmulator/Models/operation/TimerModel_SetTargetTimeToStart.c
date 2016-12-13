    Element* elem = HAL_Encode_Int(targetTimeToStart, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Timer", "SetTargetTimeToStart", elem);
    BSXML_FreeElement(elem);
    return AJ_OK;
