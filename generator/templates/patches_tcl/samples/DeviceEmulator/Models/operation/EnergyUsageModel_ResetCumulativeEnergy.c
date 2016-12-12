    Element* elem = HAL_Encode_Double(0, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "EnergyUsage", "CumulativeEnergy", elem);
    BSXML_FreeElement(elem);
    return AJ_OK;
