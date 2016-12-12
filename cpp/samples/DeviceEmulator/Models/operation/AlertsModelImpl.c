/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "AlertsModelImpl.h"
#include "../../../Utils/HAL.h"





static int HAL_Encode_Alerts_AlertRecord(FILE* fp, Alerts_AlertRecord value) UNUSED_OK;

static int HAL_Encode_Alerts_AlertRecord(FILE* fp, Alerts_AlertRecord value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_Int(fp, value.severity);
    HAL_Encode_UInt(fp, value.alertCode);
    HAL_Encode_Int(fp, value.needAcknowledgement);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_Alerts_AlertRecord(FILE* fp, Alerts_AlertRecord* value) UNUSED_OK;

static int HAL_Decode_Alerts_AlertRecord(FILE* fp, Alerts_AlertRecord* value)
{
    HAL_Decode_OpenStruct(fp);
    value->severity = HAL_Decode_Int(fp);
    value->alertCode = HAL_Decode_UInt(fp);
    value->needAcknowledgement = HAL_Decode_Int(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_Alerts_AlertRecord(FILE* fp, Array_Alerts_AlertRecord value) UNUSED_OK;

static int HAL_Encode_Array_Alerts_AlertRecord(FILE* fp, Array_Alerts_AlertRecord value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Alerts_AlertRecord(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_Alerts_AlertRecord(FILE* fp, Array_Alerts_AlertRecord* value) UNUSED_OK;

static int HAL_Decode_Array_Alerts_AlertRecord(FILE* fp, Array_Alerts_AlertRecord* value)
{
    InitArray_Alerts_AlertRecord(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_Alerts_AlertRecord(value, 1);
        HAL_Decode_Alerts_AlertRecord(fp, &value->elems[i]);
    }
    return AJ_OK;
}



static int HAL_Encode_Alerts_AlertCodesDescriptor(FILE* fp, Alerts_AlertCodesDescriptor value) UNUSED_OK;

static int HAL_Encode_Alerts_AlertCodesDescriptor(FILE* fp, Alerts_AlertCodesDescriptor value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_UInt(fp, value.alertCode);
    HAL_Encode_String(fp, value.description);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_Alerts_AlertCodesDescriptor(FILE* fp, Alerts_AlertCodesDescriptor* value) UNUSED_OK;

static int HAL_Decode_Alerts_AlertCodesDescriptor(FILE* fp, Alerts_AlertCodesDescriptor* value)
{
    HAL_Decode_OpenStruct(fp);
    value->alertCode = HAL_Decode_UInt(fp);
    value->description = HAL_Decode_String(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_Alerts_AlertCodesDescriptor(FILE* fp, Array_Alerts_AlertCodesDescriptor value) UNUSED_OK;

static int HAL_Encode_Array_Alerts_AlertCodesDescriptor(FILE* fp, Array_Alerts_AlertCodesDescriptor value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Alerts_AlertCodesDescriptor(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_Alerts_AlertCodesDescriptor(FILE* fp, Array_Alerts_AlertCodesDescriptor* value) UNUSED_OK;

static int HAL_Decode_Array_Alerts_AlertCodesDescriptor(FILE* fp, Array_Alerts_AlertCodesDescriptor* value)
{
    InitArray_Alerts_AlertCodesDescriptor(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_Alerts_AlertCodesDescriptor(value, 1);
        HAL_Decode_Alerts_AlertCodesDescriptor(fp, &value->elems[i]);
    }
    return AJ_OK;
}


static int HAL_Encode_Alerts_Severity(FILE* fp, Alerts_Severity value) UNUSED_OK;

static int HAL_Encode_Alerts_Severity(FILE* fp, Alerts_Severity value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_Alerts_Severity(FILE* fp, Alerts_Severity* value) UNUSED_OK;

static int HAL_Decode_Alerts_Severity(FILE* fp, Alerts_Severity* value)
{
    *value = (Alerts_Severity)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_Alerts_Severity(FILE* fp, Array_Alerts_Severity value) UNUSED_OK;

static int HAL_Encode_Array_Alerts_Severity(FILE* fp, Array_Alerts_Severity value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_Alerts_Severity(FILE* fp, Array_Alerts_Severity* value) UNUSED_OK;

static int HAL_Decode_Array_Alerts_Severity(FILE* fp, Array_Alerts_Severity* value)
{
    InitArray_Alerts_Severity(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_Alerts_Severity(value, 1);
        value->elems[i] = (Alerts_Severity)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}

static const char* BusPath = "/cdm/emulated";

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



static AJ_Status GetAlerts(void *context, const char *objPath, Array_Alerts_AlertRecord *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "Alerts", "Alerts");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "Alerts", "Alerts");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_Alerts_AlertRecord const value = {0};
        HAL_Encode_Array_Alerts_AlertRecord(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "Alerts", "Alerts");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_Alerts_AlertRecord value;
    HAL_Decode_Array_Alerts_AlertRecord(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static AJ_Status MethodGetAlertCodesDescription(void *context, const char *objPath, char const* languageTag, Array_Alerts_AlertCodesDescriptor* description)
{
    CopyArray_Alerts_AlertCodesDescriptor(getAlertCodesDescriptor(), description);
    return AJ_OK;
}



static AJ_Status MethodAcknowledgeAlert(void *context, const char *objPath, uint16_t alertCode)
{
    // TODO
    return AJ_ERR_FAILURE;
}



static AJ_Status MethodAcknowledgeAllAlerts(void *context, const char *objPath)
{
    // TODO
    return AJ_ERR_FAILURE;
}



static AlertsModel model = {
    GetAlerts

    , MethodGetAlertCodesDescription
    , MethodAcknowledgeAlert
    , MethodAcknowledgeAllAlerts
};


AlertsModel *GetAlertsModel(void)
{
    return &model;
}
