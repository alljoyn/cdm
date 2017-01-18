    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase", "__PhaseDescription");

    if (elem) {
        HAL_Decode_Array_OvenCyclePhase_CyclePhaseDescriptor(elem, phasesDescription);
        BSXML_FreeElement(elem);
        return AJ_OK;
    }

    return AJ_ERR_FAILURE;
