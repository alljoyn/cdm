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

#include "CurrentAirQualityModelImpl.h"
#include "../../../Utils/HAL.h"




static int HAL_Encode_CurrentAirQuality_ContaminantType(FILE* fp, CurrentAirQuality_ContaminantType value) UNUSED_OK;

static int HAL_Encode_CurrentAirQuality_ContaminantType(FILE* fp, CurrentAirQuality_ContaminantType value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_CurrentAirQuality_ContaminantType(FILE* fp, CurrentAirQuality_ContaminantType* value) UNUSED_OK;

static int HAL_Decode_CurrentAirQuality_ContaminantType(FILE* fp, CurrentAirQuality_ContaminantType* value)
{
    *value = (CurrentAirQuality_ContaminantType)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_CurrentAirQuality_ContaminantType(FILE* fp, Array_CurrentAirQuality_ContaminantType value) UNUSED_OK;

static int HAL_Encode_Array_CurrentAirQuality_ContaminantType(FILE* fp, Array_CurrentAirQuality_ContaminantType value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_CurrentAirQuality_ContaminantType(FILE* fp, Array_CurrentAirQuality_ContaminantType* value) UNUSED_OK;

static int HAL_Decode_Array_CurrentAirQuality_ContaminantType(FILE* fp, Array_CurrentAirQuality_ContaminantType* value)
{
    InitArray_CurrentAirQuality_ContaminantType(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_CurrentAirQuality_ContaminantType(value, 1);
        value->elems[i] = (CurrentAirQuality_ContaminantType)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetContaminantType(void *context, const char *objPath, CurrentAirQuality_ContaminantType *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "ContaminantType");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CurrentAirQuality", "ContaminantType");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "ContaminantType");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (CurrentAirQuality_ContaminantType)(int)value;
    fclose(fp);
    return result;
}


static AJ_Status GetCurrentValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "CurrentValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CurrentAirQuality", "CurrentValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        double const value = {0};
        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "CurrentValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetMinValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "MinValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CurrentAirQuality", "MinValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        double const value = {0};
        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "MinValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetMaxValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "MaxValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CurrentAirQuality", "MaxValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        double const value = {0};
        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "MaxValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetPrecision(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "Precision");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CurrentAirQuality", "Precision");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        double const value = {0};
        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "Precision");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetUpdateMinTime(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "UpdateMinTime");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "CurrentAirQuality", "UpdateMinTime");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "UpdateMinTime");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}




static CurrentAirQualityModel model = {
    GetContaminantType
    , GetCurrentValue
    , GetMinValue
    , GetMaxValue
    , GetPrecision
    , GetUpdateMinTime

};


CurrentAirQualityModel *GetCurrentAirQualityModel(void)
{
    return &model;
}
