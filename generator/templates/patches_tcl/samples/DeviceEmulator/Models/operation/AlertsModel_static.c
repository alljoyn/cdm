static Array_Alerts_AlertCodesDescriptor* getAlertCodesDescriptor(void)
{
    static Array_Alerts_AlertCodesDescriptor s_descrs;

    if (!s_descrs.elems) {
        InitArray_Alerts_AlertCodesDescriptor(&s_descrs, 0);
        size_t i = 0;

        i = ExtendArray_Alerts_AlertCodesDescriptor(&s_descrs, 1);
        s_descrs.elems[i].alertCode = 1;
        s_descrs.elems[i].description = strdup("bad");

        i = ExtendArray_Alerts_AlertCodesDescriptor(&s_descrs, 1);
        s_descrs.elems[i].alertCode = 2;
        s_descrs.elems[i].description = strdup("worse");

        i = ExtendArray_Alerts_AlertCodesDescriptor(&s_descrs, 1);
        s_descrs.elems[i].alertCode = 3;
        s_descrs.elems[i].description = strdup("stuffed");
    }

    return &s_descrs;
}


static void CopyAlerts_AlertCodesDescriptor(Alerts_AlertCodesDescriptor* value, Alerts_AlertCodesDescriptor* copy) UNUSED_OK;

static void CopyAlerts_AlertCodesDescriptor(Alerts_AlertCodesDescriptor* value, Alerts_AlertCodesDescriptor* copy)
{
    copy->alertCode = value->alertCode;
    copy->description = strdup(value->description);
}
