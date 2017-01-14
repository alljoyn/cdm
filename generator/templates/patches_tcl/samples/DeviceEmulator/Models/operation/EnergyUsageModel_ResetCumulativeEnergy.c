    Element* elem = HAL_Encode_Double(0, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.EnergyUsage", "CumulativeEnergy", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        EnergyUsageModel* model = (EnergyUsageModel*)context;
        Cdm_EnergyUsage_EmitCumulativeEnergyChanged(model->busAttachment, objPath, 0.0);
    }
    return AJ_OK;
