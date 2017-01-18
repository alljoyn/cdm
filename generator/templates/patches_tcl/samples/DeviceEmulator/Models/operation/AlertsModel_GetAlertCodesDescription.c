    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "__AlertCodesDescriptor");

    if (elem) {
        HAL_Decode_Array_Alerts_AlertCodesDescriptor(elem, description);
        BSXML_FreeElement(elem);
        return AJ_OK;
    }

    return AJ_ERR_FAILURE;
