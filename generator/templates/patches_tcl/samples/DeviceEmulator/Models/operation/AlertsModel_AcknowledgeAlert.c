    AJ_Status status;
    Array_Alerts_AlertRecord alerts;
    Array_Alerts_AlertRecord newAlerts;
    int found = 0;
    int i;

    status = GetAlerts(context, objPath, &alerts);
    if (status != AJ_OK) {
        return status;
    }

    /* Check that the given alert is in the array.  */
    for (i = 0; i < alerts.numElems; ++i) {
        if (alerts.elems[i].alertCode == alertCode) {
            found = 1;
        }
    }

    if (found) {
        InitArray_Alerts_AlertRecord(&newAlerts, 0);

        for (i = 0; i < alerts.numElems; ++i) {
            if (alerts.elems[i].alertCode != alertCode) {
                size_t ix = ExtendArray_Alerts_AlertRecord(&newAlerts, 1);
                newAlerts.elems[ix] = alerts.elems[i];
            }
        }

        status = WriteAlerts(objPath, &newAlerts);

        if (status == AJ_OK && Cdm_EmitSignalOnPropertySet())
        {
            AlertsModel* model = (AlertsModel*)context;
            status = Cdm_Alerts_EmitAlertsChanged(model->busAttachment, objPath, newAlerts);
        }

        FreeArray_Alerts_AlertRecord(&newAlerts);
    }

    FreeArray_Alerts_AlertRecord(&alerts);
    return status;
