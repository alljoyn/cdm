    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase", "__PhaseDescription");

    if (elem) {
        HAL_Decode_Array_LaundryCyclePhase_CyclePhaseDescriptor(elem, phasesDescription);
        BSXML_FreeElement(elem);
        return AJ_OK;
    }

    return AJ_ERR_FAILURE;
