    AJ_Status status;
    Array_Alerts_AlertRecord newAlerts;

    InitArray_Alerts_AlertRecord(&newAlerts, 0);

    status = WriteAlerts(objPath, &newAlerts);

    if (status == AJ_OK && Cdm_EmitSignalOnPropertySet()) {
        AlertsModel* model = (AlertsModel*)context;
        status = Cdm_Alerts_EmitAlertsChanged(model->busAttachment, objPath, newAlerts);
    }

    return status;
