static AJ_Status WriteAlerts(const char *objPath, const Array_Alerts_AlertRecord* alerts)
{
    Element* elem = HAL_Encode_Array_Alerts_AlertRecord(*alerts, NULL);
    bool ok = HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", elem);
    BSXML_FreeElement(elem);
    return ok? AJ_OK : AJ_ERR_FAILURE;
}
