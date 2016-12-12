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

#include "TargetHumidityModelImpl.h"
#include "../../../Utils/HAL.h"






static AJ_Status GetTargetValue(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "TargetValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetHumidity", "TargetValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "TargetValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetTargetValue(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "TargetHumidity", "TargetValue");
    HAL_Encode_UInt(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetMinValue(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "MinValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetHumidity", "MinValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "MinValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetMaxValue(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "MaxValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetHumidity", "MaxValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "MaxValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetStepValue(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "StepValue");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetHumidity", "StepValue");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "StepValue");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetSelectableHumidityLevels(void *context, const char *objPath, Array_uint8 *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "SelectableHumidityLevels");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetHumidity", "SelectableHumidityLevels");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_uint8 const value = {0};
        HAL_Encode_Array_uint8(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetHumidity", "SelectableHumidityLevels");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_uint8 value;
    HAL_Decode_Array_uint8(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static TargetHumidityModel model = {
    GetTargetValue
    , SetTargetValue
    , GetMinValue
    , GetMaxValue
    , GetStepValue
    , GetSelectableHumidityLevels

};


TargetHumidityModel *GetTargetHumidityModel(void)
{
    return &model;
}
