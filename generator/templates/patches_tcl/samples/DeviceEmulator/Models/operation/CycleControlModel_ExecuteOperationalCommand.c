    AJ_Status status = AJ_OK;
    uint8_t state;
    int chg = 0;
    
    status = GetOperationalState(context, objPath, &state);
    if (status != AJ_OK) {
        return status;
    }

    switch (command)
    {
    case CYCLECONTROL_OPERATIONAL_COMMANDS_START:
        state = CYCLECONTROL_OPERATIONAL_STATE_WORKING;
        chg = 1;
        break;

    case CYCLECONTROL_OPERATIONAL_COMMANDS_STOP:
        state = CYCLECONTROL_OPERATIONAL_STATE_IDLE;
        chg = 1;
        break;

    case CYCLECONTROL_OPERATIONAL_COMMANDS_PAUSE:
        state = CYCLECONTROL_OPERATIONAL_STATE_PAUSED;
        chg = 1;
        break;

    case CYCLECONTROL_OPERATIONAL_COMMANDS_RESUME:
        state = CYCLECONTROL_OPERATIONAL_STATE_WORKING;
        chg = 1;
        break;

    default:
        break;
    }

    if (chg) {
        Element* elem = HAL_Encode_UInt(state, NULL);
        status = HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "OperationalState", elem)? AJ_OK : AJ_ERR_FAILURE;
        BSXML_FreeElement(elem);

        if (status == AJ_OK && Cdm_EmitSignalOnPropertySet()) {
            CycleControlModel* model = (CycleControlModel*)context;
            status = Cdm_CycleControl_EmitOperationalStateChanged(model->busAttachment, objPath, state);
        }
    }

    return status;

