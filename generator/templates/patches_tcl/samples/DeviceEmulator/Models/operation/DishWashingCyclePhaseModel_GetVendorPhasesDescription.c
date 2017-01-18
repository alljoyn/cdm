    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "__PhaseDescription");

    if (elem) {
        HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(elem, phasesDescription);
        BSXML_FreeElement(elem);
        return AJ_OK;
    }

    return AJ_ERR_FAILURE;
